#pragma once
#include"ZBuffer.h"
#include"Projection.h"
#include<iostream>
using namespace std;


class CTriangle  //�����������
{
public:
	CTriangle();
	virtual ~CTriangle();
	void SetPoint(CP3 Pt0, CP3 Pt1, CP3 Pt2); //���������θ���������
	void Draw(CDC* pDC, CZBuffer* pzbuf);  //����ͼ��
private:
	CP3 P[3];
	CProjection projection;  //ͶӰ
};

