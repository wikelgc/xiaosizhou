/******************** (C) COPYRIGHT 2014 ANO Tech *******************************
 * 作者		 ：匿名科创
 * 文件名  ：ANO_IMU.cpp
 * 描述    ：飞行器姿态计算
 * 官网    ：www.anotc.com
 * 淘宝    ：anotc.taobao.com
 * 技术Q群 ：190169595
**********************************************************************************/
#include "ANO_IMU.h"

ANO_IMU imu;

ANO_IMU::ANO_IMU()
{
}

//IMU初始化
void ANO_IMU::Init()
{
	//滤波器参数初始化
	filter_Init();
	//传感器初始化
	sensor_Init();	
}

//更新传感器数据
void ANO_IMU::updateSensor()
{
	//读取加速度
	mpu6050.Read_Acc_Data();
	//读取角速度
	mpu6050.Read_Gyro_Data();	
	//获取角速度，单位为度每秒
	Gyro = mpu6050.Get_Gyro_in_dps();
	//获取加速度采样值
	Acc = mpu6050.Get_Acc();
}


//计算飞行器姿态
void ANO_IMU::getAttitude()
{
	float deltaT;
	
#ifdef ANO_IMU_USE_LPF_1st	
	//加速度数据一阶低通滤波
	Acc_lpf = LPF_1st(Acc_lpf, Acc, ano.factor.acc_lpf);
#endif	
	
#ifdef ANO_IMU_USE_LPF_2nd	
	//加速度数据二阶低通滤波
	Acc_lpf = LPF_2nd(&Acc_lpf_2nd, Acc);
#endif
	
	deltaT = getDeltaT(GetSysTime_us());
	
#ifdef ANO_IMU_USE_DCM_CF
	DCM_CF(Gyro,Acc_lpf,deltaT);
#endif
#ifdef ANO_IMU_USE_Quaternions_CF
	Quaternion_CF(Gyro,Acc_lpf_1st,deltaT);
#endif
}


//余弦矩阵更新姿态
void ANO_IMU::DCM_CF(Vector3f gyro,Vector3f acc, float deltaT)
{
	static Vector3f deltaGyroAngle, LastGyro;
	static Vector3f Vector_G(0, 0, ACC_1G), Vector_M(1000, 0, 0);
	Matrix3f dcm;
	
	//计算陀螺仪角度变化，二阶龙格库塔积分	
	deltaGyroAngle = (gyro + LastGyro) * 0.5 * deltaT;
	LastGyro = gyro;
	
	//计算表示单次旋转的余弦矩阵
	dcm.from_euler(deltaGyroAngle);
	
	//利用余弦矩阵更新重力向量在机体坐标系的投影
	Vector_G = dcm * Vector_G;
	
	//利用余弦矩阵更新地磁向量在机体坐标系的投影
	Vector_M = dcm * Vector_M;
	
	//互补滤波，使用加速度测量值矫正角速度积分漂移
	Vector_G = CF_1st(Vector_G, acc, ano.factor.gyro_cf);

	//计算飞行器的ROLL和PITCH
	Vector_G.get_rollpitch(angle);	
	
	//计算飞行器的YAW
	Vector_M.get_yaw(angle);
}


#define Kp 2.0f        //加速度权重，越大则向加速度测量值收敛越快
#define Ki 0.001f      //误差积分增益
//四元数更新姿态
void ANO_IMU::Quaternion_CF(Vector3f gyro,Vector3f acc, float deltaT)
{
	Vector3f V_gravity, V_error, V_error_I;
	
	//重力加速度归一化
	acc.normalize();
	
	//提取四元数的等效余弦矩阵中的重力分量
	Q.vector_gravity(V_gravity);
	
	//向量叉积得出姿态误差
	V_error = acc % V_gravity;
	
	//对误差进行积分	
	V_error_I += V_error * Ki;
	
	//互补滤波，姿态误差补偿到角速度上，修正角速度积分漂移
	Gyro += V_error * Kp + V_error_I;		
	
	//一阶龙格库塔法更新四元数
	Q.Runge_Kutta_1st(Gyro, deltaT);
	
	//四元数归一化
	Q.normalize();
	
	//四元数转欧拉角
	Q.to_euler(&angle.x, &angle.y, &angle.z);
}

void ANO_IMU::filter_Init()
{
	//加速度一阶低通滤波器系数计算
	ano.factor.acc_lpf = LPF_1st_Factor_Cal(IMU_LOOP_TIME * 1e-6, ACC_LPF_CUT);
	
	//加速度二阶低通滤波器系数计算
	LPF_2nd_Factor_Cal(&Acc_lpf_2nd);
	
	//互补滤波器系数计算
	ano.factor.gyro_cf = CF_Factor_Cal(IMU_LOOP_TIME * 1e-6, GYRO_CF_TAU);	
}

void ANO_IMU::sensor_Init()
{
	//初始化MPU6050，1Khz采样率，98Hz低通滤波
	mpu6050.Init(1000,98);
}

float ANO_IMU::getDeltaT(uint32_t currentT)
{
	static uint32_t previousT;
	float	deltaT = (currentT - previousT) * 1e-6;	
	previousT = currentT;
	
	return deltaT;
}

/******************* (C) COPYRIGHT 2014 ANO TECH *****END OF FILE************/
