#ifndef __ANO_CONFIG_H
#define __ANO_CONFIG_H

#include "board.h"
#include "ANO_PID.h"
#include "ANO_Filter.h"
#include "ANO_IMU.h"
#include "ANO_Scheduler.h"
#include "ANO_DT.h"
#include "ANO_Motor.h"
#include "ANO_RC.h"
#include "ANO_FlyControl.h"
#include "ANO_Param.h"

/*----------------------IMU--------------------*/
#define ANO_IMU_USE_DCM_CF
//#define ANO_IMU_USE_Quaternions_CF

//#define ANO_IMU_USE_LPF_1st
#define ANO_IMU_USE_LPF_2nd

#define IMU_LOOP_TIME					2000	//单位为uS
#define PID_INNER_LOOP_TIME		2000	//单位为us
#define PID_OUTER_LOOP_TIME		5000	//单位为us

#define ACC_1G 			4096		//由加速度计的量程确定
#define ACC_LPF_CUT 10.0f		//加速度低通滤波器截止频率10Hz

#define GYRO_CF_TAU 1.2f
/*---------------------------------------------*/

/*-------------------无线数据发送方式选择-----------------*/
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
			uint8_t failsafe;
	}f;
	
	//指示灯
	void Pilot_Light(void);
	
};

extern ANO_Config ano;

#endif

