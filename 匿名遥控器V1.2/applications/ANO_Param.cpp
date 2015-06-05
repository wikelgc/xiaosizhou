/******************** (C) COPYRIGHT 2014 ANO Tech ***************************
 * 作者		 ：匿名科创
 * 文件名  ：ANO_Param.cpp
 * 描述    ：参数读取和保存
 * 官网    ：www.anotc.com
 * 淘宝    ：anotc.taobao.com
 * 技术Q群 ：190169595
**********************************************************************************/
#include "ANO_Param.h"
#include "board.h"

ANO_Param param;

#define EE_RcDataTrimROLL	1
#define EE_RcDataTrimPITCH	2
#define EE_RcDataTrimYAW	3
#define EE_RcDataTrimTHROTTLE	4



void ANO_Param::Init(void)
{	
	READ_CONF();	
}

void ANO_Param::SAVE_RC_OFFSET(void)
{
	EE_WriteVariable(VirtAddVarTab[EE_RcDataTrimROLL], rc.DataTrim[ROLL]);
	EE_WriteVariable(VirtAddVarTab[EE_RcDataTrimPITCH], rc.DataTrim[PITCH]);
	EE_WriteVariable(VirtAddVarTab[EE_RcDataTrimYAW], rc.DataTrim[YAW]);
	EE_WriteVariable(VirtAddVarTab[EE_RcDataTrimTHROTTLE], rc.DataTrim[THROTTLE]);
}
void ANO_Param::READ_RC_OFFSET(void)
{
	uint16_t temp[4];
	EE_ReadVariable(VirtAddVarTab[EE_RcDataTrimROLL], &temp[0]);
	EE_ReadVariable(VirtAddVarTab[EE_RcDataTrimPITCH], &temp[1]);
	EE_ReadVariable(VirtAddVarTab[EE_RcDataTrimYAW], &temp[2]);
	EE_ReadVariable(VirtAddVarTab[EE_RcDataTrimTHROTTLE], &temp[3]);
	
	for(u8 i=0;i<4;i++)
		rc.DataTrim[i] = temp[i];
}

void ANO_Param::READ_CONF(void)
{
	READ_RC_OFFSET();
}










