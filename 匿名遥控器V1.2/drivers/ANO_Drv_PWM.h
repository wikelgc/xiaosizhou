#ifndef __ANO_DRV_PWM_H__
#define __ANO_DRV_PWM_H__

#include "board.h"

#define MAXMOTORS 6

class ANO_PWM
{

public:
	static void out_Init(uint16_t hz);
	void SetPwm(uint16_t pwm[MAXMOTORS]);
	
};

extern ANO_PWM pwm;

#endif

