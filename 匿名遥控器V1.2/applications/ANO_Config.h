#ifndef __ANO_CONFIG_H
#define __ANO_CONFIG_H

#include "board.h"
#include "ANO_Scheduler.h"
#include "ANO_DT.h"
#include "ANO_RC.h"
#include "ANO_Param.h"
#include "ANO_Filter.h"
#include "ANO_IMU.h"

/*----------------------IMU--------------------*/
#define IMU_LOOP_TIME					2000	//��λΪuS

#define ACC_1G 			4096		//�ɼ��ٶȼƵ�����ȷ��
#define ACC_LPF_CUT 30.0f		//���ٶȵ�ͨ�˲�����ֹƵ��10Hz

#define GYRO_CF_TAU 1.2f
/*---------------------------------------------*/


/*-------------------�������ݷ��ͷ�ʽѡ��-----------------*/
//#define ANO_DT_USE_Bluetooth
#define ANO_DT_USE_NRF24l01
/*--------------------------------------------------------*/


class ANO_Config
{
	
public:
	
	ANO_Config();

	class Factor{
		public:		
			float acc_lpf;		
			float gyro_cf;		
	}factor;
	
	class Flag{
		public:
			uint8_t ARMED;
			uint8_t STICKMODE;
			uint8_t ACCELMODE;
	}f;
	
};

extern ANO_Config ano;

#endif

