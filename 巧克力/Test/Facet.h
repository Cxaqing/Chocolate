#pragma once
#include "Vector3.h"

class CFacet
{
public:
	CFacet(void);
	virtual ~CFacet(void);
	void SetPtNumber(int Number);
	void SetFacetNormal(CP3 Vertex0,CP3 Vertex1,CP3 Vertex2);//����С�淨ʸ��
public:
	int Number; //��Ķ�����
	int Index[4];//��Ķ���������
	CVector3 fNormal;//��ķ�ʸ��
};

