#pragma once
#include "P3.h"
#define Round(d) int (d+0.5)

class CProjection
{
public:
	CProjection(void);
	virtual ~CProjection(void);
	void InitialParameter(void);
	void SetEye(double R, double Phi, double Psi);//设置视点
	CP3 GetEye(void);//获得视点
	CP3 PerspectiveProjection(CP3 WorldPoint);//透视投影
	//CP2 PerspectiveProjection(CP3 WorldPoint);//透视投影
	CP3 OrthogonalProjection(CP3 WorldPoint);//正交投影
private:
	CP3 Eye;//视点
	double k[8];//透视投影常数
	double R, Phi, Psi, d;//视点球坐标
	double Near, Far;//近、远剪切面
};