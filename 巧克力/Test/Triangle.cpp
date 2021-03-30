#include "StdAfx.h"
#include "Triangle.h"


CTriangle::CTriangle()
{
	P[0] = CP3(0,0,0);
	P[1] = CP3(0,0,0);
	P[2] = CP3(0,0,0);
}

CTriangle::~CTriangle()
{
}

void CTriangle::SetPoint(CP3 Pt0, CP3 Pt1, CP3 Pt2) //浮点数顶点
{
	this->P[0] = Pt0;
	this->P[1] = Pt1;
	this->P[2] = Pt2;
}

void CTriangle::Draw(CDC* pDC, CZBuffer * pzbuf)  //绘制三角形
{
	CP3 Point[3];
	for(int loop = 0; loop  < 3; loop++)
	{
		Point[loop] = projection.PerspectiveProjection(P[loop]);  //投影
	}
	pzbuf->SetPoint(Point[0],Point[1],Point[2]);  //填充三角形
	pzbuf->FillTriangle(pDC);
	
}