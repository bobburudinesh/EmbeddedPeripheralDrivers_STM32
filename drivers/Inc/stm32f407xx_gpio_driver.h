/*
 * stm32f407xx_gpio_driver.h
 *
 *  Created on: Aug 23, 2024
 *      Author: dineshbobburu
 */

#ifndef INC_STM32F407XX_GPIO_DRIVER_H_
#define INC_STM32F407XX_GPIO_DRIVER_H_

#include "stm32f407xx.h"

/*
 * This holds the Configuration structure of GPIO pin
 * */
typedef struct {
	uint8_t GPIO_PinNumber; // Possible values from @GPIO_PIN_NUMBERS
	uint8_t GPIO_PinMode;  // Possible values from @GPIO_PIN_MODES
	uint8_t GPIO_PinSpeeed; // Possible values from @GPIO_PIN_SPEEDS
	uint8_t GPIO_PinpupdControl; // Possible values from @GPIO_PIN_PUPD CONFIG
	uint8_t GPIO_PinOPType; // Possible values from @GPIO_PIN_OUTPUT_TYPES
	uint8_t GPIO_PinAltFunMode; // Possible values from @GPIO_PIN_MODES
}GPIO_PINConfig_t;
/*
 * This is a Handle Structure for GPIO Pin
 * */

typedef struct {
	// Pointer to hold the base address of GPIO peripheral
	GPIO_RegDef_t *pGPIOx; // This holds the base address of GPIO port to which the pin belongs to
	GPIO_PINConfig_t GPIO_PinConfig; // Holds GPIO pin config settings
}GPIO_Handle_t;



/*
 * @GPIO_PIN_NUMBERS
 * GPIO Possible Numbers
 * */
#define GPIO_PIN_NO_0		0
#define GPIO_PIN_NO_1		1
#define GPIO_PIN_NO_2		2
#define GPIO_PIN_NO_3		3
#define GPIO_PIN_NO_4		4
#define GPIO_PIN_NO_5		5
#define GPIO_PIN_NO_6		6
#define GPIO_PIN_NO_7		7
#define GPIO_PIN_NO_8		8
#define GPIO_PIN_NO_9		9
#define GPIO_PIN_NO_10		10
#define GPIO_PIN_NO_11		11
#define GPIO_PIN_NO_12		12
#define GPIO_PIN_NO_13		13
#define GPIO_PIN_NO_14		14
#define GPIO_PIN_NO_15		15

/*
 * @GPIO_PIN_MODES
 * GPIO Possible Modes
 * */
#define GPIO_MODE_IN		0
#define GPIO_MODE_OUT		1
#define GPIO_MODE_ALTFN		2
#define GPIO_MODE_ANALOG	3
#define GPIO_MODE_IT_FT		4
#define GPIO_MODE_IT_RT		5
#define GPIO_MODE_IT_RFT	6


/*
 * @GPIO_PIN_OUTPUT_TYPES
 *GPIO Pin possible output types
 * */
#define GPIO_OP_TYPE_PP     0
#define GPIO_OP_TYPE_OD     1


/**
 *
 * @GPIO_PIN_SPEEDS
 * GPIO possible output SPEED
 *
 * */

#define GPIO_SPEED_LOW		0
#define GPIO_SPEED_MEDIUM	1
#define GPIO_SPEED_FAST		2
#define GPIO_SPEED_HIGH		3


/*
 * @GPIO_PIN_PUPD CONFIG
 * GPIO Pin pull up and pull down config macros
 *
 * */
#define GPIO_NO_PUPD 		0
#define GPIO_PIN_PU 		1
#define GPIO_PIN_PD 		2





/**********************************************************************************
 * API's Supported by this driver
 * For more information about the API's check the function definitions
 *************************************************************************************/

/*
 * Peripheral Clock setup
 * */

void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnorDi);

/*
 * Init and DEInit
 * */
void GPIO_Init(GPIO_Handle_t *pGPIOHandle);
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx );

/*
 * Read and Write
 * */
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx);
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t Value);
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t Value);
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);

/*
 * IRQ HAndling
 * **/
void GPIO_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi);
void GPIO_IRQPriorityConfig(uint8_t IRQNumber,uint8_t IRQPriority);
void GPIO_IRQHandling(uint8_t PinNumber);





#endif /* INC_STM32F407XX_GPIO_DRIVER_H_ */
