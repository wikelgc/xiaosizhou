#ifndef __ANO_RC_H
#define __ANO_RC_H

#include "ANO_Config.h"

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

	uint16_t Data[8];
	int16_t DataTrim[8];
	float DataRaw[8];

	uint16_t KeyDataL,KeyDataR;
	float KeyDataRawL,KeyDataRawR;

	//参数初始化
	void Init(void);
	
	//将ADC采样值转为遥控通道数据
	void DataGet(void);

	void DataCalculate(void);

	void KeyCheck(void);

private:

};

extern ANO_RC rc;

#endif



