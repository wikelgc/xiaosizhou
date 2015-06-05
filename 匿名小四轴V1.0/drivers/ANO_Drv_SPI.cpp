/******************** (C) COPYRIGHT 2014 ANO Tech ***************************
 * 作者		 ：匿名科创
 * 文件名  ：ANO_Drv_SPI.cpp
 * 描述    ：SPI
 * 官网    ：www.anotc.com
 * 淘宝    ：anotc.taobao.com
 * 技术Q群 ：190169595
**********************************************************************************/
#include "board.h"
#include "ANO_Drv_SPI.h"


void ANO_SPI::Init(void)
{
	SPI_InitTypeDef SPI_InitStructure; 
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_GPIO_SPI, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_GPIO_CE, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE); 

	/*配置 SPI_NRF_SPI的 SCK,MISO,MOSI引脚 */ 
	GPIO_InitStructure.GPIO_Pin = SPI_Pin_SCK| SPI_Pin_MISO| SPI_Pin_MOSI; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //复用功能 
	GPIO_Init(ANO_GPIO_SPI, &GPIO_InitStructure);
	/*配置SPI_NRF_SPI的CE引脚，和SPI_NRF_SPI的 CSN 引脚:*/
	GPIO_InitStructure.GPIO_Pin = SPI_Pin_CE; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_Init(ANO_GPIO_CE, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = SPI_Pin_CSN; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_Init(ANO_GPIO_SPI, &GPIO_InitStructure);	
	
	GPIO_SetBits(ANO_GPIO_SPI, SPI_Pin_CSN);
	
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex; //双线全双工 
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master; //主模式 
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b; //数据大小8位 
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low; //时钟极性，空闲时为低 
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge; //第1个边沿有效，上升沿为采样时刻 
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft; //NSS信号由软件产生 
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8; //8分频，9MHz 
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB; //高位在前 
	SPI_InitStructure.SPI_CRCPolynomial = 7; 
	SPI_Init(SPI1, &SPI_InitStructure); 
	/* Enable SPI1 */ 
	SPI_Cmd(SPI1, ENABLE);



// 	SPI_InitTypeDef SPI_InitStructure; 
// 	GPIO_InitTypeDef GPIO_InitStructure;
// 	
// 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
// 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
// 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
// 	 
// 	/*配置 SPI_NRF_SPI的 SCK,MISO,MOSI引脚，GPIOA^5,GPIOA^6,GPIOA^7 */ 
// 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7; 
// 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; 
// 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //复用功能 
// 	GPIO_Init(GPIOA, &GPIO_InitStructure);
// 	/*配置SPI_NRF_SPI的CE引脚，和SPI_NRF_SPI的 CSN 引脚:*/
// 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5; 
// 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; 
// 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
// 	GPIO_Init(GPIOB, &GPIO_InitStructure);
// 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4; 
// 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; 
// 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
// 	GPIO_Init(GPIOA, &GPIO_InitStructure);	
// 	
// 	GPIO_SetBits(ANO_GPIO_SPI, SPI_Pin_CSN);
// 	
// 	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex; //双线全双工 
// 	SPI_InitStructure.SPI_Mode = SPI_Mode_Master; //主模式 
// 	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b; //数据大小8位 
// 	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low; //时钟极性，空闲时为低 
// 	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge; //第1个边沿有效，上升沿为采样时刻 
// 	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft; //NSS信号由软件产生 
// 	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8; //8分频，9MHz 
// 	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB; //高位在前 
// 	SPI_InitStructure.SPI_CRCPolynomial = 7; 
// 	SPI_Init(SPI1, &SPI_InitStructure); 
// 	/* Enable SPI1 */ 
// 	SPI_Cmd(SPI1, ENABLE);
	
}

u8 ANO_SPI::RW(u8 dat) 
{ 
	/* 当 SPI发送缓冲器非空时等待 */ 
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET); 
	/* 通过 SPI2发送一字节数据 */ 
	SPI_I2S_SendData(SPI1, dat); 
	/* 当SPI接收缓冲器为空时等待 */ 
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET); 
	/* Return the byte read from the SPI bus */ 
	return SPI_I2S_ReceiveData(SPI1); 
}


void ANO_SPI::CE_H(void)
{
	GPIO_SetBits(ANO_GPIO_CE, SPI_Pin_CE);
}

void ANO_SPI::CE_L(void)
{
	GPIO_ResetBits(ANO_GPIO_CE, SPI_Pin_CE);
}

void ANO_SPI::CSN_H(void)
{
	GPIO_SetBits(ANO_GPIO_SPI, SPI_Pin_CSN);
}

void ANO_SPI::CSN_L(void)
{
	GPIO_ResetBits(ANO_GPIO_SPI, SPI_Pin_CSN);
}



/******************* (C) COPYRIGHT 2014 ANO TECH *****END OF FILE************/
