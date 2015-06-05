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
	//����Ƿ��н��յ���������
	dt.Check_Event();
}

static void ANO_Loop_500Hz(void)	//2msִ��һ��
{
	//���´���������	
	imu.updateSensor();		
	
	//�����������̬
	imu.getAttitude();
	
	//��������̬�ڻ�����
	fc.Attitude_Inner_Loop();	
}

static void ANO_Loop_200Hz(void)	//5msִ��һ��
{
	//��������̬�⻷����
	fc.Attitude_Outter_Loop();	
}

static void ANO_Loop_100Hz(void)	//10msִ��һ��
{
	//���ͷ���������
	dt.Data_Exchange();
}

static void ANO_Loop_50Hz(void)	//20msִ��һ��
{
	//ң��ͨ�����ݴ���
	rc.Cal_Command();
	
	//ҡ��λ�ü��
	rc.check_sticks();
	
	//ʧ�ر������
	dt.Failsafe_Check();
	
	//LEDָʾ�ƿ���
	ano.Pilot_Light();
}

void ANO_Loop(void)
{
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
	if(scheduler.cnt_20ms >= 20){		
		ANO_Loop_50Hz();
		scheduler.cnt_20ms = 0;
	}
}

ANO_Scheduler::ANO_Scheduler()
{
	cnt_1ms = cnt_2ms = cnt_5ms = cnt_10ms = cnt_20ms	= 0;
}



/******************* (C) COPYRIGHT 2014 ANO TECH *****END OF FILE************/
