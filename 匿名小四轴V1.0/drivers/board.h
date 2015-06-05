
#ifndef __BOARD_H__
#define __BOARD_H__

#include "stm32f10x.h"
#include "string.h"
#include "ANO_Math.h"

#define ARMAPI extern "C"

/***************LED GPIO定义******************/
#define ANO_RCC_LED			RCC_APB2Periph_GPIOA
#define ANO_GPIO_LED		GPIOA
#define ANO_Pin_LED			GPIO_Pin_15
/*********************************************/
/***************I2C GPIO定义******************/
#define ANO_GPIO_I2C	GPIOB
#define I2C_Pin_SCL		GPIO_Pin_10
#define I2C_Pin_SDA		GPIO_Pin_11
#define ANO_RCC_I2C		RCC_APB2Periph_GPIOB
/*********************************************/
/***************SPI GPIO定义******************/
#define ANO_GPIO_SPI		GPIOA
#define ANO_GPIO_CE			GPIOB
#define SPI_Pin_CSN			GPIO_Pin_4
#define SPI_Pin_SCK			GPIO_Pin_5
#define SPI_Pin_MISO		GPIO_Pin_6
#define SPI_Pin_MOSI		GPIO_Pin_7
#define SPI_Pin_CE			GPIO_Pin_5
#define RCC_GPIO_SPI		RCC_APB2Periph_GPIOA
#define RCC_GPIO_CE			RCC_APB2Periph_GPIOB
/*********************************************/

/***************硬件中断优先级******************/
#define NVIC_UART_P	5
#define NVIC_UART_S	1
/***********************************************/

#include "ANO_Config.h"
#include "ANO_Drv_LED.h"
#include "ANO_Drv_SPI.h"
#include "ANO_Drv_I2C_soft.h"
#include "ANO_Drv_MPU6050.h"
#include "ANO_Drv_Nrf24l01.h"
#include "ANO_Drv_PWM.h"
#include "ANO_Drv_EEPROM.h"

void ANO_Quadcopter_board_Init(void);
void SysTick_IRQ(void);
uint32_t GetSysTime_us(void);


#endif /* __BOARD_H__ */

// 




