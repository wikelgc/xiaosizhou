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
	//���ٶ�����һ�׵�ͨ�˲�
	Acc_lpf = LPF_1st(Acc_lpf, Acc, ano.factor.acc_lpf);

	DCM_CF(Gyro,Acc_lpf,IMU_LOOP_TIME*1e-6);
}


//���Ҿ��������̬
void ANO_IMU::DCM_CF(Vector3f gyro,Vector3f acc, float deltaT)
{
	static Vector3f deltaGyroAngle, LastGyro;
	static Vector3f Vector_G(0, 0, ACC_1G);
	Matrix3f dcm;
	
	//���������ǽǶȱ仯�����������������	
	deltaGyroAngle = (gyro + LastGyro) * 0.5 * deltaT;
	LastGyro = gyro;
	
	//�����ʾ������ת�����Ҿ���
	dcm.from_euler(deltaGyroAngle);
	
	//�������Ҿ���������������ڻ�������ϵ��ͶӰ
	Vector_G = dcm * Vector_G;
	
	//�����˲���ʹ�ü��ٶȲ���ֵ�������ٶȻ���Ư��
	Vector_G = CF_1st(Vector_G, acc, ano.factor.gyro_cf);

	//�����������ROLL��PITCH
	Vector_G.get_rollpitch(angle);	
	
}

void ANO_IMU::filter_Init()
{
	//���ٶ�һ�׵�ͨ�˲���ϵ������
	ano.factor.acc_lpf = LPF_1st_Factor_Cal(IMU_LOOP_TIME * 1e-6, ACC_LPF_CUT);
	
	//�����˲���ϵ������
	ano.factor.gyro_cf = CF_Factor_Cal(IMU_LOOP_TIME * 1e-6, GYRO_CF_TAU);	
}

void ANO_IMU::sensor_Init()
{
	//��ʼ��MPU6050��1Khz�����ʣ�98Hz��ͨ�˲�
	mpu6050.Init(1000,98);
}


/******************* (C) COPYRIGHT 2014 ANO TECH *****END OF FILE************/
