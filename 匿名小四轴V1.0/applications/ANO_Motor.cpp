/******************** (C) COPYRIGHT 2014 ANO Tech ***************************
 * ����		 �������ƴ�
 * �ļ���  ��ANO_Motor.cpp
 * ����    �����������غ���
 * ����    ��www.anotc.com
 * �Ա�    ��anotc.taobao.com
 * ����QȺ ��190169595
**********************************************************************************/
#include "ANO_Motor.h"

ANO_Motor motor;

void ANO_Motor::writeMotor(uint16_t throttle, int32_t pidTermRoll, int32_t pidTermPitch, int32_t pidTermYaw)
{
	//����X��
	motorPWM[0] = throttle - pidTermRoll + pidTermPitch - pidTermYaw; //����
	motorPWM[1] = throttle - pidTermRoll - pidTermPitch + pidTermYaw; //ǰ��
	motorPWM[2] = throttle + pidTermRoll + pidTermPitch + pidTermYaw; //����
	motorPWM[3] = throttle + pidTermRoll - pidTermPitch - pidTermYaw; //ǰ��
	
	for (u8 i = 0; i < 4; i++) 
		motorPWM[i] = constrain_uint16(motorPWM[i], MINTHROTTLE, MAXTHROTTLE);

	//���δ�������򽫵���������Ϊ���
	if(!ano.f.ARMED || rc.rawData[THROTTLE] < 1200)	
	for(u8 i=0; i< 4 ; i++)
			motorPWM[i] = 1000;

	//д����PWM
	pwm.SetPwm(motorPWM);
	
}

void ANO_Motor::getPWM(uint16_t* pwm)
{
	*(pwm) = motorPWM[0];
	*(pwm+1) = motorPWM[1];
	*(pwm+2) = motorPWM[2];
	*(pwm+3) = motorPWM[3];
}




/******************* (C) COPYRIGHT 2014 ANO TECH *****END OF FILE************/
