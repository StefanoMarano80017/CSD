/*
 * fuzzy.c
 *
 *  Created on: Jun 20, 2023
 *      Author: Utente
 */

#include "fuzzy.h"

// Funzione di appartenenza triangolare
float triangular_membership(float x, FuzzyTerm term) {
  if (x <= term.a || x >= term.c) {
    return 0;
  } else if (x > term.a && x <= term.b) {
    return (x - term.a) / (term.b - term.a);
  } else {
    return (term.c - x) / (term.c - term.b);
  }
}

// Funzione di inferenza fuzzy
float fuzzy_inference(float input1, float input2, FuzzyVariable var1, FuzzyVariable var2, FuzzyVariable outputVar, FuzzyRule rules[], int nRules) {
  float output = 0;
  float total_weight = 0;

  for (int i = 0; i < nRules; i++) {
    float rule_strength = fminf(triangular_membership(input1, var1.terms[rules[i].input1]),
                                triangular_membership(input2, var2.terms[rules[i].input2]));

    float centroid = (outputVar.terms[rules[i].output].a + outputVar.terms[rules[i].output].b + outputVar.terms[rules[i].output].c) / 3;

    output += rule_strength * centroid;
    total_weight += rule_strength;
  }

  return total_weight != 0 ? output / total_weight : 0;
}

// Funzione di regolazione del servomotore
int regulate_servomotor(float temperature, float humidity) {
  // Definizione delle variabili fuzzy
  FuzzyVariable temperatureVar = {.name = "temperature",
                                  .terms = {{"low", -20, 0, 20},
                                            {"medium", 10, 25, 40},
                                            {"high", 30, 50, 70}}};

  FuzzyVariable humidityVar = {.name = "humidity",
                               .terms = {{"low", 0, 30, 60},
                                         {"medium", 40, 60, 80},
                                         {"high", 70, 90, 100}}};

  FuzzyVariable servomotorVar = {.name = "servomotor",
                                 .terms = {{"low", 0, 45, 90},
                                           {"medium", 45, 90, 135},
                                           {"high", 90, 135, 180}}};

  // Definizione delle regole fuzzy
  FuzzyRule rules[] = {{LOW, LOW, LOW},
                       {LOW, MEDIUM, LOW},
                       {LOW, HIGH, MEDIUM},
                       {MEDIUM, LOW, LOW},
                       {MEDIUM, MEDIUM, MEDIUM},
                       {MEDIUM, HIGH, HIGH},
                       {HIGH, LOW, MEDIUM},
                       {HIGH, MEDIUM, HIGH},
                       {HIGH, HIGH, HIGH}};

  int nRules = sizeof(rules) / sizeof(FuzzyRule);

  // Calcolo dell'inferenza fuzzy e regolazione del servomotor
  float servomotor_angle = fuzzy_inference(temperature, humidity, temperatureVar, humidityVar, servomotorVar, rules, nRules);

  return (int)roundf(servomotor_angle);
}
