#ifndef __ANO_FLYCONTROL_H
#define __ANO_FLYCONTROL_H

#include "ANO_Config.h"

#define FLYANGLE_MAX 250  //最大飞行倾角25度

enum {
    PIDROLL,
    PIDPITCH,
    PIDYAW,
		PIDITEMS
};

class ANO_FlyControl
{

public:
	
	ANO_PID pid[PIDITEMS];

	ANO_FlyControl();

	//姿态控制
	void Attitude_Loop(void);
	
private:
	
	uint8_t yawRate;
	int32_t RateError[3];
	void PID_Reset(void);
};

extern ANO_FlyControl fc;

#endif























