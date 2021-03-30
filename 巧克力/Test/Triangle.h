#pragma once
#include"ZBuffer.h"
#include"Projection.h"
#include<iostream>
using namespace std;


class CTriangle  //三角形填充类
{
public:
	CTriangle();
	virtual ~CTriangle();
	void SetPoint(CP3 Pt0, CP3 Pt1, CP3 Pt2); //读入三角形浮点数顶点
	void Draw(CDC* pDC, CZBuffer* pzbuf);  //绘制图形
private:
	CP3 P[3];
	CProjection projection;  //投影
};

