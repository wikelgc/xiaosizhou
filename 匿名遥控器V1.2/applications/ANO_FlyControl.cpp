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
	yawRate = 20;
	//重置PID参数
	PID_Reset();
}

//重置PID参数
void ANO_FlyControl::PID_Reset(void)
{
	pid[PIDROLL].set_pid(50, 15, 65, 2000000);
	pid[PIDPITCH].set_pid(50, 15, 65, 2000000);
	pid[PIDYAW].set_pid(30, 0, 40, 2000000);
}

//飞行器姿态控制
void ANO_FlyControl::Attitude_Loop(void)
{
	int32_t PIDTerm[3];
	int32_t	errorAngle[3];
	
	//计算角度误差值
	errorAngle[ROLL] = constrain_int32((rc.Command[ROLL] * 2) , -((int)FLYANGLE_MAX), +FLYANGLE_MAX) - imu.angle.x * 10; 
	errorAngle[PITCH] = constrain_int32((rc.Command[PITCH] * 2) , -((int)FLYANGLE_MAX), +FLYANGLE_MAX) - imu.angle.y * 10; 
	errorAngle[YAW] = (imu.magHold - imu.angle.z) * 10;
	
	for(u8 i=0; i<3;i++)
	{
		//当油门低于检查值时积分清零
		if ((rc.rawData[THROTTLE]) < RC_MINCHECK)	
			pid[i].reset_I();
		
		//得到PID输出
		PIDTerm[i] = pid[i].get_pid(errorAngle[i], PID_LOOP_TIME);
	}
	
	//PID输出转为电机控制量
	motor.writeMotor(rc.Command[THROTTLE], PIDTerm[ROLL], PIDTerm[PITCH], PIDTerm[YAW]);
}

/************************ (C) COPYRIGHT 2014 ANO TECH *****END OF FILE**********************/
