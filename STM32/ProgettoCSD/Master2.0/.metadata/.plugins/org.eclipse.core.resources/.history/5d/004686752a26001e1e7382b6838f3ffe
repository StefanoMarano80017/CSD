# include "invio.h"

double TempSetpoint=25;
PID_TypeDef TPID;
double PIDOut=0;

void invio_tx(float temp0, float hmdy0, double intes, UART_HandleTypeDef huart4){
	char bufferT[50];

	//Trasmissione Temp
	gcvt(temp0, sizeof(temp0), bufferT);
	HAL_UART_Transmit(&huart4, (uint8_t*)bufferT, strlen(bufferT), HAL_MAX_DELAY);
	sprintf(bufferT, "+");
	HAL_UART_Transmit(&huart4, (uint8_t*)bufferT, strlen(bufferT), HAL_MAX_DELAY);

	//Trasmissione Umidità
	gcvt(hmdy0, sizeof(hmdy0), bufferT);
	HAL_UART_Transmit(&huart4, (uint8_t*)bufferT, strlen(bufferT), HAL_MAX_DELAY);
	sprintf(bufferT, "+");
	HAL_UART_Transmit(&huart4, (uint8_t*)bufferT, strlen(bufferT), HAL_MAX_DELAY);

	gcvt(intes, sizeof(intes), bufferT);
	HAL_UART_Transmit(&huart4, (uint8_t*)bufferT, strlen(bufferT), HAL_MAX_DELAY);
	sprintf(bufferT, "\n");
	HAL_UART_Transmit(&huart4, (uint8_t*)bufferT, strlen(bufferT), HAL_MAX_DELAY);

	for(int i=0;i<50;i++)bufferT[i]=0;
}

double calcola_parametri(float Temp, float Hmdy, int StatoC, int modo){
	if(StatoC>0 && modo==0){
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11,GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_10,GPIO_PIN_RESET);
		double Tem= Temp;
		PID(&TPID, &Tem, &PIDOut, &TempSetpoint, PID_KP, PID_KD, PID_KI, _PID_P_ON_E, _PID_CD_DIRECT);
		PID_SetMode(&TPID, _PID_MODE_AUTOMATIC);
		PID_SetSampleTime(&TPID, SAMPLE_TIME);
		PID_SetOutputLimits(&TPID, PID_LIM_MIN, PID_LIM_MAX);
	 	PID_Compute(&TPID);
	 	return PIDOut;
	}else if(StatoC>0 && modo==1){
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_10,GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11,GPIO_PIN_RESET);
		//funzione fuzzy
		return calcola_fuzzy(Temp, Hmdy);
	}
	return 0;
}


