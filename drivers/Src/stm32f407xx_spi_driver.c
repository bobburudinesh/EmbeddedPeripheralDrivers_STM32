/*
 * stm32f407xx_spi_driver.c
 *
 *  Created on: Aug 26, 2024
 *      Author: dineshbobburu
 */
#include "stm32f407xx_spi_driver.h"

static void spi_txe_interrupt_handle(SPI_Handle_t *pSPIHandle);
static void spi_rnxe_interrupt_handle(SPI_Handle_t *pSPIHandle);
static void spi_ovr_err_interrupt_handle(SPI_Handle_t *pSPIHandle);

/*
 * Peripheral Clock setup
 * */

void SPI_PeriClockControl(SPI_RegDef_t *pSPIx, uint8_t EnorDi) {
	if (EnorDi == ENABLE) {
		if (pSPIx == SPI1) {
			SPI1_PCLK_EN();
				} else if (pSPIx == SPI2) {
					SPI2_PCLK_EN();
				}else if (pSPIx == SPI3) {
					SPI3_PCLK_EN();
				}
	} else {
		if (pSPIx == SPI1) {
					SPI1_PCLK_DI();
						} else if (pSPIx == SPI2) {
							SPI2_PCLK_DI();
						}else if (pSPIx == SPI3) {
							SPI3_PCLK_DI();
						}
	}
}

/*
 * Init and DEInit
 * */
void SPI_Init(SPI_Handle_t *pSPIHandle) {
	uint32_t temp = 0;
	// Enable peripheral clock
	SPI_PeriClockControl(pSPIHandle->pSPIx, ENABLE);
	if (pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_FD) {
		// Clear BIDI_Mode
		temp &= !(1<<SPI_CR1_BIDIMODE);
	} else if (pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_HD) {
		// Set BIDI_Mode
		temp |= 1<<SPI_CR1_BIDIMODE;

	} else if (pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_RXONLY) {
		// Clear BIDI_MODE and SET RX_ONLY mode
		temp &= ~(1<<SPI_CR1_BIDIMODE);
		temp |= 1<<SPI_CR1_RXONLY;
	}

	temp |= (pSPIHandle->SPIConfig.SPI_DFF << SPI_CR1_DFF);
	temp |= pSPIHandle->SPIConfig.SPI_SSM << SPI_CR1_SSM;
	temp |= pSPIHandle->SPIConfig.SPI_DeviceMode<<SPI_CR1_MSTR;
	temp |= pSPIHandle->SPIConfig.SPI_SclkSpeed << SPI_CR1_BR2_0;
	temp |= pSPIHandle->SPIConfig.SPI_CPHA <<SPI_CR1_CHPA;
	temp |= pSPIHandle->SPIConfig.SPI_CPOL < SPI_CR1_CPOL;
	pSPIHandle->pSPIx->CR1 = temp;
}
void SPI_DeInit(SPI_RegDef_t *pSPIx ) {
	if (pSPIx == SPI1) {
		SPI1_RESET();
					} else if (pSPIx == SPI2) {
						SPI2_RESET();
					} else if (pSPIx == SPI3) {
						SPI3_RESET();
					}
}


/*
 * SEND AND RECEIVE DATA
 *
 * */



//*** This is a blocking call function, it is called blocking because until all the thousand bytes are transferred function will not return.
void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t  *pTxBuffer, uint32_t length) {

	while(length>0) {
		// checking if TX buffer is empty else we have to wait; Check for TXE Bit.
		while(SPI_GetFlagStatus(pSPIx, SPI_TXE_FLAG) == FLAG_RESET);
		// Check for DFF bit to know if data is 8 bit or 16 bit.
		if(pSPIx->CR1 & (1<<SPI_CR1_DFF)) {
				// 16 bit data frame
				*((uint16_t*)pTxBuffer) = pSPIx->DR;
				length--;
				(uint16_t*)pTxBuffer++;
		} else {
				// 8 bit data frame
				*pTxBuffer = pSPIx->DR;
				pTxBuffer++;
		}
			length--;


	}
}

void SPI_ReceiveData(SPI_RegDef_t *pSPIx, uint8_t  *pRxBuffer, uint32_t length) {
	while (length > 0) {
		while(SPI_GetFlagStatus(pSPIx, SPI_SR_RXNE) == FLAG_RESET); // checking if the receiver buffer has data, if it has data it will go past this loop
		// CHeck for 8 bit data DFF or 16 bit DFF
		if(pSPIx->CR1 & (1<<SPI_CR1_DFF)) {
			// 16 bit
			pSPIx->DR = *((uint16_t*)pRxBuffer);
			(uint16_t*)pRxBuffer++;
			length--;
		} else {
			// 8 bit
			pSPIx->DR = *pRxBuffer;
			pRxBuffer++;

		}
		length--;
	}
}

uint8_t SPI_SendDataIT(SPI_Handle_t pSPIHandle, uint8_t  *pTxBuffer , uint32_t length){
	uint8_t state = pSPIHandle.TxState;
	if(state != SPI_BUSY_IN_TX){
		//1. Save Txbuffer and len info in some global variables
			pSPIHandle.pTxBuffer = pTxBuffer;
			pSPIHandle.Tx_Len = length;
			//2. Mark the SPI state as busy in transmission so that no other code can take over same SPI Peripheral until transmission is over
			pSPIHandle.TxState = SPI_BUSY_IN_TX;
			// 3. Enable TXEIE control bit to get interrupt when ever TXE flag is set in SR
			pSPIHandle.pSPIx->CR2 |= (1<<SPI_CR2_TXEIE);
			//4, Data transmission will be handled by ISR.
	}

	return state;



}


uint8_t SPI_ReceiveDataIT(SPI_Handle_t pSPIHandle, uint8_t  *pRxBuffer , uint32_t length) {
	uint8_t state = pSPIHandle.RxState;
		if(state != SPI_BUSY_IN_RX){
			//1. Save Rxbuffer and len info in some global variables
				pSPIHandle.pRxBuffer = pRxBuffer;
				pSPIHandle.Rx_Len = length;
				//2. Mark the SPI state as busy in receiving so that no other code can take over same SPI Peripheral until receiving is over
				pSPIHandle.RxState = SPI_BUSY_IN_TX;
				// 3. Enable RXNEIE control bit to get interrupt when ever RXE flag is set in SR
				pSPIHandle.pSPIx->CR2 |= (1<<SPI_CR2_RXNEIE);
				//4, Data receiving will be handled by ISR.
		}

		return state;
}

static void spi_txe_interrupt_handle(SPI_Handle_t *pSPIHandle){
	// Check for DFF bit to know if data is 8 bit or 16 bit.
			if(pSPIHandle->pSPIx->CR1 & (1<<SPI_CR1_DFF)) {
					// 16 bit data frame
					*((uint16_t*)pSPIHandle->pTxBuffer) = pSPIHandle->pSPIx->DR;
					pSPIHandle->Tx_Len--;
					(uint16_t*)pSPIHandle->pTxBuffer++;
			} else {
					// 8 bit data frame
					*pSPIHandle->pTxBuffer = pSPIHandle->pSPIx->DR;
					pSPIHandle->pTxBuffer++;
			}
				pSPIHandle->Tx_Len--;
				if(!pSPIHandle->Tx_Len) {
					//TxLen is 0, so close the SPI transmission and inform the application that tx is over.
					SPI_CloseTransmission(pSPIHandle);
				}
}
static void spi_rnxe_interrupt_handle(SPI_Handle_t *pSPIHandle) {
	// CHeck for 8 bit data DFF or 16 bit DFF
			if(pSPIHandle->pSPIx->CR1 & (1<<SPI_CR1_DFF)) {
				// 16 bit
				pSPIHandle->pSPIx->DR = *((uint16_t*)pSPIHandle->pRxBuffer);
				(uint16_t*)pSPIHandle->pRxBuffer++;
				pSPIHandle->Rx_Len--;
			} else {
				// 8 bit
				pSPIHandle->pSPIx->DR = *pSPIHandle->pRxBuffer;
				pSPIHandle->pRxBuffer++;

			}
			pSPIHandle->Rx_Len--;
			if(!pSPIHandle->Rx_Len) {
				//RxLen is 0, so close the SPI transmission and inform the application that tx is over.
				SPI_CloseReception(pSPIHandle);
							}
}
static void spi_ovr_err_interrupt_handle(SPI_Handle_t *pSPIHandle) {
	uint8_t temp;
	//1. Clear the OVR flag. It is cleared by reading DR register and the reading SR register(refer OVR documentation)
	if(pSPIHandle->TxState != SPI_BUSY_IN_TX) {
		temp = pSPIHandle->pSPIx->DR;
		temp = pSPIHandle->pSPIx->SR;

	}
	(void)temp;
	// Inform the application
	SPI_ApplicationEventCallback(pSPIHandle, SPI_EVENT_OVR_ERR);



}

/*
 * IRQ Configuration and ISR HAndling
 * */
// Implement IRQ Hanlders
void SPI_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi);
void SPI_IRQPriorityConfig(uint8_t IRQNumber,uint8_t IRQPriority);
void SPI_IRQHandling(SPI_Handle_t *pHandle) {
	uint8_t temp1, temp2;
	//1. Check for TXE
	temp1 = pHandle->pSPIx->SR & (1<< SPI_SR_TXE);
	//2. Check for TXEIE
	temp2 = pHandle->pSPIx->CR2 & (1<<SPI_CR2_TXEIE);

	if (temp1 && temp2) {
		spi_txe_interrupt_handle(pHandle);
	}
	//1. Check for RXE
	temp1 = pHandle->pSPIx->SR & (1<< SPI_SR_RXNE);
		//2. Check for RXNEIE
	temp2 = pHandle->pSPIx->CR2 & (1<<SPI_CR2_RXNEIE);
	if (temp1 && temp2) {
			spi_rnxe_interrupt_handle(pHandle);
		}
	// Handle ERRIE
	// FOR OVR flag
	//1. Check for RXE
		temp1 = pHandle->pSPIx->SR & (1<< SPI_SR_OVR);
			//2. Check for RXNEIE
		temp2 = pHandle->pSPIx->CR2 & (1<<SPI_CR2_ERRIE);
		if (temp1 && temp2) {
				spi_ovr_err_interrupt_handle(pHandle);
			}

}


/*
 * Other Peripheral Control API's
 * */

uint8_t SPI_GetFlagStatus(SPI_RegDef_t *pSPIx, uint32_t FlagName) {

	if (pSPIx->SR & FlagName) {
		return FLAG_SET;
	}
	return FLAG_RESET;
}

void SPI_Peripheral_Control(SPI_RegDef_t *pSPIx, uint8_t EnorDi) {
	if (EnorDi == ENABLE) {
		pSPIx->CR1 |= (1<<SPI_CR1_SPE);
	} else {
		pSPIx->CR1 &= ~(1<<SPI_CR1_SPE);
	}
}

void SPI_SSIConfig(SPI_RegDef_t *pSPIx, uint8_t EnorDi) {
	if (EnorDi == ENABLE) {
		pSPIx->CR1 |= (1<<SPI_CR1_SSI);
	} else {
		pSPIx->CR1 &= ~(1<<SPI_CR1_SSI);
	}
}

void SPI_SSOEConfig(SPI_RegDef_t *pSPIx, uint8_t EnorDi) {
	if (EnorDi == ENABLE) {
		pSPIx->CR2 |= (1<<SPI_CR2_SSOE);
	} else {
		pSPIx->CR2 &= ~(1<<SPI_CR2_SSOE);
	}
}

void SPI_ClearOVRFLag(SPI_RegDef_t *pSPIx) {
	uint8_t temp;
		//1. Clear the OVR flag. It is cleared by reading DR register and the reading SR register(refer OVR documentation)
			temp = pSPIx->DR;
			temp = pSPIx->SR;

			(void)temp;
}
void SPI_CloseTransmission(SPI_Handle_t *pSPIHandle){
	pSPIHandle->pSPIx->CR2 &= ~(1<<SPI_CR2_TXEIE); // This prevents interrupts from setting up the TXE flag
						pSPIHandle->pTxBuffer = NULL;
						pSPIHandle->Tx_Len = 0;
						pSPIHandle->TxState = SPI_READY;
						SPI_ApplicationEventCallback(pSPIHandle, SPI_EVENT_TX_CMPLT);
}
void SPI_CloseReception(SPI_Handle_t *pSPIHandle){
	pSPIHandle->pSPIx->CR2 &= ~(1<<SPI_CR2_RXNEIE); // This prevents interrupts from setting up the TXE flag
									pSPIHandle->pRxBuffer = NULL;
									pSPIHandle->Rx_Len = 0;
									pSPIHandle->RxState = SPI_READY;
									SPI_ApplicationEventCallback(pSPIHandle, SPI_EVENT_RX_CMPLT);
}



__attribute__((weak))void SPI_ApplicationEventCallback(SPI_Handle_t *pSPIHandle, uint8_t applicationEvent) {
	// This function will be implemented by application.
}
