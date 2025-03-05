/*
 * stm32f407xx_i2c_driver.c
 *
 *  Created on: Jan 25, 2025
 *      Author: dineshbobburu
 */


#include"stm32f407xx.h"

static void I2C_GenerateStartCondition(I2C_RegDef_t *pI2Cx);
static void I2C_GenerateAddressPhase(I2C_RegDef_t *pI2Cx, uint8_t slaveAddr, uint8_t sendOrReceive);
static void I2C_ClearADDRFlag(I2C_RegDef_t *pI2Cx);
static void I2C_GenerateStopCondition(I2C_RegDef_t *pI2Cx);



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
	// NOTE: BELOW ACK is enabled but it should be again enabled in application code as the below enabling does not come into effect as PE is 0 initiallt.
	// SO, ACK should be again a=enabled when PE is Enabled.
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

	// T Rise Configuration
	if(pI2CHandle->I2C_Config.I2C_SCLSpeed < I2C_SCL_SPEED_SM) {

		tempReg = (RCC_GetPCLK1_Value()/1000000U)+1;
	} else {
		tempReg = ((RCC_GetPCLK1_Value()*300)/1000000U)+1;
	}

	pI2CHandle->pI2Cx->TRISE = (tempReg & 0x3F);

}
void I2C_DeInit(I2C_RegDef_t *pI2Cx );


/*
 * SEND AND RECEIVE DATA
 *
 * */
/*
 * Send and receive Helper functions Begin
 * */

static void I2C_GenerateStartCondition(I2C_RegDef_t *pI2Cx) {
	pI2Cx->CR1 |= (1<<I2C_CR1_START);
}

static void I2C_GenerateAddressPhase(I2C_RegDef_t *pI2Cx, uint8_t slaveAddr, uint8_t sendOrReceive) {
	slaveAddr = slaveAddr << 1;
	if(sendOrReceive == I2C_Data_Send) {
		slaveAddr &= ~(1);
	} else {
		slaveAddr |= 0x1;
	}

	pI2Cx->DR = slaveAddr;
}

static void I2C_ClearADDRFlag(I2C_RegDef_t *pI2Cx) {
	uint32_t dummyRead;
	dummyRead = pI2Cx->SR1;
	dummyRead = pI2Cx->SR2;
	(void) dummyRead;
}

static void I2C_GenerateStopCondition(I2C_RegDef_t *pI2Cx) {
	pI2Cx->CR1 |= (1<<I2C_CR1_STOP);
}




/*
 * Send and receive Helper functions END
 * */

void I2C_MasterSendData(I2C_Handle_t *pI2CHandle, uint8_t *pTxbuffer, uint32_t length, uint8_t slaveAddr){
	//1. Generate the Start Condition
	I2C_GenerateStartCondition(pI2CHandle->pI2Cx);

	//2. Confirm the start generation is completed by checking SB1 in SR1 reg.
	// Note: Until SB is cleared SCLK is stretched(pulled t low.)
	while(!I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_SB));
	//3. Send the address of slave with r/nw bit set to w(0).
	I2C_GenerateAddressPhase(pI2CHandle->pI2Cx, slaveAddr, I2C_Data_Send);
	//4. Confirm that Address phase is completed by checking the ADDR flag in SR1 reg.
	while(!I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_ADDR));
	//5. Clear the ADDR flag according to its software sequence.
	// Note: Until SB is cleared SCLK is stretched(pulled t low.)
	I2C_ClearADDRFlag(pI2CHandle->pI2Cx);
	//6. Send the data until len becomes 0
	while(length > 0) {
		while(!(I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_TXE)));/// wait till TxE is set
		pI2CHandle->pI2Cx->DR = *pTxbuffer;
		pTxbuffer++;
		length--;
	}
	//7. when length becomes 0, wait for TxE =1 and BTF = 1 before generating the stop condition
	// Note: TxE = 1 and BTF = 1, means both SR and DR are empty next transmission should begin
	// When BTF = 1, clock will be stretched to Low.
	while(!(I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_TXE)));
	while(!(I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_BTF)));

	//8. Generate Stop condition, Master need not wait for the stop condition.
	// Generating stop automatically clears BTF.
	I2C_GenerateStopCondition(pI2CHandle->pI2Cx);
}



void I2C_MasterReceiveData(I2C_Handle_t *pI2CHandle, uint8_t *pRxbuffer, uint32_t length, uint8_t slaveAddr){
	//1. Generate Start Condition
	I2C_GenerateStartCondition(pI2CHandle->pI2Cx);
	//2. Confirm the Start generation is competed by checking SB flag in SR1
	//Note: // Note: Until SB is cleared SCLK is stretched(pulled t low.)
	while(!I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_SB));
	//3.Send the address of slave with r/nw bit set to R(1).
	I2C_GenerateAddressPhase(pI2CHandle->pI2Cx, slaveAddr, I2C_Data_Receive);

	//4. Confirm that Address phase is completed by checking the ADDR flag in SR1 reg.
	while(!I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_ADDR));
	// Prodedure to read only one byte of data from slave
	if (length == 1) {
		// Disable Acking
		I2C_ConfigACKFlag(pI2CHandle->pI2Cx, I2C_ACK_DISABLE);

		// Clear the ADDR Flag
		I2C_ClearADDRFlag(pI2CHandle->pI2Cx);
		// Wait until RxNE becomes 1
		while(!(I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_RXNE)));/// wait till RxNE is set
		//generate STOP Condition
		I2C_GenerateStopCondition(pI2CHandle->pI2Cx);
		//read data into buffer

		*(pRxbuffer) = pI2CHandle->pI2Cx->DR;
		length--;
	}

	if(length > 1) {
		// Clear the ADDR Flag
		I2C_ClearADDRFlag(pI2CHandle->pI2Cx);
		for(uint32_t i = length; i>0;i--) {
			while(!(I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_RXNE)));/// wait till RxNE is set
			if(i == 2) {
				// Disable Acking
				I2C_ConfigACKFlag(pI2CHandle->pI2Cx, I2C_ACK_DISABLE);
				//generate STOP Condition
				I2C_GenerateStopCondition(pI2CHandle->pI2Cx);
			}
			while(!(I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_RXNE)));/// wait till RxNE is set
			*(pRxbuffer) = pI2CHandle->pI2Cx->DR;
			pRxbuffer++;
		}
	}
	if(pI2CHandle->I2C_Config.I2C_AckControl == I2C_ACK_ENABLE) {
		I2C_ConfigACKFlag(pI2CHandle->pI2Cx, I2C_ACK_ENABLE);
	}

}



/*
 * IRQ Configuration and ISR HAndling
 * */
void I2C_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi);
void I2C_IRQPriorityConfig(uint8_t IRQNumber,uint8_t IRQPriority);


/*
 * Other Peripheral Control API's
 * */
uint8_t I2C_GetFlagStatus(I2C_RegDef_t *pI2Cx, uint32_t FlagName) {
	if(pI2Cx->SR1 & FlagName){
		return FLAG_SET;
	}
	return FLAG_RESET;
}
void I2C_Peripheral_Control(I2C_RegDef_t *pI2Cx, uint8_t EnorDi) {
	if(EnorDi == ENABLE) {
		pI2Cx->CR1 |= (1<<I2C_CR1_PE);
	} else {
		pI2Cx->CR1 &= ~(1<<I2C_CR1_PE);
	}
}

void I2C_ConfigACKFlag(I2C_RegDef_t *pI2Cx, uint8_t EnorDi) {
	if (EnorDi == I2C_ACK_ENABLE) {
		pI2Cx->CR1 |= 1<<I2C_CR1_ACK;
	} else {
		pI2Cx->CR1 &= ~(1<<I2C_CR1_ACK);
	}

}



/*
 * Application Callback
 * */

void I2C_ApplicationEventCallback(I2C_Handle_t *pI2CHandle, uint8_t applicationEvent);

