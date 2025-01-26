/*
 * stm32f407xx_i2c_driver.h
 *
 *  Created on: Jan 25, 2025
 *      Author: dineshbobburu
 */

#ifndef INC_STM32F407XX_I2C_DRIVER_H_
#define INC_STM32F407XX_I2C_DRIVER_H_

/*
 * Configuration structure for I2C Peripheral
 * */
typedef struct{
	uint32_t	I2C_SCLSpeed; // refer  @I2C SCL Speed
	uint8_t		I2C_DeviceAddress;
	uint8_t		I2C_AckControl;
	uint8_t		I2C_FMDutyCycle;
}I2C_Config_t;

/*
 * Handle structure for I2C Peripheral
 * */
typedef struct {
	I2C_Config_t	I2C_Config;
	I2C_RegDef_t	*pI2Cx;
}I2C_Handle_t;


/*
 * @I2C SCL Speed
 * */

#define I2C_SCL_SPEED_SM		100000
#define I2C_SCL_SPEED_FM4K		400000
#define I2C_SCL_SPEED_FM2K		200000

/*
 * @I2C ACK Control
 * */


#define I2C_ACK_ENABLE			1
#define I2C_ACK_DISABLE			0

/*
 * @I2C FM Duty Cycle
 * */

#define I2C_FM_DUTY_2			0
#define I2C_FM_DUTY_16_9		1



/**********************************************************************************
 * API's Supported by this driver
 * For more information about the API's check the function definitions
 *************************************************************************************/

/*
 * Peripheral Clock setup
 * */

void I2C_PeriClockControl(I2C_RegDef_t *pI2Cx, uint8_t EnorDi);

/*
 * Init and DEInit
 * */
void I2C_Init(I2C_Handle_t *pI2CHandle);
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
void I2C_Peripheral_Control(I2C_RegDef_t *pI2Cx, uint8_t EnorDi);



/*
 * Application Callback
 * */

void I2C_ApplicationEventCallback(I2C_Handle_t *pI2CHandle, uint8_t applicationEvent);



#endif /* INC_STM32F407XX_I2C_DRIVER_H_ */
