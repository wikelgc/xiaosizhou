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


void ANO_DT::Check_Event(void)
{
	if(Rx_Ok0)
	{
		Rx_Ok0 = 0;
		nrf.TxPacket_AP(Rx_Buf[0],Rx_Buf[0][3]+5);
	}
	if(Rx_Ok1)
	{
		Rx_Ok1 = 0;
		nrf.TxPacket_AP(Rx_Buf[1],Rx_Buf[1][3]+5);
	}
	
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
			break;
		default:
			f.Send_RCData = 1;
			break;		
	}
	cnt++;
	
	if(f.Send_RCData){
		f.Send_RCData = 0;
		Send_RCData();
	}		
}


void ANO_DT::Send_RCData(void)
{
	u8 _cnt=0;
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0xAF;
	data_to_send[_cnt++]=0x03;
	data_to_send[_cnt++]=0;
	data_to_send[_cnt++]=BYTE1(rc.Data[THROTTLE]);
	data_to_send[_cnt++]=BYTE0(rc.Data[THROTTLE]);
	data_to_send[_cnt++]=BYTE1(rc.Data[YAW]);
	data_to_send[_cnt++]=BYTE0(rc.Data[YAW]);
	data_to_send[_cnt++]=BYTE1(rc.Data[ROLL]);
	data_to_send[_cnt++]=BYTE0(rc.Data[ROLL]);
	data_to_send[_cnt++]=BYTE1(rc.Data[PITCH]);
	data_to_send[_cnt++]=BYTE0(rc.Data[PITCH]);
	data_to_send[_cnt++]=BYTE1(rc.Data[AUX1]);
	data_to_send[_cnt++]=BYTE0(rc.Data[AUX1]);
	data_to_send[_cnt++]=BYTE1(rc.Data[AUX2]);
	data_to_send[_cnt++]=BYTE0(rc.Data[AUX2]);
	data_to_send[_cnt++]=BYTE1(rc.Data[AUX3]);
	data_to_send[_cnt++]=BYTE0(rc.Data[AUX3]);
	data_to_send[_cnt++]=BYTE1(rc.Data[AUX4]);
	data_to_send[_cnt++]=BYTE0(rc.Data[AUX4]);
	
	data_to_send[3] = _cnt-4;
	
	u8 sum = 0;
	for(u8 i=0;i<_cnt;i++)
		sum += data_to_send[i];
	
	data_to_send[_cnt++]=sum;
	
	Send_Data(data_to_send, _cnt);
}



void ANO_DT::Send_Data(u8 *dataToSend , u8 length)
{
#ifdef ANO_DT_USE_NRF24l01
	nrf.TxPacket(data_to_send,length);
#endif
}



/******************* (C) COPYRIGHT 2014 ANO TECH *****END OF FILE************/
