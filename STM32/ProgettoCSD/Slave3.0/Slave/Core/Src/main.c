/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include <stdio.h>
#include "string.h"
#include <stdbool.h>
#include "../LIBR/Dht11/DHT.h"
#include "../LIBR/TruncateAlgo/TruncateMean.h"
#define one 49
#define  DT 0.5
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim16;
TIM_HandleTypeDef htim17;

UART_HandleTypeDef huart1;
DHT_DataTypedef DHT11_Data;
TruncatedMeanData data;
float Temperature, Humidity;
float LastTemperature, LastHumidity;
int modo=0;
char modoTx='0';
bool StartSystem=false;
int contPA0=0;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM16_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_TIM17_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */


int i=0;
char bufferH[10],bufferT[50];
char msgRx;


void HAL_UART_RxCpltCallback(UART_HandleTypeDef * huart)
{
	if (HAL_UART_Receive_IT(&huart1, &msgRx, 1) == HAL_OK && msgRx==one) {
			       HAL_GPIO_WritePin(GPIOE, GPIO_PIN_14, GPIO_PIN_SET);
			       StartSystem=true;
			       contPA0++;

	}
}








bool StartTx=false;


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* Prevent unused argument(s) compilation warning */


	if( StartSystem==true){
		//lettura dati
		   HAL_GPIO_WritePin(GPIOE, GPIO_PIN_15,GPIO_PIN_SET);
		   DHT_GetData(&DHT11_Data);
			Temperature = DHT11_Data.TemperatureD +(0.1)*DHT11_Data.TemperatureU;
			Humidity =    DHT11_Data.HumidityD +(0.1)*DHT11_Data.HumidityU;
		if(htim->Instance==htim16.Instance){
			if(modo==0){
            	if(i<=SAMPLES){
            			TruncatedMean_AddSample(&data,Temperature,Humidity);


						if(i==0 && StartTx==false){

							   gcvt(Temperature, sizeof(Temperature), bufferT);
							   HAL_UART_Transmit(&huart1, (uint8_t*)bufferT, strlen(bufferT), HAL_MAX_DELAY);

							   for(int i=0;i<50;i++)bufferT[i]=0;

							   sprintf(bufferT, "+");
							   HAL_UART_Transmit(&huart1, (uint8_t*)bufferT, strlen(bufferT), HAL_MAX_DELAY);

							   for(int i=0;i<50;i++)bufferT[i]=0;

							   gcvt(Humidity, sizeof(Humidity), bufferT);
							   HAL_UART_Transmit(&huart1, (uint8_t*)bufferT, strlen(bufferT), HAL_MAX_DELAY);

							   for(int i=0;i<50;i++)bufferT[i]=0;

							   sprintf(bufferT, "-");
							   HAL_UART_Transmit(&huart1, (uint8_t*)bufferT, strlen(bufferT), HAL_MAX_DELAY);

							   for(int i=0;i<10;i++)bufferT[i]=0;

							   //gcvt(modo, sizeof(modo), bufferT);
							   HAL_UART_Transmit(&huart1, &modoTx, strlen(modoTx), HAL_MAX_DELAY);



							   sprintf(bufferT, "s");
							   HAL_UART_Transmit(&huart1, (uint8_t*)bufferT, strlen(bufferT), HAL_MAX_DELAY);

							   for(int i=0;i<50;i++)bufferT[i]=0;

							   StartTx=true;

						}
						i++;
            	}else{
						i=0;
						float TmpMean= TruncatedMean_CalculateTemperature(&data);
						float TmpHmdy= TruncatedMean_CalculateHumidity(&data);


						gcvt(TmpMean, sizeof(TmpMean), bufferT);
													   HAL_UART_Transmit(&huart1, (uint8_t*)bufferT, strlen(bufferT), HAL_MAX_DELAY);

													   for(int i=0;i<50;i++)bufferT[i]=0;

													   sprintf(bufferT, "+");
													   HAL_UART_Transmit(&huart1, (uint8_t*)bufferT, strlen(bufferT), HAL_MAX_DELAY);

													   for(int i=0;i<50;i++)bufferT[i]=0;

													   gcvt(TmpHmdy, sizeof(TmpHmdy), bufferT);
													   HAL_UART_Transmit(&huart1, (uint8_t*)bufferT, strlen(bufferT), HAL_MAX_DELAY);

													   for(int i=0;i<50;i++)bufferT[i]=0;

													   sprintf(bufferT, "-");
													   HAL_UART_Transmit(&huart1, (uint8_t*)bufferT, strlen(bufferT), HAL_MAX_DELAY);

													   for(int i=0;i<10;i++)bufferT[i]=0;


													   HAL_UART_Transmit(&huart1, &modoTx, strlen(modoTx), HAL_MAX_DELAY);

													   sprintf(bufferT, "s");
													   HAL_UART_Transmit(&huart1, (uint8_t*)bufferT, strlen(bufferT), HAL_MAX_DELAY);

													   for(int i=0;i<50;i++)bufferT[i]=0;
            	}

	}else{

					if((Temperature!=LastTemperature)){
						if (Temperature - LastTemperature >= DT || LastTemperature - Temperature >= DT ) {

							gcvt(Temperature, sizeof(Temperature), bufferT);
							HAL_UART_Transmit(&huart1, (uint8_t*)bufferT, strlen(bufferT), HAL_MAX_DELAY);

							for(int i=0;i<50;i++)bufferT[i]=0;

							sprintf(bufferT, "+");
							HAL_UART_Transmit(&huart1, (uint8_t*)bufferT, strlen(bufferT), HAL_MAX_DELAY);

							for(int i=0;i<50;i++)bufferT[i]=0;

							gcvt(Humidity, sizeof(Humidity), bufferT);
							HAL_UART_Transmit(&huart1, (uint8_t*)bufferT, strlen(bufferT), HAL_MAX_DELAY);

							for(int i=0;i<50;i++)bufferT[i]=0;

							sprintf(bufferT, "-");
							HAL_UART_Transmit(&huart1, (uint8_t*)bufferT, strlen(bufferT), HAL_MAX_DELAY);

							for(int i=0;i<50;i++)bufferT[i]=0;

							HAL_UART_Transmit(&huart1, &modoTx, strlen(modoTx), HAL_MAX_DELAY);

							sprintf(bufferT, "s");
							HAL_UART_Transmit(&huart1, (uint8_t*)bufferT, strlen(bufferT), HAL_MAX_DELAY);

							for(int i=0;i<50;i++)bufferT[i]=0;

							LastTemperature=Temperature;
							LastHumidity=Humidity;
						}




					}
	}

 }

	if(htim->Instance==htim17.Instance && modo==1 && !(htim->Instance==htim16.Instance)){
								gcvt(Temperature, sizeof(Temperature), bufferT);
								HAL_UART_Transmit(&huart1, (uint8_t*)bufferT, strlen(bufferT), HAL_MAX_DELAY);

								for(int i=0;i<50;i++)bufferT[i]=0;

								sprintf(bufferT, "+");
								HAL_UART_Transmit(&huart1, (uint8_t*)bufferT, strlen(bufferT), HAL_MAX_DELAY);

								for(int i=0;i<50;i++)bufferT[i]=0;

								gcvt(Humidity, sizeof(Humidity), bufferT);
								HAL_UART_Transmit(&huart1, (uint8_t*)bufferT, strlen(bufferT), HAL_MAX_DELAY);

								for(int i=0;i<50;i++)bufferT[i]=0;

								sprintf(bufferT, "-");
								HAL_UART_Transmit(&huart1, (uint8_t*)bufferT, strlen(bufferT), HAL_MAX_DELAY);

								for(int i=0;i<50;i++)bufferT[i]=0;

								HAL_UART_Transmit(&huart1, &modoTx, strlen(modoTx), HAL_MAX_DELAY);

								sprintf(bufferT, "s");
								HAL_UART_Transmit(&huart1, (uint8_t*)bufferT, strlen(bufferT), HAL_MAX_DELAY);

								for(int i=0;i<50;i++)bufferT[i]=0;
	}
}

}
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM16_Init();
  MX_USART1_UART_Init();
  MX_TIM17_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  HAL_TIM_Base_Start_IT(&htim16);
  HAL_TIM_Base_Start_IT(&htim17);
   TruncatedMean_Init(&data);
   HAL_GPIO_WritePin(GPIOE, GPIO_PIN_10,GPIO_PIN_SET);
   HAL_UART_Receive_IT(&huart1, &msgRx, 1);


   while (1)
   {
     /* USER CODE END WHILE */
 	  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_15,GPIO_PIN_RESET);



 	  	  if((GPIOA->IDR & GPIO_IDR_0) ==GPIO_IDR_0 &&  StartSystem==true){
 	  	 		  while((GPIOA->IDR & GPIO_IDR_0) ==GPIO_IDR_0);
 	  	 		  contPA0++;

 	  	 		  	  if(contPA0==1){

 	  	 				if(modo==0){
 	  	 						HAL_GPIO_WritePin(GPIOE, GPIO_PIN_10,GPIO_PIN_RESET);
 	  	 						HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11,GPIO_PIN_SET);
 	  	 						modo=1;
 	  	 						LastTemperature=0;
 	  	 						LastHumidity=0;

 	  	 						//modoTx='1';



 	  	 				}else{
 	  	 						HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11,GPIO_PIN_RESET);
 	  	 						HAL_GPIO_WritePin(GPIOE, GPIO_PIN_10,GPIO_PIN_SET);
 	  	 						modo=0;
 	  	 						//modoTx='0';
 	  	 						i=0;
 	  	 						TruncatedMean_Init(&data);
 	  	 						StartTx=false;



 	  	 				}


 	  	 		  	  }else if(contPA0==2){

 	  	 		  		  if(modoTx=='1'){
 	  	 		  			  modoTx='0';
 	  	 		  		  }else  if(modoTx=='0'){
 	  	 		  			  modoTx='1';
 	  	 		  		  }


 	  	 		  	contPA0=0;

 	  	 		  	  }


 	  	  }







 	  	  }

 	  	  }
     /* USER CODE BEGIN 3 */

   /* USER CODE END 3 */

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM16 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM16_Init(void)
{

  /* USER CODE BEGIN TIM16_Init 0 */

  /* USER CODE END TIM16_Init 0 */

  /* USER CODE BEGIN TIM16_Init 1 */

  /* USER CODE END TIM16_Init 1 */
  htim16.Instance = TIM16;
  htim16.Init.Prescaler = 50000;
  htim16.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim16.Init.Period = 100;
  htim16.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim16.Init.RepetitionCounter = 0;
  htim16.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim16) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM16_Init 2 */

  /* USER CODE END TIM16_Init 2 */

}

/**
  * @brief TIM17 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM17_Init(void)
{

  /* USER CODE BEGIN TIM17_Init 0 */

  /* USER CODE END TIM17_Init 0 */

  /* USER CODE BEGIN TIM17_Init 1 */

  /* USER CODE END TIM17_Init 1 */
  htim17.Instance = TIM17;
  htim17.Init.Prescaler = 1011000;
  htim17.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim17.Init.Period = 100000;
  htim17.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim17.Init.RepetitionCounter = 0;
  htim17.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim17) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM17_Init 2 */

  /* USER CODE END TIM17_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 9600;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13
                          |GPIO_PIN_14|GPIO_PIN_15, GPIO_PIN_RESET);

  /*Configure GPIO pins : PA0 PA5 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PE10 PE11 PE12 PE13
                           PE14 PE15 */
  GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13
                          |GPIO_PIN_14|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
