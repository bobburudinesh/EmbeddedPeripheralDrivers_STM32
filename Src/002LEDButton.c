/*
 * 002LEDButton.c
 *
 *  Created on: Aug 24, 2024
 *      Author: dineshbobburu
 */


#include "stm32f407xx.h"

void delay(void) {
	for(uint32_t i = 0; i<500000/2; i++);
}

int main(void) {
	GPIO_Handle_t  GpioLED;
	GPIO_Handle_t  GpioSwitch;
	GpioLED.pGPIOx = GPIOD;
	GpioLED.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;
	GpioLED.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GpioLED.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GpioLED.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	GpioLED.GPIO_PinConfig.GPIO_PinpupdControl = GPIO_NO_PUPD;


	GpioSwitch.pGPIOx = GPIOA;
	GpioSwitch.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_0;
	GpioSwitch.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
	GpioSwitch.GPIO_PinConfig.GPIO_PinSpeeed = GPIO_SPEED_FAST;
	GpioSwitch.GPIO_PinConfig.GPIO_PinpupdControl = GPIO_NO_PUPD;
	GPIO_PeriClockControl(GPIOD, ENABLE);
	GPIO_PeriClockControl(GPIOA, ENABLE);
	GPIO_Init(&GpioLED);
	GPIO_Init(&GpioSwitch);

	while(1) {
		delay();
		if (GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_NO_0)) {
			GPIO_ToggleOutputPin(GPIOD, GPIO_PIN_NO_12);
		}


	}

	return 0;
}
