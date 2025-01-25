/*
 * SPI_Driver_Testing.c
 *
 *  Created on: Jan 24, 2025
 *      Author: dineshbobburu
 */

#include "stm32f407xx.h"
#include<string.h>


/*
 * PB12 - NSS
 * PB13 - SPI2_CLK
 * PB14 - SPI2_MISO
 * PB15 - SPI2_MOSI
 * */

void SPI2_GPIOInits(void) {
	GPIO_Handle_t	spi_Pins;
	spi_Pins.pGPIOx = GPIOB;
	spi_Pins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
	spi_Pins.GPIO_PinConfig.GPIO_PinAltFunMode = 5;
	spi_Pins.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	spi_Pins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	spi_Pins.GPIO_PinConfig.GPIO_PinpupdControl = GPIO_NO_PUPD;

	// init pin 12
	spi_Pins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;
	GPIO_Init(&spi_Pins);

	// init pin 13
	spi_Pins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;
	GPIO_Init(&spi_Pins);

	// init pin 14
	spi_Pins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_14;
	GPIO_Init(&spi_Pins);

	// init pin 15
	spi_Pins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_15;
	GPIO_Init(&spi_Pins);
}

void SPI2_Inits(void) {
	SPI_Handle_t spi2_Handle;

	spi2_Handle.pSPIx = SPI2;
	spi2_Handle.SPIConfig.SPI_BusConfig = SPI_BUS_CONFIG_FD;
	spi2_Handle.SPIConfig.SPI_DeviceMode = SPI_DEVICE_MODE_MASTER;
	spi2_Handle.SPIConfig.SPI_SclkSpeed = SPI_SCLK_SPEED_DIV2; // generates 8Mhz of CLK
	spi2_Handle.SPIConfig.SPI_DFF = SPI_DFF_8BITS;
	spi2_Handle.SPIConfig.SPI_CPHA = SPI_CPHA_LOW;
	spi2_Handle.SPIConfig.SPI_CPOL = SPI_CPOL_LOW;
	spi2_Handle.SPIConfig.SPI_SSM = SPI_SSM_DI; // SSM ENable the configure SSI as ENbale else Disbale SSI.

	SPI_Init(&spi2_Handle);
}

int main (void) {
	char userData[] = "Hello World!";
	// This function configures GPIO's for SPI2 peripheral
	SPI2_GPIOInits();
	//This function configures SPI2 peripheral
	SPI2_Inits();

	//::  if you are using SSE as Enable then we have configure SSI as Enable, if We are using
	//SPI_SSIConfig(SPI2, ENABLE);
	/*
	 * If we are using SSE as disable the we have to drive output through NSS pin for Slave select, for this we have to enable SSOE bit
	 * Else (if we are using SSM as Enable) comment below line
	 * */
	SPI_SSOEConfig(SPI2, ENABLE);
	while(1) {

			// Finally we have to enable SPI peripheral, this bit will be disabled by default this have to be enables once all the spi configurations are made.
			// Because once this bit is enabled SPI will be busy in communication it will not accept any changes to its control bits.
			SPI_Peripheral_Control(SPI2, ENABLE);
			// First send data length to spi slave
			uint8_t dataLength = strlen(userData);
			SPI_SendData(SPI2, &dataLength, 1);
			SPI_SendData(SPI2, (uint8_t*)userData, strlen(userData));
			// Confieming SPI is not Busy meaning it has completed data transmission
			while(SPI_GetFlagStatus(SPI2, SPI_SR_BSY));

			SPI_Peripheral_Control(SPI2, DISABLE);
	}

	return 0;

}


