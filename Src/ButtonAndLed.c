/*
 * ButtonAndLed.c
 *
 *  Created on: Jan 22, 2025
 *      Author: dineshbobburu
 */


#include <stm32f407xx.h>
#include <stm32f407xx_gpio_driver.h>

void delay(void) {
	for(volatile uint32_t i = 0; i<500000/2;i++);
}

int main(void) {

	GPIO_Handle_t gpioSw, gpioLED;
	gpioSw.pGPIOx = GPIOA;
	gpioSw.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_0;
	gpioSw.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
	gpioSw.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	gpioSw.GPIO_PinConfig.GPIO_PinpupdControl = GPIO_NO_PUPD;
	//gpioSw.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	//gpioSw.GPIO_PinConfig.GPIO_PinAltFunMode = 	GPIO_MODE_IN;


	gpioLED.pGPIOx = GPIOD;
	gpioLED.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;
	gpioLED.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	gpioLED.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	gpioLED.GPIO_PinConfig.GPIO_PinpupdControl = GPIO_NO_PUPD;
	gpioLED.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	//gpioLED.GPIO_PinConfig.GPIO_PinAltFunMode = 	GPIO_MODE_IN;
	GPIO_PeriClockControl(GPIOA, ENABLE);
	GPIO_PeriClockControl(GPIOD, ENABLE);

	GPIO_Init(&gpioLED);
	GPIO_Init(&gpioSw);

	while(1) {
		delay();
		if (GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_NO_0)) {
			GPIO_ToggleOutputPin(GPIOD, GPIO_PIN_NO_12);
		}

	}





	return 0;
}
