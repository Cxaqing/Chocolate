#pragma once
#include"P3.h"
#include"Point3.h"

#include"Point2.h"
#include"Vector3.h"
#include"Projection.h"

class CZBuffer
{
public:
	CZBuffer();
	virtual ~CZBuffer();
	void SetPoint(CP3 P0, CP3 P1, CP3 P2);
	void FillTriangle(CDC *pDC);  //填充三角形
	void GouraudShade(CDC *pDC);  //光滑着色
	void EdgeFlag(CPoint3 PStart, CPoint3 PEnd, BOOL bFeature); //打边标记算法
	void SortVertex();  //三角形顶点排序
	CRGB LinearInterpolation(double t, double mStart, double mEnd, CRGB cStart, CRGB cEnd); //颜色线性插值
	void InitialDepthBuffer(int,int,double);//初始化深度缓冲器
public:
	CPoint3 point0, point1, point2;  //三角形的整数顶点
	CPoint2* SpanLeft;  //跨度的起点数组标志
	CPoint2* SpanRight; //跨度的终点数组标志
	int nIndex;  //记录扫描线条数
	double **zBuffer;//缓深度冲区
	int Width,Height;//缓冲区宽度与高度
};

