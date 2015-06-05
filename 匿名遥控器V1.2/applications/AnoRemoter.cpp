/******************** (C) COPYRIGHT 2014 ANO Tech ***************************
 * 作者		 ：匿名科创
 * 文件名  ：AnoRemoter.cpp
 * 描述    ：匿名迷你手持遥控器
 * 代码版本：V1.2
 * 时间		 ：2014/10/13
 * 官网    ：www.anotc.com
 * 淘宝    ：anotc.taobao.com
 * 技术Q群 ：190169595
**********************************************************************************/
#include "ANO_Config.h"

int main(void)
{
	//初始化遥控器的硬件设置
	ANO_Remoter_board_Init();
	
	//初始化参数
	param.Init();
	
	//初始化IMU（惯性测量单元）
	imu.Init();		
	
	while(1)
	{
		ANO_Loop();
	}
	
	return 0;
}


/******************* (C) COPYRIGHT 2014 ANO TECH *****END OF FILE************/
