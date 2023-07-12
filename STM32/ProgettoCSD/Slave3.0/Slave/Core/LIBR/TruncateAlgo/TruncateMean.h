/*
 * TruncateMean.h
 *
 *  Created on: Jun 20, 2023
 *      Author: Utente
 */

#ifndef TRUNCATEALGO_TRUNCATEMEAN_H_
#define TRUNCATEALGO_TRUNCATEMEAN_H_
#include "stm32f3xx_hal.h"

#define SAMPLES 30	//Campioni >2


typedef struct {
	float temperature[SAMPLES];
	float humidity[SAMPLES];
	int index;
} TruncatedMeanData;

//prototipi
void TruncatedMean_Init(TruncatedMeanData *);
void TruncatedMean_AddSample(TruncatedMeanData *, float,float);
float TruncatedMean_CalculateTemperature(TruncatedMeanData *);
float TruncatedMean_CalculateHumidity(TruncatedMeanData *);
#endif /* TRUNCATEALGO_TRUNCATEMEAN_H_ */
