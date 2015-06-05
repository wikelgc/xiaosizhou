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

#define EE_FirstInitFlag 0
#define EE_6050_ACC_X_OFFSET_ADDR	1
#define EE_6050_ACC_Y_OFFSET_ADDR	2
#define EE_6050_ACC_Z_OFFSET_ADDR	3
#define EE_6050_GYRO_X_OFFSET_ADDR	4
#define EE_6050_GYRO_Y_OFFSET_ADDR	5
#define EE_6050_GYRO_Z_OFFSET_ADDR	6
#define EE_PID_ROL_P	7
#define EE_PID_ROL_I	8
#define EE_PID_ROL_D	9
#define EE_PID_PIT_P	10
#define EE_PID_PIT_I	11
#define EE_PID_PIT_D	12
#define EE_PID_YAW_P	13
#define EE_PID_YAW_I	14
#define EE_PID_YAW_D	15
#define EE_PID_ALT_P	16
#define EE_PID_ALT_I	17
#define EE_PID_ALT_D	18
#define EE_PID_LEVEL_P	19
#define EE_PID_LEVEL_I	20
#define EE_PID_LEVEL_D	21
#define EE_PID_MAG_P	22
#define EE_PID_MAG_I	23
#define EE_PID_MAG_D	24

uint16_t FirstInitFlag = 0x44;


void ANO_Param::Init(void)
{

	if(READ_FirstInitFlag()!= FirstInitFlag)	//板子从未初始化
	{
		SAVE_PID();
	}
	
	READ_CONF();
	SAVE_FirstInitFlag();
	
}

void ANO_Param::SAVE_FirstInitFlag(void)
{
	EE_WriteVariable(VirtAddVarTab[EE_FirstInitFlag], FirstInitFlag);
}

uint16_t ANO_Param::READ_FirstInitFlag(void)
{
	uint16_t temp;
	EE_ReadVariable(VirtAddVarTab[EE_FirstInitFlag], &temp);
	return temp;
}

void ANO_Param::SAVE_ACC_OFFSET(void)
{
	EE_WriteVariable(VirtAddVarTab[EE_6050_ACC_X_OFFSET_ADDR], mpu6050.Acc_Offset.x);
	EE_WriteVariable(VirtAddVarTab[EE_6050_ACC_Y_OFFSET_ADDR], mpu6050.Acc_Offset.y);
	EE_WriteVariable(VirtAddVarTab[EE_6050_ACC_Z_OFFSET_ADDR], mpu6050.Acc_Offset.z);
}
void ANO_Param::READ_ACC_OFFSET(void)
{
	uint16_t temp[3];
	EE_ReadVariable(VirtAddVarTab[EE_6050_ACC_X_OFFSET_ADDR], &temp[0]);
	EE_ReadVariable(VirtAddVarTab[EE_6050_ACC_Y_OFFSET_ADDR], &temp[1]);
	EE_ReadVariable(VirtAddVarTab[EE_6050_ACC_Z_OFFSET_ADDR], &temp[2]);
	mpu6050.Acc_Offset.x = temp[0];
	mpu6050.Acc_Offset.y = temp[1];
	mpu6050.Acc_Offset.z = temp[2];
}
void ANO_Param::SAVE_GYRO_OFFSET(void)
{
	EE_WriteVariable(VirtAddVarTab[EE_6050_GYRO_X_OFFSET_ADDR], mpu6050.Gyro_Offset.x);
	EE_WriteVariable(VirtAddVarTab[EE_6050_GYRO_Y_OFFSET_ADDR], mpu6050.Gyro_Offset.y);
	EE_WriteVariable(VirtAddVarTab[EE_6050_GYRO_Z_OFFSET_ADDR], mpu6050.Gyro_Offset.z);
}
void ANO_Param::READ_GYRO_OFFSET(void)
{
	uint16_t temp[3];
	EE_ReadVariable(VirtAddVarTab[EE_6050_GYRO_X_OFFSET_ADDR], &temp[0]);
	EE_ReadVariable(VirtAddVarTab[EE_6050_GYRO_Y_OFFSET_ADDR], &temp[1]);
	EE_ReadVariable(VirtAddVarTab[EE_6050_GYRO_Z_OFFSET_ADDR], &temp[2]);
	mpu6050.Gyro_Offset.x = temp[0];
	mpu6050.Gyro_Offset.y = temp[1];
	mpu6050.Gyro_Offset.z = temp[2];
}
void ANO_Param::SAVE_PID(void)
{
	u16 _temp;
	_temp = fc.pid[PIDROLL].kP;
	EE_WriteVariable(VirtAddVarTab[EE_PID_ROL_P],_temp);
	_temp = fc.pid[PIDROLL].kI;
	EE_WriteVariable(VirtAddVarTab[EE_PID_ROL_I],_temp);
	_temp = fc.pid[PIDROLL].kD;
	EE_WriteVariable(VirtAddVarTab[EE_PID_ROL_D],_temp);
	_temp = fc.pid[PIDPITCH].kP;
	EE_WriteVariable(VirtAddVarTab[EE_PID_PIT_P],_temp);
	_temp = fc.pid[PIDPITCH].kI;
	EE_WriteVariable(VirtAddVarTab[EE_PID_PIT_I],_temp);
	_temp = fc.pid[PIDPITCH].kD;
	EE_WriteVariable(VirtAddVarTab[EE_PID_PIT_D],_temp);
	_temp = fc.pid[PIDYAW].kP;
	EE_WriteVariable(VirtAddVarTab[EE_PID_YAW_P],_temp);
	_temp = fc.pid[PIDYAW].kI;
	EE_WriteVariable(VirtAddVarTab[EE_PID_YAW_I],_temp);
	_temp = fc.pid[PIDYAW].kD;
	EE_WriteVariable(VirtAddVarTab[EE_PID_YAW_D],_temp);
	_temp = fc.pid[PIDALT].kP;
	EE_WriteVariable(VirtAddVarTab[EE_PID_ALT_P],_temp);
	_temp = fc.pid[PIDALT].kI;
	EE_WriteVariable(VirtAddVarTab[EE_PID_ALT_I],_temp);
	_temp = fc.pid[PIDALT].kD;
	EE_WriteVariable(VirtAddVarTab[EE_PID_ALT_D],_temp);
	_temp = fc.pid[PIDLEVEL].kP;
	EE_WriteVariable(VirtAddVarTab[EE_PID_LEVEL_P],_temp);
	_temp = fc.pid[PIDLEVEL].kI;
	EE_WriteVariable(VirtAddVarTab[EE_PID_LEVEL_I],_temp);
	_temp = fc.pid[PIDLEVEL].kD;
	EE_WriteVariable(VirtAddVarTab[EE_PID_LEVEL_D],_temp);
	_temp = fc.pid[PIDMAG].kP;
	EE_WriteVariable(VirtAddVarTab[EE_PID_MAG_P],_temp);
	_temp = fc.pid[PIDMAG].kI;
	EE_WriteVariable(VirtAddVarTab[EE_PID_MAG_I],_temp);
	_temp = fc.pid[PIDMAG].kD;
	EE_WriteVariable(VirtAddVarTab[EE_PID_MAG_D],_temp);
}

void ANO_Param::READ_PID(void)
{
	u16 _temp;
	EE_ReadVariable(VirtAddVarTab[EE_PID_ROL_P],&_temp);
	fc.pid[PIDROLL].kP = _temp;
	EE_ReadVariable(VirtAddVarTab[EE_PID_ROL_I],&_temp);
	fc.pid[PIDROLL].kI = _temp ;
	EE_ReadVariable(VirtAddVarTab[EE_PID_ROL_D],&_temp);
	fc.pid[PIDROLL].kD = _temp ;
	
	EE_ReadVariable(VirtAddVarTab[EE_PID_PIT_P],&_temp);
	fc.pid[PIDPITCH].kP = _temp ;
	EE_ReadVariable(VirtAddVarTab[EE_PID_PIT_I],&_temp);
	fc.pid[PIDPITCH].kI = _temp ;
	EE_ReadVariable(VirtAddVarTab[EE_PID_PIT_D],&_temp);
	fc.pid[PIDPITCH].kD = _temp ;
	
	EE_ReadVariable(VirtAddVarTab[EE_PID_YAW_P],&_temp);
	fc.pid[PIDYAW].kP = _temp ;
	EE_ReadVariable(VirtAddVarTab[EE_PID_YAW_I],&_temp);
	fc.pid[PIDYAW].kI = _temp ;
	EE_ReadVariable(VirtAddVarTab[EE_PID_YAW_D],&_temp);
	fc.pid[PIDYAW].kD = _temp ;
	
	EE_ReadVariable(VirtAddVarTab[EE_PID_ALT_P],&_temp);
	fc.pid[PIDALT].kP = _temp ;
	EE_ReadVariable(VirtAddVarTab[EE_PID_ALT_I],&_temp);
	fc.pid[PIDALT].kI = _temp ;
	EE_ReadVariable(VirtAddVarTab[EE_PID_ALT_D],&_temp);
	fc.pid[PIDALT].kD = _temp ;
	
	EE_ReadVariable(VirtAddVarTab[EE_PID_LEVEL_P],&_temp);
	fc.pid[PIDLEVEL].kP = _temp ;
	EE_ReadVariable(VirtAddVarTab[EE_PID_LEVEL_I],&_temp);
	fc.pid[PIDLEVEL].kI = _temp ;
	EE_ReadVariable(VirtAddVarTab[EE_PID_LEVEL_D],&_temp);
	fc.pid[PIDLEVEL].kD = _temp ;
	
	EE_ReadVariable(VirtAddVarTab[EE_PID_MAG_P],&_temp);
	fc.pid[PIDMAG].kP = _temp ;
	EE_ReadVariable(VirtAddVarTab[EE_PID_MAG_I],&_temp);
	fc.pid[PIDMAG].kI = _temp ;
	EE_ReadVariable(VirtAddVarTab[EE_PID_MAG_D],&_temp);
	fc.pid[PIDMAG].kD = _temp ;
}

void ANO_Param::READ_CONF(void)
{
	READ_PID();
	READ_ACC_OFFSET();
	READ_GYRO_OFFSET();
}










