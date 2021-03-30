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

void CTriangle::SetPoint(CP3 Pt0, CP3 Pt1, CP3 Pt2) //����������
{
	this->P[0] = Pt0;
	this->P[1] = Pt1;
	this->P[2] = Pt2;
}

void CTriangle::Draw(CDC* pDC, CZBuffer * pzbuf)  //����������
{
	CP3 Point[3];
	for(int loop = 0; loop  < 3; loop++)
	{
		Point[loop] = projection.PerspectiveProjection(P[loop]);  //ͶӰ
	}
	pzbuf->SetPoint(Point[0],Point[1],Point[2]);  //���������
	pzbuf->FillTriangle(pDC);
	
}