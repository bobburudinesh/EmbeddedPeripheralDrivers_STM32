/*
 * stm32f407xx_i2c_driver.c
 *
 *  Created on: Jan 25, 2025
 *      Author: dineshbobburu
 */


#include"stm32f407xx.h"




/**********************************************************************************
 * API's Supported by this driver
 * For more information about the API's check the function definitions
 *************************************************************************************/

/*
 * Peripheral Clock setup
 * */

void I2C_PeriClockControl(I2C_RegDef_t *pI2Cx, uint8_t EnorDi) {

	if(EnorDi == ENABLE) {
		if(pI2Cx == I2C1) {
			I2C1_PCLK_EN();
		} else if (pI2Cx == I2C2) {
			I2C2_PCLK_EN();
		} else if (pI2Cx == I2C3) {
			I2C3_PCLK_EN();
		}
	} else {
		if(pI2Cx == I2C1) {
			I2C1_PCLK_DI();
				} else if (pI2Cx == I2C2) {
					I2C2_PCLK_DI();
				} else if (pI2Cx == I2C3) {
					I2C3_PCLK_DI();
				}
	}
}

/*
 * Init and DEInit
 * */
uint32_t RCC_GetPLLOutputClock(void) {
	uint32_t pclk1;
	pclk1 = 0x01;
	return pclk1;
}
uint16_t AHB_PreScaler[8] = {2,4,8,16,32,64,128,512};
uint16_t APB1_PreScaler[4] = {2,4,8,16};
uint32_t RCC_GetPCLK1_Value(void){
	uint32_t pclk1, systemClk;
	uint8_t clksrc, temp, ahbp, apb1p;

	clksrc = (RCC->CFGR >> 2) & 0x03;

	if(clksrc == 0) {
		systemClk = 16000000;
	} else if (clksrc == 1) {
		systemClk = 8000000;
	} else if (clksrc == 2) {
		systemClk = RCC_GetPLLOutputClock();
	}
	// AHB
	temp = (RCC->CFGR >> 4) &0x0F;
	if(temp<8) {
		ahbp = 1;
	} else {
		ahbp = AHB_PreScaler[temp-8];
	}
	//APB1

	temp = (RCC->CFGR >> 10) &0x07;
		if(temp<8) {
			apb1p = 1;
		} else {
			apb1p = APB1_PreScaler[temp-8];
		}
		pclk1 = (systemClk/ahbp)/apb1p;
	return pclk1;
}
void I2C_Init(I2C_Handle_t *pI2CHandle) {
	I2C_PeriClockControl(pI2CHandle->pI2Cx, ENABLE);
	uint32_t tempReg = 0;
	tempReg |= pI2CHandle->I2C_Config.I2C_AckControl<<I2C_CR1_ACK;
	pI2CHandle->pI2Cx->CR1 = tempReg;
	//Configure the freq field of CR2
	tempReg = 0;
	tempReg |= RCC_GetPCLK1_Value()/1000000U;
	pI2CHandle->pI2Cx->CR2 = (tempReg & 0x3F);
	//Program Device own address
	tempReg |= pI2CHandle->I2C_Config.I2C_DeviceAddress<<1;
	tempReg |= 1<<14;
	pI2CHandle->pI2Cx->OAR1 = tempReg;

	//CCR Claculations
	uint16_t ccr_value = 0;
	tempReg = 0;
	if(pI2CHandle->I2C_Config.I2C_SCLSpeed < I2C_SCL_SPEED_SM) {
		// Standard Mode
		ccr_value = RCC_GetPCLK1_Value()/(2*pI2CHandle->I2C_Config.I2C_SCLSpeed);
		tempReg |= (ccr_value & 0xFFF);


	} else {
		// fast mode
		tempReg |= (1<<15);
		tempReg |= (pI2CHandle->I2C_Config.I2C_FMDutyCycle << 14);
		if(pI2CHandle->I2C_Config.I2C_FMDutyCycle == I2C_FM_DUTY_2) {
			ccr_value = RCC_GetPCLK1_Value()/(3*pI2CHandle->I2C_Config.I2C_SCLSpeed);
		} else {
			ccr_value = RCC_GetPCLK1_Value()/(25*pI2CHandle->I2C_Config.I2C_SCLSpeed);
		}
		tempReg |= (ccr_value & 0xFFF);
	}
	pI2CHandle->pI2Cx->CCR = tempReg;

}
void I2C_DeInit(I2C_RegDef_t *pI2Cx );


/*
 * SEND AND RECEIVE DATA
 *
 * */

/*
 * IRQ Configuration and ISR HAndling
 * */
void I2C_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi);
void I2C_IRQPriorityConfig(uint8_t IRQNumber,uint8_t IRQPriority);


/*
 * Other Peripheral Control API's
 * */
uint8_t I2C_GetFlagStatus(I2C_RegDef_t *pI2Cx, uint32_t FlagName);
void I2C_Peripheral_Control(I2C_RegDef_t *pI2Cx, uint8_t EnorDi) {
	if(EnorDi == ENABLE) {
		pI2Cx->CR1 |= (1<<I2C_CR1_PE);
	} else {
		pI2Cx->CR1 &= ~(1<<I2C_CR1_PE);
	}
}



/*
 * Application Callback
 * */

void I2C_ApplicationEventCallback(I2C_Handle_t *pI2CHandle, uint8_t applicationEvent);

