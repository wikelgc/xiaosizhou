#ifndef __ANO_FLYCONTROL_H
#define __ANO_FLYCONTROL_H

#include "ANO_Config.h"

#define FLYANGLE_MAX 250  //���������25��

enum {
    PIDROLL,
    PIDPITCH,
    PIDYAW,
    PIDALT,
    PIDLEVEL,
    PIDMAG,
		PIDITEMS
};

class ANO_FlyControl
{

public:
	
	ANO_PID pid[PIDITEMS];

	ANO_FlyControl();

	//��̬�⻷����
	void Attitude_Outter_Loop(void);

	//��̬�ڻ�����
	void Attitude_Inner_Loop(void);
	
private:
	
	uint8_t yawRate;
	int32_t RateError[3];
	void PID_Reset(void);
};

extern ANO_FlyControl fc;

#endif























