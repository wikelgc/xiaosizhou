#ifndef __ANO_DRV_LED_H__
#define __ANO_DRV_LED_H__

#include "board.h"

class ANO_LED
{

public:
	
	static void Init(void);

	void ON(void);
	void OFF(void);

};

extern ANO_LED led;

#endif

