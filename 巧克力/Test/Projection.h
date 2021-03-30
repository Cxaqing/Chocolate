#pragma once
#include "P3.h"
#define Round(d) int (d+0.5)

class CProjection
{
public:
	CProjection(void);
	virtual ~CProjection(void);
	void InitialParameter(void);
	void SetEye(double R, double Phi, double Psi);//�����ӵ�
	CP3 GetEye(void);//����ӵ�
	CP3 PerspectiveProjection(CP3 WorldPoint);//͸��ͶӰ
	//CP2 PerspectiveProjection(CP3 WorldPoint);//͸��ͶӰ
	CP3 OrthogonalProjection(CP3 WorldPoint);//����ͶӰ
private:
	CP3 Eye;//�ӵ�
	double k[8];//͸��ͶӰ����
	double R, Phi, Psi, d;//�ӵ�������
	double Near, Far;//����Զ������
};