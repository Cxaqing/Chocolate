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
	void FillTriangle(CDC *pDC);  //���������
	void GouraudShade(CDC *pDC);  //�⻬��ɫ
	void EdgeFlag(CPoint3 PStart, CPoint3 PEnd, BOOL bFeature); //��߱���㷨
	void SortVertex();  //�����ζ�������
	CRGB LinearInterpolation(double t, double mStart, double mEnd, CRGB cStart, CRGB cEnd); //��ɫ���Բ�ֵ
	void InitialDepthBuffer(int,int,double);//��ʼ����Ȼ�����
public:
	CPoint3 point0, point1, point2;  //�����ε���������
	CPoint2* SpanLeft;  //��ȵ���������־
	CPoint2* SpanRight; //��ȵ��յ������־
	int nIndex;  //��¼ɨ��������
	double **zBuffer;//����ȳ���
	int Width,Height;//�����������߶�
};

