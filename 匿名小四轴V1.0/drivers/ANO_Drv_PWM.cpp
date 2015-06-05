/******************** (C) COPYRIGHT 2014 ANO Tech ***************************
 * 作者		 ：匿名科创
 * 文件名  ：ANO_Drv_PWM.cpp
 * 描述    ：PWM相关定时器
 * 官网    ：www.anotc.com
 * 淘宝    ：anotc.taobao.com
 * 技术Q群 ：190169595
**********************************************************************************/
#include "ANO_Drv_PWM.h"

ANO_PWM pwm;

void ANO_PWM::out_Init(uint16_t hz)
{
	TIM_TimeBaseInitTypeDef		TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  				TIM_OCInitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_8|GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	
	uint16_t PrescalerValue = 0;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	PrescalerValue = (uint16_t) (SystemCoreClock / 24000000) - 1;
	/* Time base configuration */
	TIM_TimeBaseStructure.TIM_Period = 999;		//计数上线	
	TIM_TimeBaseStructure.TIM_Prescaler = PrescalerValue;	//pwm时钟分频
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;	
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;		//向上计数
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
	
	/* PWM1 Mode configuration: Channel */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;//999;//初始占空比为0
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);            //GPIOA8   PWM3
	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);      
	
	TIM_OCInitStructure.TIM_Pulse = 0;//初始占空比为0
	TIM_OC4Init(TIM1, &TIM_OCInitStructure);             //GPIOA11    PWM4
	TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);	
	
	TIM_CtrlPWMOutputs(TIM1, ENABLE);
	TIM_ARRPreloadConfig(TIM1, ENABLE);
	TIM_Cmd(TIM1, ENABLE);
		
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	/* Compute the prescaler value */
	PrescalerValue = (uint16_t) (SystemCoreClock / 24000000) - 1;
	/* Time base configuration */
	TIM_TimeBaseStructure.TIM_Period = 999;		//
	TIM_TimeBaseStructure.TIM_Prescaler = PrescalerValue;	//pwm时钟分频
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;	
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;		//向上计数
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	
	/* PWM1 Mode configuration: Channel */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;//初始占空比为0
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	
	TIM_OC1Init(TIM2, &TIM_OCInitStructure);        //GPIOA0   PWM1
	TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);      
	TIM_OC2Init(TIM2, &TIM_OCInitStructure);        //GPIOA1   PWM2
	TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);
	TIM_ARRPreloadConfig(TIM2, ENABLE);
	TIM_Cmd(TIM2, ENABLE);
}



void ANO_PWM::SetPwm(uint16_t pwm[MAXMOTORS])
{
	for(u8 i=0;i<MAXMOTORS;i++)
	{
		if(pwm[i] < 1000)
			pwm[i] = 1000;
		else if(pwm[i] > 2000)
			pwm[i] = 2000;
	}
	
	TIM1->CCR4 = pwm[1] - 1000; 
	TIM2->CCR1 = pwm[3] - 1000;	
	TIM1->CCR1 = pwm[0] - 1000; 
	TIM2->CCR2 = pwm[2] - 1000;
	
}


/******************* (C) COPYRIGHT 2014 ANO TECH *****END OF FILE************/
