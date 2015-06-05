/******************** (C) COPYRIGHT 2014 ANO Tech ***************************
 * ����		 �������ƴ�
 * �ļ���  ��ANO_Scheduler.cpp
 * ����    ��������
 * ����    ��www.anotc.com
 * �Ա�    ��anotc.taobao.com
 * ����QȺ ��190169595
**********************************************************************************/
#include "ANO_Scheduler.h"

ANO_Scheduler scheduler;


static void ANO_Loop_1000Hz(void)	//1msִ��һ��
{
	rc.DataGet();
}

static void ANO_Loop_500Hz(void)	//2msִ��һ��
{	
	//���´���������	
	imu.updateSensor();		
	
	//�����������̬
	imu.getAttitude();	
}

static void ANO_Loop_200Hz(void)	//5msִ��һ��
{
	rc.DataCalculate();
}

static void ANO_Loop_100Hz(void)	//10msִ��һ��
{
	rc.KeyCheck();
}

static void ANO_Loop_30Hz(void)	//30msִ��һ��
{
	dt.Data_Exchange();
}

void ANO_Loop(void)
{
	
	//����Ƿ��н��յ���������
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
