#ifndef __ANO_SCHEDULER_H
#define __ANO_SCHEDULER_H

#include "board.h"
#include "ANO_Config.h"

class ANO_Scheduler
{
public:
	//构造函数
	ANO_Scheduler();
	//任务时基计数变量
	uint16_t cnt_1ms,cnt_2ms,cnt_5ms,cnt_10ms,cnt_30ms;

};

void ANO_Loop(void);

extern ANO_Scheduler scheduler;

#endif











