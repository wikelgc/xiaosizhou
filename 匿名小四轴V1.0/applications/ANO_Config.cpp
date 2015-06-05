/******************** (C) COPYRIGHT 2014 ANO Tech ***************************
 * 作者		 ：匿名科创
 * 文件名  ：ANO_Config.cpp
 * 描述    ：配置文件
 * 官网    ：www.anotc.com
 * 淘宝    ：anotc.taobao.com
 * 技术Q群 ：190169595
**********************************************************************************/

#include "ANO_Config.h"

ANO_Config ano;


ANO_Config::ANO_Config(void)
{
	
}

//指示灯
void ANO_Config::Pilot_Light(void)
{
	static u8 cnt = 0;
	
	if(f.ARMED)   //解锁成功
	{
		cnt++;
		switch(cnt)
		{
			case 1:
				led.ON();
				break;
			case 25:
				led.OFF();
				break;
			case 50:
				cnt = 0;
				break;
		}
	}
	else
	{
		led.ON(); 
	}
	
}


/******************* (C) COPYRIGHT 2014 ANO TECH *****END OF FILE************/
