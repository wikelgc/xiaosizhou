/******************** (C) COPYRIGHT 2014 ANO Tech ***************************
 * ����		 �������ƴ�
 * �ļ���  ��AnoCopter.cpp
 * ����    ������΢�����������
 * ����汾��V1.0
 * ʱ��		 ��2014/10/13 
 * ����    ��www.anotc.com
 * �Ա�    ��anotc.taobao.com
 * ����QȺ ��190169595
**********************************************************************************/
#include "ANO_Config.h"

int main(void)
{
	//��ʼ���ɿذ��Ӳ������
	ANO_Quadcopter_board_Init();
	
	//��ʼ������
	param.Init();
	
	//��ʼ��IMU�����Բ�����Ԫ��
	imu.Init();	
	
	while(1)
	{
		ANO_Loop();
	}
	
	return 0;
}


/******************* (C) COPYRIGHT 2014 ANO TECH *****END OF FILE************/
