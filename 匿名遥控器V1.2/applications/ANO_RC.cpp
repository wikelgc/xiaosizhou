/************************ (C) COPYRIGHT 2014 ANO Tech ******************************
 * 作者		 ：匿名科创
 * 文件名  ：ANO_RC.cpp
 * 描述    ：遥控通道数据处理
 * 官网    ：www.anotc.com
 * 淘宝    ：anotc.taobao.com
 * 技术Q群 ：190169595
**********************************************************************************/
#include "ANO_RC.h"

ANO_RC rc;

ANO_RC::ANO_RC()
{
	Init();
}

void ANO_RC::Init(void)
{
	DataRaw[ROLL] = 1500;
	DataRaw[PITCH] = 1500;
	DataRaw[YAW] = 1500;
}

void ANO_RC::DataGet(void)
{
	DataRaw[ROLL] = DataRaw[ROLL] * 0.99 + (float)ADC_ConvertedValue[3] * 0.01;
	DataRaw[PITCH] = DataRaw[PITCH] * 0.99 + (float)ADC_ConvertedValue[2] * 0.01;
	DataRaw[YAW] = DataRaw[YAW] * 0.99 + (float)ADC_ConvertedValue[1] * 0.01;
	DataRaw[THROTTLE] = DataRaw[THROTTLE] * 0.99 + (float)ADC_ConvertedValue[0] * 0.01;
	KeyDataRawL = (float)ADC_ConvertedValue[5];
	KeyDataRawR = (float)ADC_ConvertedValue[6];
}

void ANO_RC::DataCalculate(void)
{
	if(ano.f.STICKMODE)
	{
		Data[ROLL] = (u16)(1000 - DataRaw[ROLL]/2 + 1000) - DataTrim[ROLL];	
		Data[ROLL] =	(Data[ROLL] - 1500) * 0.8 +1500;
		Data[PITCH] = (u16)(DataRaw[PITCH]/2 + 1000) - DataTrim[PITCH];	
		Data[PITCH] =	(Data[PITCH] - 1500) * 0.8 +1500;
	}
	else if(ano.f.ACCELMODE)
	{
		Data[ROLL] =  constrain_int16(imu.angle.x * 10, -500, +500) * 0.8 + 1500;
		Data[PITCH] = constrain_int16(imu.angle.y * 10, -500, +500) * 0.8 + 1500;
	}
	
	Data[YAW] = (u16)(1000 - DataRaw[YAW]/2  + 1000) - DataTrim[YAW];		
	Data[YAW] =	(Data[YAW] - 1500) * 0.8 +1500;
	Data[THROTTLE] = (u16)(DataRaw[THROTTLE]/2 + 1000) - DataTrim[THROTTLE];		
	Data[THROTTLE] =	(Data[THROTTLE] - 1500) * 0.85 +1500;
	
	KeyDataL = (u16)KeyDataRawL;
	KeyDataR = (u16)KeyDataRawR;
}

void ANO_RC::KeyCheck(void)
{
	static u8 keyFlagL = 1, keyFlagR = 1;
	static u8 timeDelayFlag = 0;
	
	if(timeDelayFlag)
		timeDelayFlag --;	
	
	if(KeyDataL<100 && keyFlagL)	//THR+
	{
		if(!timeDelayFlag)
			timeDelayFlag = 10;
		
		if((KeyDataL<100 && keyFlagL) && timeDelayFlag == 1)	
		{
			DataTrim[THROTTLE] -= 2;
			param.SAVE_RC_OFFSET();
			keyFlagL = 0;		
		}
	}
	else if(KeyDataL>1950 && KeyDataL<2100 && keyFlagL)	//YAW-
	{
		if(!timeDelayFlag)
			timeDelayFlag = 10;
		
		if(KeyDataL>1950 && KeyDataL<2100 && timeDelayFlag == 1)
		{
			DataTrim[YAW] += 2;
			param.SAVE_RC_OFFSET();
			keyFlagL = 0;		
		}
	}
	else if(KeyDataL>2650 && KeyDataL<2750 && keyFlagL)	//THR-
	{
		if(!timeDelayFlag)
			timeDelayFlag = 10;
		
		if(KeyDataL>2650 && KeyDataL<2750 && timeDelayFlag == 1)
		{
			DataTrim[THROTTLE] += 2;
			param.SAVE_RC_OFFSET();
			keyFlagL = 0;		
		}
	}
	else if(KeyDataL>3000 && KeyDataL<3100 && keyFlagL)	//YAW+
	{
		if(!timeDelayFlag)
			timeDelayFlag = 10;
		
		if(KeyDataL>3000 && KeyDataL<3100 && timeDelayFlag == 1)
		{
			DataTrim[YAW] -= 2;
			param.SAVE_RC_OFFSET();
			keyFlagL = 0;
		}
	}
	else if(KeyDataL>3200 && KeyDataL<3300 && keyFlagL)
	{
		if(!timeDelayFlag)
			timeDelayFlag = 10;
		
		if(KeyDataL>3200 && KeyDataL<3300 && keyFlagL && timeDelayFlag == 1)
		{
			if(ano.f.STICKMODE)
			{
				ano.f.STICKMODE = 0;
				ano.f.ACCELMODE = 1;
			}
			else if(ano.f.ACCELMODE)
			{
				ano.f.STICKMODE = 1;
				ano.f.ACCELMODE = 0;
			}
			keyFlagL = 0;
		}
	}	
	else if(KeyDataL>4050)
	{
		keyFlagL = 1;
	}
	
	
	if(KeyDataR<100 && keyFlagR)	//PITCH+
	{
		if(!timeDelayFlag)
			timeDelayFlag = 10;
		
		if(KeyDataR<100 && keyFlagR && timeDelayFlag == 1)
		{
			DataTrim[PITCH] -= 2;
			param.SAVE_RC_OFFSET();
			keyFlagR = 0;		
		}
	}
	else if(KeyDataR>1900 && KeyDataR<2100 && keyFlagR)	//ROLL+
	{
		if(!timeDelayFlag)
			timeDelayFlag = 10;
		
		if(KeyDataR>1900 && KeyDataR<2100 && keyFlagR && timeDelayFlag == 1)
		{
			DataTrim[ROLL] -= 2;
			param.SAVE_RC_OFFSET();
			keyFlagR = 0;		
		}
	}
	else if(KeyDataR>2600 && KeyDataR<2800 && keyFlagR)	//PITCH-
	{
		if(!timeDelayFlag)
			timeDelayFlag = 10;
		
		if(KeyDataR>2600 && KeyDataR<2800 && keyFlagR && timeDelayFlag == 1)
		{
			DataTrim[PITCH] += 2;
			param.SAVE_RC_OFFSET();
			keyFlagR = 0;	
		}			
	}
	else if(KeyDataR>2950 && KeyDataR<3150 && keyFlagR)	//ROLL-
	{
		if(!timeDelayFlag)
			timeDelayFlag = 10;
		
		if(KeyDataR>2950 && KeyDataR<3150 && keyFlagR && timeDelayFlag == 1)
		{
			DataTrim[ROLL] += 2;
			param.SAVE_RC_OFFSET();
			keyFlagR = 0;
		}
	}
	else if(KeyDataR>3200 && KeyDataR<3300 && keyFlagR)
	{
		if(!timeDelayFlag)
			timeDelayFlag = 10;
		
		if(KeyDataR>3200 && KeyDataR<3300 && keyFlagR && timeDelayFlag == 1)
		{
		}
	}
	else if(KeyDataR>3350 && KeyDataR<3450 && keyFlagR)
	{
		if(!timeDelayFlag)
			timeDelayFlag = 10;
		
		if(KeyDataR>3350 && KeyDataR<3450 && keyFlagR && timeDelayFlag == 1)
		{

		}
	}
	else if(KeyDataR>4050)
	{
		keyFlagR = 1;
	}
	
	
}
/******************* (C) COPYRIGHT 2014 ANO TECH *****END OF FILE************/
