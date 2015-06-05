/******************** (C) COPYRIGHT 2014 ANO Tech ***************************
 * 作者		 ：匿名科创
 * 文件名  ：ANO_Scheduler.cpp
 * 描述    ：任务处理
 * 官网    ：www.anotc.com
 * 淘宝    ：anotc.taobao.com
 * 技术Q群 ：190169595
**********************************************************************************/
#include "ANO_Scheduler.h"

ANO_Scheduler scheduler;


static void ANO_Loop_1000Hz(void)	//1ms执行一次
{
	rc.DataGet();
}

static void ANO_Loop_500Hz(void)	//2ms执行一次
{	
	//更新传感器数据	
	imu.updateSensor();		
	
	//计算飞行器姿态
	imu.getAttitude();	
}

static void ANO_Loop_200Hz(void)	//5ms执行一次
{
	rc.DataCalculate();
}

static void ANO_Loop_100Hz(void)	//10ms执行一次
{
	rc.KeyCheck();
}

static void ANO_Loop_30Hz(void)	//30ms执行一次
{
	dt.Data_Exchange();
}

void ANO_Loop(void)
{
	
	//检查是否有接收到无线数据
	dt.Check_Event();
	
	if(scheduler.cnt_1ms >= 1){
		ANO_Loop_1000Hz();	
		scheduler.cnt_1ms = 0;
	}
	if(scheduler.cnt_2ms >= 2){
		ANO_Loop_500Hz();
		scheduler.cnt_2ms = 0;
	}		
	if(scheduler.cnt_5ms >= 5){	
		ANO_Loop_200Hz();
		scheduler.cnt_5ms = 0;
	}
	if(scheduler.cnt_10ms >= 10){		
		ANO_Loop_100Hz();
		scheduler.cnt_10ms = 0;
	}
	if(scheduler.cnt_30ms >= 30){		
		ANO_Loop_30Hz();
		scheduler.cnt_30ms = 0;
	}
}

ANO_Scheduler::ANO_Scheduler()
{
	cnt_1ms = cnt_2ms = cnt_5ms = cnt_10ms = cnt_30ms	= 0;
}



/******************* (C) COPYRIGHT 2014 ANO TECH *****END OF FILE************/
