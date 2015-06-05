#ifndef __ANO_RC_H
#define __ANO_RC_H

#include "ANO_Config.h"

#define RC_MID  			1500                     
#define RC_MINCHECK		1150                      
#define RC_MAXCHECK  	1850 

enum {
    ROLL = 0,
    PITCH,
    YAW,
    THROTTLE,
    AUX1,
    AUX2,
    AUX3,
    AUX4
};

class ANO_RC
{
	
public:
	
	ANO_RC();

	uint16_t rawData[8];
	int16_t Command[4];

	//参数初始化
	void Init(void);
	//遥控通道数据处理
	void Cal_Command(void);
	//摇杆位置检测
	void check_sticks(void);

private:

};

extern ANO_RC rc;

#endif



