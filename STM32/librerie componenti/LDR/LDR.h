#ifndef LDR_H_
#define LDR_H_

#define HAL_ADC_MODULE_ENABLED

#include "stm32f3xx_hal.h"

// The Number OF LM35 Sensors To Be Used In The Project
#define SENSORS_NUM  1

typedef struct
{
	GPIO_TypeDef * LDR_GPIO;
	ADC_TypeDef*   ADC_Instance;
	uint32_t       ADC_CH;
}LDR_CfgType;


/*-----[ Prototypes For All Functions ]-----*/
void LDR_Init(uint16_t LM35_Instance);
float LDR_Read(uint16_t LM35_Instance);
float LDR_FirstRead(uint16_t LDR_Instance);

#endif /* LDR_H_ */
