#ifndef __ANO_PARAM_H
#define __ANO_PARAM_H

#include "ANO_Config.h"


class ANO_Param
{
	
public:
	
	void Init(void);

	void SAVE_RC_OFFSET(void);

private:
	
	void READ_RC_OFFSET(void);
	void READ_CONF(void);
};

extern ANO_Param param;

#endif

