/*
 * stm32f407xx.h
 *
 *  Created on: Aug 22, 2024
 *      Author: dineshbobburu
 */

#ifndef INC_STM32F407XX_H_
#define INC_STM32F407XX_H_
#include <stdint.h>
#include<stddef.h>

/*******************************START: Processor Specific Details***************************
 * ARM Cortex M4 NVIC ISERx register Address
 *
 * */
#define NVIC_ISER0   			((volatile uint32_t*)0xE000E100)
#define NVIC_ISER1   			((volatile uint32_t*)0xE000E104)
#define NVIC_ISER2   			((volatile uint32_t*)0xE000E108)
#define NVIC_ISER3   			((volatile uint32_t*)0xE000E100c)


/* ARM Cortex M4 NVIC ICERx register Address
 *
 * */
#define NVIC_ICER0   			((volatile uint32_t*)0xE000E180)
#define NVIC_ICER1   			((volatile uint32_t*)0xE000E184)
#define NVIC_ICER2   			((volatile uint32_t*)0xE000E188)
#define NVIC_ICER3   			((volatile uint32_t*)0xE000E18c)


/*
 * ARM Cortex Mx Processor Priority Register Address Calculation
 *
 * */
#define NVIC_PR_BASE_ADDR 		((volatile uint32_t*)0xE000E400)



#define NO_PR_BITS_IMPLEMENTED 	4



/*
 *
 * base addresses of Flash and SRAM memories
 * */

#define FLASH_BASEADDR 0x08000000U	// Flash(main) Memory Base Address
#define SRAM1_BASEADDR 0x20000000U	// SRAM1 BAse Address
#define SRAM2_BASEADDR 0x20001C00U  // SRAM1+(112*1024)
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
#define SPI4_BASEADDR  (APB2PERIPH_BASEADDR + 0x3400)
#define USART1_BASEADDR (APB2PERIPH_BASEADDR + 0x1000)
#define USART6_BASEADDR (APB2PERIPH_BASEADDR + 0x1400)
#define SYSCFG_BASEADDR (APB2PERIPH_BASEADDR + 0x3800)

/************PERIPHERAL REGISTER DEFINITION STRUCTURES**************/
/*
 * NOTE: Registers of a peripheral are specific to MCU, Please check Device Reference manual
 * */

/*
 *
 * Peripheral definition structure for GPIO
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

/*
 *
 * Peripheral definition structure for RCC
 * */

typedef struct {
	volatile uint32_t CR;
	volatile uint32_t PLLCFGR;
	volatile uint32_t CFGR;
	volatile uint32_t CIR;
	volatile uint32_t AHB1RSTR;
	volatile uint32_t AHB2RSTR;
	volatile uint32_t AHB3RSTR;
	uint32_t RESERVED0;
	volatile uint32_t APB1RSTR;
	volatile uint32_t APB2RSTR;
	uint32_t RESERVED1[2];
	volatile uint32_t AHB1ENR;
	volatile uint32_t AHB2ENR;
	volatile uint32_t AHB3ENR;
	uint32_t RESERVED2;
	volatile uint32_t APB1ENR;
	volatile uint32_t APB2ENR;
	uint32_t RESERVED3[2];
	volatile uint32_t AHB1LPENR;
	volatile uint32_t AHB2LPENR;
	volatile uint32_t AHB3LPENR;
	uint32_t RESERVED4;
	volatile uint32_t APB1LPENR;
	volatile uint32_t APB2LPENR;
	uint32_t RESERVED5[2];
	volatile uint32_t BDCR;
	volatile uint32_t CSR;
	uint32_t RESERVED6[2];
	volatile uint32_t SSCGR;
	volatile uint32_t PLLI2SCFGR;
} RCC_RegDef_t;


/*
 *
 * Peripheral definition structure for EXTI
 * */
typedef struct {
	volatile uint32_t IMR;
	volatile uint32_t EMR;
	volatile uint32_t RTSR;
	volatile uint32_t FTSR;
	volatile uint32_t SWIER;
	volatile uint32_t PR;
}EXTI_RegDef_t;



/*
 *
 * Peripheral definition structure for EXTI
 * */
typedef struct {
	volatile uint32_t MEMRMP;
	volatile uint32_t PMC;
	volatile uint32_t EXTICR[4];
	uint32_t RESERVED0[2];
	volatile uint32_t CMPCR;
	uint32_t RESERVED1[2];
	volatile uint32_t CFGR;
}SYSCFG_RegDef_t;



/*
 * Peripheral definition structure for SPI
 * */

typedef struct {
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t SR;
	volatile uint32_t DR;
	volatile uint32_t CRCPR;
	volatile uint32_t RXCRCR;
	volatile uint32_t TXCRCR;
	volatile uint32_t I2sCFGR;
	volatile uint32_t I2SPR;
}SPI_RegDef_t;



/*
 * Peripheral definition structure for I2C
 * */

typedef struct {
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t OAR1;
	volatile uint32_t OAR2;
	volatile uint32_t DR;
	volatile uint32_t SR1;
	volatile uint32_t SR2;
	volatile uint32_t CCR;
	volatile uint32_t TRISE;
	volatile uint32_t FLTR;

}I2C_RegDef_t;



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

#define EXTI ((EXTI_RegDef_t*)EXTI_BASEADDR)

#define SYSCFG ((SYSCFG_RegDef_t*)SYSCFG_BASEADDR)


#define SPI1	((SPI_RegDef_t*)SPI1_BASEADDR)
#define SPI2	((SPI_RegDef_t*)SPI2_BASEADDR)
#define SPI3	((SPI_RegDef_t*)SPI3_BASEADDR)


#define I2C1 	((I2C_RegDef_t*)I2C1_BASEADDR)
#define I2C2 	((I2C_RegDef_t*)I2C2_BASEADDR)
#define I2C3 	((I2C_RegDef_t*)I2C3_BASEADDR)


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
 * Macros to disable SPIx Peripherals
 * */
#define SPI1_RESET()					do{(RCC->APB2RSTR |= (1<<12)); (RCC->APB2RSTR &= ~(1<<12));}while(0)
#define SPI2_RESET()					do{(RCC->APB1RSTR |= (1<<14)); (RCC->APB1RSTR &= ~(1<<14));}while(0)
#define SPI3_RESET()					do{(RCC->APB1RSTR |= (1<<15)); (RCC->APB1RSTR &= ~(1<<15));}while(0)
/*
 * Returns port code for given GPIOx base address
 * */
#define GPIO_BASEADDR_TO_CODE(x) 		((x == GPIOA) ? 0 :\
										(x == GPIOB) ? 1 :\
										(x == GPIOC) ? 2 :\
										(x == GPIOD) ? 3 :\
										(x == GPIOE) ? 4 :\
										(x == GPIOF) ? 5 :\
										(x == GPIOG) ? 6 :\
										(x == GPIOH) ? 7 :0)


/*
 * IRQ Number Definitions
 * */
// GPIO IRQ Definitions
#define IRQ_NO_EXTI0			6
#define IRQ_NO_EXTI1			7
#define IRQ_NO_EXTI2			8
#define IRQ_NO_EXTI3			9
#define IRQ_NO_EXTI4			10
#define IRQ_NO_EXTI9_5			23
#define IRQ_NO_EXTI15_10		40


// SPI IRQ Definitions







/*
 * Some Generic Macros
 * */
#define ENABLE 			1
#define DISABLE 		0
#define SET 			ENABLE
#define RESET 			DISABLE
#define GPIO_PIN_SET	SET
#define GPIO_PIN_RESET  RESET
#define FLAG_RESET		RESET
#define FLAG_SET		SET





/*
 * Bit Position definitions of SPI Peripheral
 *
 * */

/*
 * SPI CR1 BIT POSITION MACROS
 * */
#define SPI_CR1_CHPA		0
#define SPI_CR1_CPOL		1
#define SPI_CR1_MSTR		2
#define SPI_CR1_BR2_0		3
#define SPI_CR1_SPE			6
#define SPI_CR1_LSBFIRST	7
#define SPI_CR1_SSI			8
#define SPI_CR1_SSM			9
#define SPI_CR1_RXONLY		10
#define SPI_CR1_DFF			11
#define SPI_CR1_CRCNEXT		12
#define SPI_CR1_CRCEN		13
#define SPI_CR1_BIDIOE		14
#define SPI_CR1_BIDIMODE	15

/*
 * SPI CR2 BIT POSITION MACROS
 * */
#define SPI_CR2_RXDMAEN		0
#define SPI_CR2_TXDMAEN		1
#define SPI_CR2_SSOE		2
#define SPI_CR2_FRF			4
#define SPI_CR2_ERRIE		5
#define SPI_CR2_RXNEIE		6
#define SPI_CR2_TXEIE		7

/*
 * SPI SR BIT POSITION MACROS
 * */
#define SPI_SR_RXNE			0
#define SPI_SR_TXE			1
#define SPI_SR_CHSIDE		2
#define SPI_SR_UDR			3
#define SPI_SR_CRCERR		4
#define SPI_SR_MODF			5
#define SPI_SR_OVR			6
#define SPI_SR_BSY			7
#define SPI_SR_FRE			8





/*
 * Bit Position definitions of I2C Peripheral
 *
 * */

/*
 * CR1 Bit Positions
 * */

#define I2C_CR1_PE			0
#define I2C_CR1_SMBUS		1
#define I2C_CR1_SMBTYPE		3
#define I2C_CR1_ENARP		4
#define I2C_CR1_ENPEC		5
#define I2C_CR1_ENGC		6
#define I2C_CR1_NOSTRETCH	7
#define I2C_CR1_START		8
#define I2C_CR1_STOP		9
#define I2C_CR1_ACK			10
#define I2C_CR1_POS			11
#define I2C_CR1_PEC			12
#define I2C_CR1_ALERT		13
#define I2C_CR1_SWRST		15



/*
 * CR2 Bit Positions
 * */

#define I2C_CR2_5_0		0
#define I2C_CR2_ITERREN 8
#define I2C_CR2_ITEVTEN 9
#define I2C_CR2_ITBUFEN 10
#define I2C_CR2_DMAEN	11
#define I2C_CR2_LAST	12


/*
 * SR1 Bit Positions
 * */
#define I2C_SR1_SB		0
#define I2C_SR1_ADDR	1
#define I2C_SR1_BTF		2
#define I2C_SR1_ADD10	3
#define I2C_SR1_STOPF	4
#define I2C_SR1_RXNE	6
#define I2C_SR1_TXE		7
#define I2C_SR1_BERR	8
#define I2C_SR1_ARLO	9
#define I2C_SR1_AF		10
#define I2C_SR1_OVR		11
#define I2C_SR1_PECERR	12
#define I2C_SR1_TIMEOUT	14
#define I2C_SR1_SMB_ALERT 15

/*
 * SR2 Bit Positions
 * */
#define I2C_SR2_MSL			0
#define I2C_SR2_BUSY		1
#define I2C_SR2_TRA			2
#define I2C_SR2_GEN_CALL	4
#define I2C_SR2_SMBDE_FAULT	5
#define I2C_SR2_SMB_HOST	6
#define I2C_SR2_DUALF		7
#define I2C_SR2_PEC_15_8	8



#include "stm32f407xx_gpio_driver.h"
#include "stm32f407xx_spi_driver.h"
#include"stm32f407xx_i2c_driver.h"


/*
 * SPI Related Clock Enable and Disable Macros
 * */





#endif /* INC_STM32F407XX_H_ */
