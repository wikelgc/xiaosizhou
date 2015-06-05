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
	
	void Init();
	
	//���´���������
	void updateSensor();	
	
	//�����������̬
	void getAttitude();
	
private:

	//�������Ҿ���ͻ����˲�����̬����
	void DCM_CF(Vector3f gyro,Vector3f acc, float deltaT);

	//�˲���������ʼ��
	void filter_Init();
	//��������ʼ��
	void sensor_Init();

};

extern ANO_IMU imu;

#endif

