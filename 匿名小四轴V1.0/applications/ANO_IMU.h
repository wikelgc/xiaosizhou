#ifndef __ANO_IMU_H
#define __ANO_IMU_H

#include "ANO_Config.h"

class ANO_IMU : public ANO_Filter
{
	
public:

	ANO_IMU();
	
	//ŷ���Ǳ�ʾ�ķ�������̬
	Vector3f angle;
	
	Vector3f Gyro, Acc, Acc_lpf; 

	LPF2ndData_t Acc_lpf_2nd;

	float magHold;
	
	void Init();
	
	//���´���������
	void updateSensor();	
	
	//�����������̬
	void getAttitude();
	
private:

	Quaternion Q;

	float getDeltaT(uint32_t time);

	//�������Ҿ���ͻ����˲�����̬����
	void DCM_CF(Vector3f gyro,Vector3f acc, float deltaT);
	//������Ԫ���ͻ����˲�����̬����
	void Quaternion_CF(Vector3f gyro,Vector3f acc, float deltaT);

	//�˲���������ʼ��
	void filter_Init();
	//��������ʼ��
	void sensor_Init();

};

extern ANO_IMU imu;

#endif

