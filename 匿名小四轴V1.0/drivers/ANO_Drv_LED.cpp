/******************** (C) COPYRIGHT 2014 ANO Tech ***************************
 * 作者		 ：匿名科创
 * 文件名  ：ANO_Drv_LED.cpp
 * 描述    ：LED
 * 官网    ：www.anotc.com
 * 淘宝    ：anotc.taobao.com
 * 技术Q群 ：190169595
**********************************************************************************/
#include "ANO_Drv_LED.h"

ANO_LED led;

void ANO_LED::Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(ANO_RCC_LED,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);  
	
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin   = ANO_Pin_LED;        //GPIO15
	GPIO_Init(ANO_GPIO_LED, &GPIO_InitStructure);
}

void ANO_LED::ON(void)
{
	GPIO_ResetBits(ANO_GPIO_LED, ANO_Pin_LED);	
}

void ANO_LED::OFF(void)
{
	GPIO_SetBits(ANO_GPIO_LED, ANO_Pin_LED);		
}




/******************* (C) COPYRIGHT 2014 ANO TECH *****END OF FILE************/

