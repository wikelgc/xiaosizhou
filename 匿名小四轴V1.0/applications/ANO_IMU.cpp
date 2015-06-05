/******************** (C) COPYRIGHT 2014 ANO Tech *******************************
 * ����		 �������ƴ�
 * �ļ���  ��ANO_IMU.cpp
 * ����    ����������̬����
 * ����    ��www.anotc.com
 * �Ա�    ��anotc.taobao.com
 * ����QȺ ��190169595
**********************************************************************************/
#include "ANO_IMU.h"

ANO_IMU imu;

ANO_IMU::ANO_IMU()
{
}

//IMU��ʼ��
void ANO_IMU::Init()
{
	//�˲���������ʼ��
	filter_Init();
	//��������ʼ��
	sensor_Init();	
}

//���´���������
void ANO_IMU::updateSensor()
{
	//��ȡ���ٶ�
	mpu6050.Read_Acc_Data();
	//��ȡ���ٶ�
	mpu6050.Read_Gyro_Data();	
	//��ȡ���ٶȣ���λΪ��ÿ��
	Gyro = mpu6050.Get_Gyro_in_dps();
	//��ȡ���ٶȲ���ֵ
	Acc = mpu6050.Get_Acc();
}


//�����������̬
void ANO_IMU::getAttitude()
{
	float deltaT;
	
#ifdef ANO_IMU_USE_LPF_1st	
	//���ٶ�����һ�׵�ͨ�˲�
	Acc_lpf = LPF_1st(Acc_lpf, Acc, ano.factor.acc_lpf);
#endif	
	
#ifdef ANO_IMU_USE_LPF_2nd	
	//���ٶ����ݶ��׵�ͨ�˲�
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


//���Ҿ��������̬
void ANO_IMU::DCM_CF(Vector3f gyro,Vector3f acc, float deltaT)
{
	static Vector3f deltaGyroAngle, LastGyro;
	static Vector3f Vector_G(0, 0, ACC_1G), Vector_M(1000, 0, 0);
	Matrix3f dcm;
	
	//���������ǽǶȱ仯�����������������	
	deltaGyroAngle = (gyro + LastGyro) * 0.5 * deltaT;
	LastGyro = gyro;
	
	//�����ʾ������ת�����Ҿ���
	dcm.from_euler(deltaGyroAngle);
	
	//�������Ҿ���������������ڻ�������ϵ��ͶӰ
	Vector_G = dcm * Vector_G;
	
	//�������Ҿ�����µش������ڻ�������ϵ��ͶӰ
	Vector_M = dcm * Vector_M;
	
	//�����˲���ʹ�ü��ٶȲ���ֵ�������ٶȻ���Ư��
	Vector_G = CF_1st(Vector_G, acc, ano.factor.gyro_cf);

	//�����������ROLL��PITCH
	Vector_G.get_rollpitch(angle);	
	
	//�����������YAW
	Vector_M.get_yaw(angle);
}


#define Kp 2.0f        //���ٶ�Ȩ�أ�Խ��������ٶȲ���ֵ����Խ��
#define Ki 0.001f      //����������
//��Ԫ��������̬
void ANO_IMU::Quaternion_CF(Vector3f gyro,Vector3f acc, float deltaT)
{
	Vector3f V_gravity, V_error, V_error_I;
	
	//�������ٶȹ�һ��
	acc.normalize();
	
	//��ȡ��Ԫ���ĵ�Ч���Ҿ����е���������
	Q.vector_gravity(V_gravity);
	
	//��������ó���̬���
	V_error = acc % V_gravity;
	
	//�������л���	
	V_error_I += V_error * Ki;
	
	//�����˲�����̬���������ٶ��ϣ��������ٶȻ���Ư��
	Gyro += V_error * Kp + V_error_I;		
	
	//һ�����������������Ԫ��
	Q.Runge_Kutta_1st(Gyro, deltaT);
	
	//��Ԫ����һ��
	Q.normalize();
	
	//��Ԫ��תŷ����
	Q.to_euler(&angle.x, &angle.y, &angle.z);
}

void ANO_IMU::filter_Init()
{
	//���ٶ�һ�׵�ͨ�˲���ϵ������
	ano.factor.acc_lpf = LPF_1st_Factor_Cal(IMU_LOOP_TIME * 1e-6, ACC_LPF_CUT);
	
	//���ٶȶ��׵�ͨ�˲���ϵ������
	LPF_2nd_Factor_Cal(&Acc_lpf_2nd);
	
	//�����˲���ϵ������
	ano.factor.gyro_cf = CF_Factor_Cal(IMU_LOOP_TIME * 1e-6, GYRO_CF_TAU);	
}

void ANO_IMU::sensor_Init()
{
	//��ʼ��MPU6050��1Khz�����ʣ�98Hz��ͨ�˲�
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
