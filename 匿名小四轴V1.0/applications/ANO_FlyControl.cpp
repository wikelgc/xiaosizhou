/******************** (C) COPYRIGHT 2014 ANO Tech ***************************
 * 作者		 ：匿名科创
 * 文件名  ：ANO_FlyControl.cpp
 * 描述    ：飞行控制
 * 官网    ：www.anotc.com
 * 淘宝    ：anotc.taobao.com
 * 技术Q群 ：190169595
**********************************************************************************/
#include "ANO_FlyControl.h"

ANO_FlyControl fc;


ANO_FlyControl::ANO_FlyControl()
{
	yawRate = 120;
	//重置PID参数
	PID_Reset();
}

//重置PID参数
void ANO_FlyControl::PID_Reset(void)
{
	pid[PIDROLL].set_pid(90, 30, 90, 2000000);
	pid[PIDPITCH].set_pid(90, 30, 90, 2000000);
	pid[PIDYAW].set_pid(150, 85, 0, 2000000);
	pid[PIDLEVEL].set_pid(280, 0, 0, 0);
	pid[PIDMAG].set_pid(15, 0, 0, 0);
}

//飞行器姿态外环控制
void ANO_FlyControl::Attitude_Outter_Loop(void)
{
	int32_t	errorAngle[2];
	Vector3f Gyro_ADC;
	
	//计算角度误差值
	errorAngle[ROLL] = constrain_int32((rc.Command[ROLL] * 2) , -((int)FLYANGLE_MAX), +FLYANGLE_MAX) - imu.angle.x * 10; 
	errorAngle[PITCH] = constrain_int32((rc.Command[PITCH] * 2) , -((int)FLYANGLE_MAX), +FLYANGLE_MAX) - imu.angle.y * 10; 
	
	//获取角速度
	Gyro_ADC = mpu6050.Get_Gyro() / 4;
	
	//得到外环PID输出
	RateError[ROLL] = pid[PIDLEVEL].get_p(errorAngle[ROLL]) - Gyro_ADC.x;
	RateError[PITCH] = pid[PIDLEVEL].get_p(errorAngle[PITCH]) - Gyro_ADC.y;
	RateError[YAW] = ((int32_t)(yawRate) * rc.Command[YAW]) / 32 - Gyro_ADC.z;		
}

//飞行器姿态内环控制
void ANO_FlyControl::Attitude_Inner_Loop(void)
{
	int32_t PIDTerm[3];
	
	for(u8 i=0; i<3;i++)
	{
		//当油门低于检查值时积分清零
		if ((rc.rawData[THROTTLE]) < RC_MINCHECK)	
			pid[i].reset_I();
		
		//得到内环PID输出
		PIDTerm[i] = pid[i].get_pid(RateError[i], PID_INNER_LOOP_TIME);
	}
	
	PIDTerm[YAW] = -constrain_int32(PIDTerm[YAW], -300 - abs(rc.Command[YAW]), +300 + abs(rc.Command[YAW]));	
		
	//PID输出转为电机控制量
	motor.writeMotor(rc.Command[THROTTLE], PIDTerm[ROLL], PIDTerm[PITCH], PIDTerm[YAW]);
}	
	
/************************ (C) COPYRIGHT 2014 ANO TECH *****END OF FILE**********************/
