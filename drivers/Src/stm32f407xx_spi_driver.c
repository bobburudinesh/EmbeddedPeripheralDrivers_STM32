/*
 * stm32f407xx_spi_driver.c
 *
 *  Created on: Aug 26, 2024
 *      Author: dineshbobburu
 */
#include "stm32f407xx_spi_driver.h"


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
		while((pSPIx->SR & (1<<SPI_SR_TXE))) { // checking if tx buffer is empty else we habe to wait
			if(pSPIx->CR1 & (1<<SPI_CR1_DFF)) { //
				// 16 bit data frame
				pSPIx->DR = *((uint16_t*)pTxBuffer);
				length--;
				(uint16_t*)pTxBuffer++;
			} else {
				// 8 bit data frame
				pSPIx->DR = *pTxBuffer;
				pTxBuffer++;
			}
			length--;

		}
	}
}

void SPI_ReceiveData(SPI_RegDef_t *pSPIx, uint8_t  *pRxBuffer, uint32_t length);

/*
 * IRQ Configuration and ISR HAndling
 * */
void SPI_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi);
void SPI_IRQPriorityConfig(uint8_t IRQNumber,uint8_t IRQPriority);
void SPI_IRQHandling(SPI_Handle_t *pHandle);
