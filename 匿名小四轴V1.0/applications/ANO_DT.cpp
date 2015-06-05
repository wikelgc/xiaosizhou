/******************** (C) COPYRIGHT 2014 ANO Tech ***************************
 * 作者		 ：匿名科创
 * 文件名  ：ANO_DT.cpp
 * 描述    ：无线数据收发和处理
 * 官网    ：www.anotc.com
 * 淘宝    ：anotc.taobao.com
 * 技术Q群 ：190169595
**********************************************************************************/
#include "ANO_DT.h"

#define BYTE0(dwTemp)       (*(char *)(&dwTemp))
#define BYTE1(dwTemp)       (*((char *)(&dwTemp) + 1))
#define BYTE2(dwTemp)       (*((char *)(&dwTemp) + 2))
#define BYTE3(dwTemp)       (*((char *)(&dwTemp) + 3))

ANO_DT dt;

void ANO_DT::Data_Receive_Anl(u8 *data_buf,u8 num)
{
	u8 sum = 0;
	
	for(u8 i=0;i<(num-1);i++)
		sum += *(data_buf+i);
	if(!(sum==*(data_buf+num-1)))		return;		//判断sum
	if(!(*(data_buf)==0xAA && *(data_buf+1)==0xAF))		return;		//判断帧头
	
	ano.f.failsafe = 0;
/////////////////////////////////////////////////////////////////////////////////////
	if(*(data_buf+2)==0X01)
	{
		if(*(data_buf+4)==0X01)
			mpu6050.Acc_CALIBRATED = 1;
		if(*(data_buf+4)==0X02)
			mpu6050.Gyro_CALIBRATED = 1;
		if(*(data_buf+4)==0X03)
		{
			mpu6050.Acc_CALIBRATED = 1;		
			mpu6050.Gyro_CALIBRATED = 1;			
		}
	}
	
	if(*(data_buf+2)==0X02)
	{
		if(*(data_buf+4)==0X01)
		{
			f.Send_PID1 = 1;
			f.Send_PID2 = 1;
			f.Send_PID3 = 1;
		}
		if(*(data_buf+4)==0X02)
		{
			
		}
	}

	if(*(data_buf+2)==0X03)
	{
		rc.rawData[THROTTLE] = (vs16)(*(data_buf+4)<<8)|*(data_buf+5);
		rc.rawData[YAW] = (vs16)(*(data_buf+6)<<8)|*(data_buf+7);
		rc.rawData[ROLL] = (vs16)(*(data_buf+8)<<8)|*(data_buf+9);
		rc.rawData[PITCH] = (vs16)(*(data_buf+10)<<8)|*(data_buf+11);
		rc.rawData[AUX1] = (vs16)(*(data_buf+12)<<8)|*(data_buf+13);
		rc.rawData[AUX2] = (vs16)(*(data_buf+14)<<8)|*(data_buf+15);
		rc.rawData[AUX3] = (vs16)(*(data_buf+16)<<8)|*(data_buf+17);
		rc.rawData[AUX4] = (vs16)(*(data_buf+18)<<8)|*(data_buf+19);
	}

	if(*(data_buf+2)==0X10)								//PID1
	{
		fc.pid[PIDROLL].kP = (vs16)(*(data_buf+4)<<8)|*(data_buf+5);
		fc.pid[PIDROLL].kI = (vs16)(*(data_buf+6)<<8)|*(data_buf+7);
		fc.pid[PIDROLL].kD = (vs16)(*(data_buf+8)<<8)|*(data_buf+9);
		fc.pid[PIDPITCH].kP = (vs16)(*(data_buf+10)<<8)|*(data_buf+11);
		fc.pid[PIDPITCH].kI = (vs16)(*(data_buf+12)<<8)|*(data_buf+13);
		fc.pid[PIDPITCH].kD = (vs16)(*(data_buf+14)<<8)|*(data_buf+15);
		fc.pid[PIDYAW].kP = (vs16)(*(data_buf+16)<<8)|*(data_buf+17);
		fc.pid[PIDYAW].kI = (vs16)(*(data_buf+18)<<8)|*(data_buf+19);
		fc.pid[PIDYAW].kD = (vs16)(*(data_buf+20)<<8)|*(data_buf+21);
		Send_Check(sum);
	}
	if(*(data_buf+2)==0X11)								//PID2
	{
		fc.pid[PIDALT].kP = (vs16)(*(data_buf+4)<<8)|*(data_buf+5);
		fc.pid[PIDALT].kI = (vs16)(*(data_buf+6)<<8)|*(data_buf+7);
		fc.pid[PIDALT].kD = (vs16)(*(data_buf+8)<<8)|*(data_buf+9);
		fc.pid[PIDLEVEL].kP = (vs16)(*(data_buf+10)<<8)|*(data_buf+11);
		fc.pid[PIDLEVEL].kI = (vs16)(*(data_buf+12)<<8)|*(data_buf+13);
		fc.pid[PIDLEVEL].kD = (vs16)(*(data_buf+14)<<8)|*(data_buf+15);
		fc.pid[PIDMAG].kP = (vs16)(*(data_buf+16)<<8)|*(data_buf+17);
		fc.pid[PIDMAG].kI = (vs16)(*(data_buf+18)<<8)|*(data_buf+19);
		fc.pid[PIDMAG].kD = (vs16)(*(data_buf+20)<<8)|*(data_buf+21);
		Send_Check(sum);
	}
	if(*(data_buf+2)==0X12)								//PID3
	{
		Send_Check(sum);
		param.SAVE_PID();
	}
	if(*(data_buf+2)==0X12)								//PID4
	{
		Send_Check(sum);
	}
	if(*(data_buf+2)==0X12)								//PID5
	{
		Send_Check(sum);
	}
	if(*(data_buf+2)==0X12)								//PID6
	{
		Send_Check(sum);
	}
	if(*(data_buf+2)==0X16)								//OFFSET
	{

	}

/////////////////////////////////////////////////////////////////////////////////////////////////
	if(*(data_buf+2)==0x18)					
	{

	}
}

void ANO_DT::Check_Event(void)
{
	
#ifdef ANO_DT_USE_NRF24l01	
	nrf.Check_Event();
#endif
	
}

void ANO_DT::Data_Exchange(void)
{
	static u8 cnt = 0;
	
	switch(cnt)
	{
		case 1: 
			f.Send_RCData = 1;
			break;
		case 2:
			f.Send_MotoPwm = 1;
			break;
		case 30:
			cnt = 0;
			break;
		default:
			if(cnt%3)
				f.Send_Senser = 1;	
			else
				f.Send_Status = 1;
						
	}
	cnt++;
	
	if(f.Send_Status){
		f.Send_Status = 0;
		Send_Status();
	}	
	if(f.Send_Senser){
		f.Send_Senser = 0;
		Send_Senser();
	}	
	if(f.Send_RCData){
		f.Send_RCData = 0;
		Send_RCData();
	}		
	if(f.Send_MotoPwm){
		f.Send_MotoPwm = 0;
		Send_MotoPWM();
	}	
	if(f.Send_PID1){
		f.Send_PID1 = 0;
		Send_PID1();
	}	
	if(f.Send_PID2){
		f.Send_PID2 = 0;
		Send_PID2();
	}	
}

void ANO_DT::Send_Status(void)
{
	u8 _cnt=0;
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0x01;
	data_to_send[_cnt++]=0;
	vs16 _temp;
	_temp = (int)(imu.angle.x*100);
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = (int)(imu.angle.y*100);
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = (int)(imu.angle.z*100);
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	vs32 _temp2 = 0;//UltraAlt * 100;
	data_to_send[_cnt++]=BYTE3(_temp2);
	data_to_send[_cnt++]=BYTE2(_temp2);
	data_to_send[_cnt++]=BYTE1(_temp2);
	data_to_send[_cnt++]=BYTE0(_temp2);
	
	data_to_send[3] = _cnt-4;
	
	u8 sum = 0;
	for(u8 i=0;i<_cnt;i++)
		sum += data_to_send[i];
	data_to_send[_cnt++]=sum;
	
	Send_Data(data_to_send, _cnt);
}


void ANO_DT::Send_Senser(void)
{
	u8 _cnt=0;
	vs16 _temp;
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0x02;
	data_to_send[_cnt++]=0;
	_temp = imu.Acc.x;
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = imu.Acc.y;
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = imu.Acc.z;	
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = mpu6050.Get_Gyro().x;	
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = mpu6050.Get_Gyro().y;	
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = mpu6050.Get_Gyro().z;	
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	
	data_to_send[_cnt++] = 0;
	data_to_send[_cnt++] = 0;
	data_to_send[_cnt++] = 0;
	data_to_send[_cnt++] = 0;
	data_to_send[_cnt++] = 0;
	data_to_send[_cnt++] = 0;
	
	data_to_send[3] = _cnt-4;
	
	u8 sum = 0;
	for(u8 i=0;i<_cnt;i++)
		sum += data_to_send[i];
	data_to_send[_cnt++] = sum;
	
	Send_Data(data_to_send, _cnt);
}

void ANO_DT::Send_RCData(void)
{
	u8 _cnt=0;
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0x03;
	data_to_send[_cnt++]=0;
	data_to_send[_cnt++]=BYTE1(rc.rawData[THROTTLE]);
	data_to_send[_cnt++]=BYTE0(rc.rawData[THROTTLE]);
	data_to_send[_cnt++]=BYTE1(rc.rawData[YAW]);
	data_to_send[_cnt++]=BYTE0(rc.rawData[YAW]);
	data_to_send[_cnt++]=BYTE1(rc.rawData[ROLL]);
	data_to_send[_cnt++]=BYTE0(rc.rawData[ROLL]);
	data_to_send[_cnt++]=BYTE1(rc.rawData[PITCH]);
	data_to_send[_cnt++]=BYTE0(rc.rawData[PITCH]);
	data_to_send[_cnt++]=BYTE1(rc.rawData[AUX1]);
	data_to_send[_cnt++]=BYTE0(rc.rawData[AUX1]);
	data_to_send[_cnt++]=BYTE1(rc.rawData[AUX2]);
	data_to_send[_cnt++]=BYTE0(rc.rawData[AUX2]);
	data_to_send[_cnt++]=BYTE1(rc.rawData[AUX3]);
	data_to_send[_cnt++]=BYTE0(rc.rawData[AUX3]);
	data_to_send[_cnt++]=BYTE1(rc.rawData[AUX4]);
	data_to_send[_cnt++]=BYTE0(rc.rawData[AUX4]);
	
	data_to_send[3] = _cnt-4;
	
	u8 sum = 0;
	for(u8 i=0;i<_cnt;i++)
		sum += data_to_send[i];
	
	data_to_send[_cnt++]=sum;
	
	Send_Data(data_to_send, _cnt);
}

void ANO_DT::Send_MotoPWM(void)
{
	u8 _cnt=0;
	uint16_t Moto_PWM[6];
	motor.getPWM(Moto_PWM);
	
	for(u8 i=0;i<6;i++)
		Moto_PWM[i] -= 1000;
	
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0x06;
	data_to_send[_cnt++]=0;
	data_to_send[_cnt++]=BYTE1(Moto_PWM[1]);
	data_to_send[_cnt++]=BYTE0(Moto_PWM[1]);
	data_to_send[_cnt++]=BYTE1(Moto_PWM[3]);
	data_to_send[_cnt++]=BYTE0(Moto_PWM[3]);
	data_to_send[_cnt++]=BYTE1(Moto_PWM[5]);
	data_to_send[_cnt++]=BYTE0(Moto_PWM[5]);
	data_to_send[_cnt++]=BYTE1(Moto_PWM[2]);
	data_to_send[_cnt++]=BYTE0(Moto_PWM[2]);
	data_to_send[_cnt++]=BYTE1(Moto_PWM[0]);
	data_to_send[_cnt++]=BYTE0(Moto_PWM[0]);
	data_to_send[_cnt++]=BYTE1(Moto_PWM[4]);
	data_to_send[_cnt++]=BYTE0(Moto_PWM[4]);

	data_to_send[3] = _cnt-4;
	
	u8 sum = 0;
	for(u8 i=0;i<_cnt;i++)
		sum += data_to_send[i];
	
	data_to_send[_cnt++]=sum;
	
	Send_Data(data_to_send, _cnt);
}

void ANO_DT::Send_PID1(void)
{
	u8 _cnt=0;
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0x10;
	data_to_send[_cnt++]=0;
	
	vs16 _temp;
	_temp = fc.pid[PIDROLL].kP ;
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = fc.pid[PIDROLL].kI ;
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = fc.pid[PIDROLL].kD ;
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = fc.pid[PIDPITCH].kP ;
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = fc.pid[PIDPITCH].kI ;
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = fc.pid[PIDPITCH].kD ;
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = fc.pid[PIDYAW].kP;
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = fc.pid[PIDYAW].kI;
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = fc.pid[PIDYAW].kD;
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	
	data_to_send[3] = _cnt-4;
	
	u8 sum = 0;
	for(u8 i=0;i<_cnt;i++)
		sum += data_to_send[i];
	
	data_to_send[_cnt++]=sum;

	Send_Data(data_to_send, _cnt);
}

void ANO_DT::Send_PID2(void)
{
	u8 _cnt=0;
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0x11;
	data_to_send[_cnt++]=0;
	
	vs16 _temp;
	_temp = fc.pid[PIDALT].kP;
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = fc.pid[PIDALT].kI;
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = fc.pid[PIDALT].kD;
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = fc.pid[PIDLEVEL].kP;
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = fc.pid[PIDLEVEL].kI;
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = fc.pid[PIDLEVEL].kD;
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = fc.pid[PIDMAG].kP;
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = fc.pid[PIDMAG].kI;
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = fc.pid[PIDMAG].kD;
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	
	data_to_send[3] = _cnt-4;
	
	u8 sum = 0;
	for(u8 i=0;i<_cnt;i++)
		sum += data_to_send[i];
	
	data_to_send[_cnt++]=sum;
	
	Send_Data(data_to_send, _cnt);
}

void ANO_DT::Send_Check(u16 check)
{
	data_to_send[0]=0xAA;
	data_to_send[1]=0xAA;
	data_to_send[2]=0xF0;
	data_to_send[3]=3;
	data_to_send[4]=0xBA;
	
	data_to_send[5]=BYTE1(check);
	data_to_send[6]=BYTE0(check);
	
	u8 sum = 0;
	for(u8 i=0;i<7;i++)
		sum += data_to_send[i];
	
	data_to_send[7]=sum;

	Send_Data(data_to_send, 8);
}

void ANO_DT::Send_Data(u8 *dataToSend , u8 length)
{
	
#ifdef ANO_DT_USE_Bluetooth
	Uart1_Put_Buf(data_to_send,length);
#endif
	
#ifdef ANO_DT_USE_NRF24l01
	nrf.TxPacket(data_to_send,length);
#endif
}


void ANO_DT::Failsafe_Check(void)
{
		static u8 failsafeCnt = 0;
		if(failsafeCnt > 30)
		{
			failsafeCnt = 0;
			if(!ano.f.failsafe)
				ano.f.failsafe = 1;
			else
			{	
				ano.f.ARMED = 0;
			}
		}
		failsafeCnt++;	
}




/******************* (C) COPYRIGHT 2014 ANO TECH *****END OF FILE************/
