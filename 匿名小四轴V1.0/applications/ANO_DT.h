#ifndef __ANO_DT_H
#define __ANO_DT_H

#include "ANO_Config.h"

class ANO_DT
{
	
public:
	
	void Data_Receive_Anl(u8 *data_buf,u8 num);
	//检查是否有接收到无线数据
	void Check_Event(void);
	//数据发送
	void Data_Exchange(void);
	//失控保护检查
	void Failsafe_Check(void);

	class flag{
		public:
		u8 Send_Status;
		u8 Send_Senser;
		u8 Send_PID1;
		u8 Send_PID2;
		u8 Send_PID3;
		u8 Send_RCData;
		u8 Send_Offset;
		u8 Send_MotoPwm;
	}f;
	
private:
		
	u8 data_to_send[50];

	void Send_Status(void);
	void Send_Senser(void);
	void Send_RCData(void);
	void Send_MotoPWM(void);
	void Send_PID1(void);
	void Send_PID2(void);
	void Send_PID3(void);
	void Send_Check(u16 check);

	void Send_Data(u8 *dataToSend , u8 length);

};

extern ANO_DT dt;

#endif









