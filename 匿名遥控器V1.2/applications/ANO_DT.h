#ifndef __ANO_DT_H
#define __ANO_DT_H

#include "ANO_Config.h"

class ANO_DT
{
	
public:
	
	//检查是否有接收到无线数据
	void Check_Event(void);
	//数据发送
	void Data_Exchange(void);
	//失控保护检查
	void Failsafe_Check(void);

	class flag{
		public:
		u8 Send_RCData;
	}f;
	
	void Send_Data(u8 *dataToSend , u8 length);	
	
private:
		
	u8 data_to_send[50];

	void Send_RCData(void);



};

extern ANO_DT dt;

#endif









