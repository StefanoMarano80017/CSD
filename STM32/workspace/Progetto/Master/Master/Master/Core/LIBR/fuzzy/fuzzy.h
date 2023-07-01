/*
 * fuzzy.h
 *
 *  Created on: Jun 20, 2023
 *      Author: Utente
 */

#ifndef FUZZY_FUZZY_H_
#define FUZZY_FUZZY_H_
#include <stdio.h>
#include <math.h>

// Definizione delle funzioni di appartenenza fuzzy
float temperature_low(float temperature);
float temperature_medium(float temperature);
float temperature_high(float temperature);
float humidity_low(float humidity);
float humidity_medium(float humidity);
float humidity_high(float humidity);
float airflow_low();
float airflow_medium();
float airflow_high();

// Definizione delle regole fuzzy
float rule1(float temperature, float humidity);
float rule2(float temperature, float humidity);
float rule3(float temperature, float humidity);
float rule4(float temperature, float humidity);
float rule5(float temperature, float humidity);
float rule6(float temperature, float humidity);
float rule7(float temperature, float humidity);
float rule8(float temperature, float humidity);


#endif /* FUZZY_FUZZY_H_ */
