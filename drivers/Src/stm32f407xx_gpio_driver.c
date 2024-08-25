/*
 * stm32f407xx_gpio_driver.c
 *
 *  Created on: Aug 23, 2024
 *      Author: dineshbobburu
 */


#include "stm32f407xx_gpio_driver.h"


/*
 * Peripheral Clock setup
 * */

void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnorDi) {
	if(EnorDi == ENABLE) {
		if (pGPIOx == GPIOA) {
			GPIOA_PCLK_EN();
		} else if (pGPIOx == GPIOB) {
			GPIOB_PCLK_EN();
		}else if (pGPIOx == GPIOC) {
			GPIOC_PCLK_EN();
		}else if (pGPIOx == GPIOD) {
			GPIOD_PCLK_EN();
		}else if (pGPIOx == GPIOE) {
			GPIOE_PCLK_EN();
		}else if (pGPIOx == GPIOF) {
			GPIOF_PCLK_EN();
		}else if (pGPIOx == GPIOG) {
			GPIOG_PCLK_EN();
		}else if (pGPIOx == GPIOH) {
			GPIOH_PCLK_EN();
		}else if (pGPIOx == GPIOI) {
			GPIOI_PCLK_EN();
		}

	} else {
		if (pGPIOx == GPIOA) {
					GPIOA_PCLK_DI();
				} else if (pGPIOx == GPIOB) {
					GPIOB_PCLK_DI();
				}else if (pGPIOx == GPIOC) {
					GPIOC_PCLK_DI();
				}else if (pGPIOx == GPIOD) {
					GPIOD_PCLK_DI();
				}else if (pGPIOx == GPIOE) {
					GPIOE_PCLK_DI();
				}else if (pGPIOx == GPIOF) {
					GPIOF_PCLK_DI();
				}else if (pGPIOx == GPIOG) {
					GPIOG_PCLK_DI();
				}else if (pGPIOx == GPIOH) {
					GPIOH_PCLK_DI();
				}else if (pGPIOx == GPIOI) {
					GPIOI_PCLK_DI();
				}
	}
}

/*
 * Init and DEInit
 * */
void GPIO_Init(GPIO_Handle_t *pGPIOHandle) {
	uint32_t temp = 0; // temp register
	// 1. CONFIGURE MODE
	if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_ANALOG) {
		temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode << (2* pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
		pGPIOHandle->pGPIOx->MODER &= ~(0x3<<pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		pGPIOHandle->pGPIOx->MODER |= temp;

	} else {
		// This is an interrupt
	}
	temp = 0;
	//2. CONFIGURE SPEED
	temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinSpeeed << (2* pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
	pGPIOHandle->pGPIOx->OSPEEDR &= ~(0x3<<pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
	pGPIOHandle->pGPIOx->OSPEEDR |= temp;
	temp = 0;
	//3. CONFIGURE PUPD SETTINGS
	temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinpupdControl << (2* pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
	pGPIOHandle->pGPIOx->PUPDR &= ~(0x3<<pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
	pGPIOHandle->pGPIOx->PUPDR |= temp;
	temp = 0;
	//4. CONFIGURE O/P TYPE
	temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinOPType << (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
	pGPIOHandle->pGPIOx->OTYPER &= ~(0x3<<pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
	pGPIOHandle->pGPIOx->OTYPER |= temp;
	temp = 0;
	//5. CONFIGURE ALT FUNCTION
	if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_ALTFN) {
		uint8_t temp1 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 8;
		uint8_t temp2 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 8;
		temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinAltFunMode <<(4*temp2) );
		pGPIOHandle->pGPIOx->AFR[temp1] &= ~(0xF <<(4*temp2) );
		pGPIOHandle->pGPIOx->AFR[temp1] |= temp;
		temp = 0;
	}

}
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx ) {
	if (pGPIOx == GPIOA) {
		GPIOA_REG_RESET();
					} else if (pGPIOx == GPIOB) {
						GPIOB_REG_RESET();
					}else if (pGPIOx == GPIOC) {
						GPIOC_REG_RESET();
					}else if (pGPIOx == GPIOD) {
						GPIOD_REG_RESET();
					}else if (pGPIOx == GPIOE) {
						GPIOE_REG_RESET();
					}else if (pGPIOx == GPIOF) {
						GPIOF_REG_RESET();
					}else if (pGPIOx == GPIOG) {
						GPIOG_REG_RESET();
					}else if (pGPIOx == GPIOH) {
						GPIOH_REG_RESET();
					}else if (pGPIOx == GPIOI) {
						GPIOI_REG_RESET();
					}
}

/*
 * Read and Write
 * */
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber) {
	uint8_t value;
	value = (uint8_t)(pGPIOx->IDR >> PinNumber) & (0x00000001);
	return value;
}
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx) {
	uint16_t value;
	value = (uint16_t)(pGPIOx->IDR);
	return value;
}
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t Value) {
	if(Value == GPIO_PIN_SET) {
		//write 1
		pGPIOx->ODR |= 1<< PinNumber;
	} else {
		//write 0
		pGPIOx->ODR |= 0<< PinNumber;
	}
}
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t Value) {
	pGPIOx->ODR = Value;
}
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber) {
	pGPIOx->ODR ^= 1<<PinNumber;
}

/*
 * IRQ HAndling
 * **/
void GPIO_IRQConfig(uint8_t IRQNumber, uint8_t IRQPriority, uint8_t EnorDi);
void GPIO_IRQHandling(uint8_t PinNumber);

