/*
 * stm32f407xx.h
 *
 *  Created on: Aug 22, 2024
 *      Author: dineshbobburu
 */

#ifndef INC_STM32F407XX_H_
#define INC_STM32F407XX_H_
#include <stdint.h>

/*
 *
 * base addresses of Flash and SRAM memories
 * */

#define FLASH_BASEADDR 0x08000000U
#define SRAM1_BASEADDR 0x20000000U
#define SRAM2_BASEADDR 0x20001C00U
#define ROM_BASEADDR	0x1FFF0000U
#define SRAM 			SRAM1_BASEADDR

/*
 *
 * AHBX AND APBX BUS PERIPHERAL BASE ADDRESSES
 * */

#define PERIPH_BASEADDR 	0x40000000U
#define APB1PERIPH_BASEADDR 0x40000000U
#define APB2PERIPH_BASEADDR 0x40010000U
#define AHB1PERIPH_BASEADDR 0x40020000U
#define AHB2PERIPH_BASEADDR 0x50000000U

/*
 * Base addresses of Peripherals hanging on AHB1
 * */

#define GPIOA_BASEADDR  (AHB1PERIPH_BASEADDR + 0x0000)
#define GPIOB_BASEADDR  (AHB1PERIPH_BASEADDR + 0x0400)
#define GPIOC_BASEADDR  (AHB1PERIPH_BASEADDR + 0x0800)
#define GPIOD_BASEADDR  (AHB1PERIPH_BASEADDR + 0x0C00)
#define GPIOE_BASEADDR  (AHB1PERIPH_BASEADDR + 0x1000)
#define GPIOF_BASEADDR  (AHB1PERIPH_BASEADDR + 0x1400)
#define GPIOG_BASEADDR  (AHB1PERIPH_BASEADDR + 0x1800)
#define GPIOH_BASEADDR  (AHB1PERIPH_BASEADDR + 0x1C00)
#define GPIOI_BASEADDR  (AHB1PERIPH_BASEADDR + 0x2000)
#define GPIOJ_BASEADDR  (AHB1PERIPH_BASEADDR + 0x2400)
#define GPIOK_BASEADDR  (AHB1PERIPH_BASEADDR + 0x2800)
#define RCC_BASEADDR	(AHB1PERIPH_BASEADDR + 0x3800)



/*
 * Base addresses of Peripherals hanging on APB1
 * */
#define I2C1_BASEADDR  (APB1PERIPH_BASEADDR + 0x5400)
#define I2C2_BASEADDR  (APB1PERIPH_BASEADDR + 0x5800)
#define I2C3_BASEADDR  (APB1PERIPH_BASEADDR + 0x5C00)

#define SPI2_BASEADDR  (APB1PERIPH_BASEADDR + 0x3800)
#define SPI3_BASEADDR  (APB1PERIPH_BASEADDR + 0x3C00)

#define USART2_BASEADDR  (APB1PERIPH_BASEADDR + 0x4400)
#define USART3_BASEADDR  (APB1PERIPH_BASEADDR + 0x4800)
#define UART4_BASEADDR  (APB1PERIPH_BASEADDR + 0x4C00)
#define UART5_BASEADDR  (APB1PERIPH_BASEADDR + 0x5000)

/*
 * Base addresses of Peripherals hanging on APB2
 * */
#define EXTI_BASEADDR (APB2PERIPH_BASEADDR + 0x3C00)
#define SPI1_BASEADDR (APB2PERIPH_BASEADDR + 0x3000)
#define USART1_BASEADDR (APB2PERIPH_BASEADDR + 0x1000)
#define USART6_BASEADDR (APB2PERIPH_BASEADDR + 0x1400)
#define SYSCFG_BASEADDR (APB2PERIPH_BASEADDR + 0x3800)

/************PERIPHERAL REGISTER DEFINITION STRUCTURES**************/
/*
 * NOTE: Registers of a peripheral are specific to MCU, Please check Device Reference manual
 * */
typedef struct {
	volatile uint32_t MODER; /*GPIO port mode register, 0x00*/
	volatile uint32_t OTYPER; /* GPIO port output type register, 0x04*/
	volatile uint32_t OSPEEDR;/* GPIO port output speed register, 0x08*/
	volatile uint32_t PUPDR; /* GPIO port pull-up/pull-down register*/
	volatile uint32_t IDR;/*GPIO port input data register*/
	volatile uint32_t ODR;/*GPIO port output data register*/
	volatile uint32_t BSRR;/*GPIO port bit set/reset register*/
	volatile uint32_t LCKR;/*GPIO port configuration lock register*/
	volatile uint32_t AFR[2];/*AFR[0]: GPIO alternate function low register, AFR[1]: GPIO alternate function high register*/
}GPIO_RegDef_t;


typedef struct {
	uint32_t CR;
	uint32_t PLLCFGR;
	uint32_t CFGR;
	uint32_t CIR;
	uint32_t AHB1RSTR;
	uint32_t AHB2RSTR;
	uint32_t AHB3RSTR;
	uint32_t RESERVED0;
	uint32_t APB1RSTR;
	uint32_t APB2RSTR;
	uint32_t RESERVED1[2];
	uint32_t AHB1ENR;
	uint32_t AHB2ENR;
	uint32_t AHB3ENR;
	uint32_t RESERVED2;
	uint32_t APB1ENR;
	uint32_t APB2ENR;
	uint32_t RESERVED3[2];
	uint32_t AHB1LPENR;
	uint32_t AHB2LPENR;
	uint32_t AHB3LPENR;
	uint32_t RESERVED4;
	uint32_t APB1LPENR;
	uint32_t APB2LPENR;
	uint32_t RESERVED5[2];
	uint32_t BDCR;
	uint32_t CSR;
	uint32_t RESERVED6[2];
	uint32_t SSCGR;
	uint32_t PLLI2SCFGR;
} RCC_RegDef_t;

/*
 * PERIPHERAL DEFINITIONS(PERIPHERAL BASE ADDRESS TYPE CASTED TO XXX_REGDEF_T)
 * */
#define GPIOA ((GPIO_RegDef_t*)GPIOA_BASEADDR)
#define GPIOB ((GPIO_RegDef_t*)GPIOB_BASEADDR)
#define GPIOC ((GPIO_RegDef_t*)GPIOC_BASEADDR)
#define GPIOD ((GPIO_RegDef_t*)GPIOD_BASEADDR)
#define GPIOE ((GPIO_RegDef_t*)GPIOE_BASEADDR)
#define GPIOF ((GPIO_RegDef_t*)GPIOF_BASEADDR)
#define GPIOG ((GPIO_RegDef_t*)GPIOG_BASEADDR)
#define GPIOH ((GPIO_RegDef_t*)GPIOH_BASEADDR)
#define GPIOI ((GPIO_RegDef_t*)GPIOI_BASEADDR)

#define RCC ((RCC_RegDef_t*)RCC_BASEADDR)

/*
 * Clock Enable for Peripherals
 * */

/*
 * Clock enable Macros for GPIOx Peripherals
 * */
#define GPIOA_PCLK_EN() (RCC->AHB1ENR |= (1<<0))
#define GPIOB_PCLK_EN() (RCC->AHB1ENR |= (1<<1))
#define GPIOC_PCLK_EN() (RCC->AHB1ENR |= (1<<2))
#define GPIOD_PCLK_EN() (RCC->AHB1ENR |= (1<<3))
#define GPIOE_PCLK_EN() (RCC->AHB1ENR |= (1<<4))
#define GPIOF_PCLK_EN() (RCC->AHB1ENR |= (1<<5))
#define GPIOG_PCLK_EN() (RCC->AHB1ENR |= (1<<6))
#define GPIOH_PCLK_EN() (RCC->AHB1ENR |= (1<<7))
#define GPIOI_PCLK_EN() (RCC->AHB1ENR |= (1<<8))


/*
 * Clock enable Macros for I2Cx Peripherals
 * */
#define I2C1_PCLK_EN() (RCC->APB1ENR |= (1<<21))
#define I2C2_PCLK_EN() (RCC->APB1ENR |= (1<<22))
#define I2C3_PCLK_EN() (RCC->APB1ENR |= (1<<23))



/*
 * Clock enable Macros for SPIx Peripherals
 * */

#define SPI1_PCLK_EN() (RCC->APB2ENR |= (1<<12))
#define SPI2_PCLK_EN() (RCC->APB1ENR |= (1<<14))
#define SPI3_PCLK_EN() (RCC->APB1ENR |= (1<<15))

/*
 * Clock enable Macros for USARTx Peripherals
 * */
#define USART1_PCLK_EN() (RCC->APB2ENR |= (1<<4))
#define USART2_PCLK_EN() (RCC->APB1ENR |= (1<<17))
#define USART3_PCLK_EN() (RCC->APB1ENR |= (1<<18))
#define USART6_PCLK_EN() (RCC->APB2ENR |= (1<<5))



/*
 * Clock enable Macros for UARTx Peripherals
 * */

#define UART4_PCLK_EN() (RCC->APB1ENR |= (1<<19))
#define UART5_PCLK_EN() (RCC->APB1ENR |= (1<<20))

/*
 * Clock enable Macros for SYSCFG Peripherals
 * */

#define SYSCFG_PCLK_EN() (RCC->APB2ENR |= (1<<14))


/*
 * Clock Disable for Peripherals
 * */

/*
 * Clock disable Macros for GPIOx Peripherals
 * */
#define GPIOA_PCLK_DI() (RCC->AHB1ENR &= ~(1<<0))
#define GPIOB_PCLK_DI() (RCC->AHB1ENR &= ~(1<<1))
#define GPIOC_PCLK_DI() (RCC->AHB1ENR &= ~(1<<2))
#define GPIOD_PCLK_DI() (RCC->AHB1ENR &= ~(1<<3))
#define GPIOE_PCLK_DI() (RCC->AHB1ENR &= ~(1<<4))
#define GPIOF_PCLK_DI() (RCC->AHB1ENR &= ~(1<<5))
#define GPIOG_PCLK_DI() (RCC->AHB1ENR &= ~(1<<6))
#define GPIOH_PCLK_DI() (RCC->AHB1ENR &= ~(1<<7))
#define GPIOI_PCLK_DI() (RCC->AHB1ENR &= ~(1<<8))


/*
 * Clock disable Macros for I2Cx Peripherals
 * */
#define I2C1_PCLK_DI() (RCC->APB1ENR &= ~(1<<21))
#define I2C2_PCLK_DI() (RCC->APB1ENR &= ~(1<<22))
#define I2C3_PCLK_DI() (RCC->APB1ENR &= ~(1<<23))



/*
 * Clock disable Macros for SPIx Peripherals
 * */

#define SPI1_PCLK_DI() (RCC->APB2ENR &= ~(1<<12))
#define SPI2_PCLK_DI() (RCC->APB1ENR &= ~(1<<14))
#define SPI3_PCLK_DI() (RCC->APB1ENR &= ~(1<<15))

/*
 * Clock disable Macros for USARTx Peripherals
 * */
#define USART1_PCLK_DI() (RCC->APB2ENR &= ~(1<<4))
#define USART2_PCLK_DI() (RCC->APB1ENR &= ~(1<<17))
#define USART3_PCLK_DI() (RCC->APB1ENR &= ~(1<<18))
#define USART6_PCLK_DI() (RCC->APB2ENR &= ~(1<<5))



/*
 * Clock disable Macros for UARTx Peripherals
 * */

#define UART4_PCLK_DI() (RCC->APB1ENR &= ~(1<<19))
#define UART5_PCLK_DI() (RCC->APB1ENR &= ~(1<<20))

/*
 * Clock disable Macros for SYSCFG Peripherals
 * */

#define SYSCFG_PCLK_DI() (RCC->APB2ENR &= ~(1<<14))


/*
 * Macros to disable GPIOx Peripherals
 * */
#define GPIOA_REG_RESET()			do{(RCC->AHB1RSTR |= (1<<0));	(RCC->AHB1RSTR &= ~(1<<0));} while(0)
#define GPIOB_REG_RESET()			do{(RCC->AHB1RSTR |= (1<<1));	(RCC->AHB1RSTR &= ~(1<<1));} while(0)
#define GPIOC_REG_RESET()			do{(RCC->AHB1RSTR |= (1<<2));	(RCC->AHB1RSTR &= ~(1<<2));} while(0)
#define GPIOD_REG_RESET()			do{(RCC->AHB1RSTR |= (1<<3));	(RCC->AHB1RSTR &= ~(1<<3));} while(0)
#define GPIOE_REG_RESET()			do{(RCC->AHB1RSTR |= (1<<4));	(RCC->AHB1RSTR &= ~(1<<4));} while(0)
#define GPIOF_REG_RESET()			do{(RCC->AHB1RSTR |= (1<<5));	(RCC->AHB1RSTR &= ~(1<<5));} while(0)
#define GPIOG_REG_RESET()			do{(RCC->AHB1RSTR |= (1<<6));	(RCC->AHB1RSTR &= ~(1<<6));} while(0)
#define GPIOH_REG_RESET()			do{(RCC->AHB1RSTR |= (1<<7));	(RCC->AHB1RSTR &= ~(1<<7));} while(0)
#define GPIOI_REG_RESET()			do{(RCC->AHB1RSTR |= (1<<8));	(RCC->AHB1RSTR &= ~(1<<8));} while(0)
/*
 * Some Generic Macros
 * */
#define ENABLE 			1
#define DISABLE 		0
#define SET 			ENABLE
#define RESET 			DISABLE
#define GPIO_PIN_SET	SET
#define GPIO_PIN_RESET  RESET




#include "stm32f407xx_gpio_driver.h"





#endif /* INC_STM32F407XX_H_ */
