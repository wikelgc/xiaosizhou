/******************** (C) COPYRIGHT 2014 ANO Tech ***************************
 * ����		 �������ƴ�
 * �ļ���  ��AnoRemoter.cpp
 * ����    �����������ֳ�ң����
 * ����汾��V1.2
 * ʱ��		 ��2014/10/13
 * ����    ��www.anotc.com
 * �Ա�    ��anotc.taobao.com
 * ����QȺ ��190169595
**********************************************************************************/
#include "ANO_Config.h"

int main(void)
{
	//��ʼ��ң������Ӳ������
	ANO_Remoter_board_Init();
	
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
