#pragma once
#include"Facet.h"
#include"Projection.h"
#include "Lighting.h"
#include "Material.h"
#include "Triangle.h"
#include "ZBuffer.h"

class CCube
{
public:
	CCube(void);
	virtual ~CCube(void);
	void ReadVertex(void);//������
	void ReadFacet(void);//�������
	void SetScene(CLighting* pLight, CMaterial* pMaterial);//���ó���
	void Draw(CDC* pDC, CZBuffer* pZBuffer, BOOL bFlatShade);//����ͼ��
	//void Draw(CDC* pDC);//����ͼ��	
public:	
	CP3 P[8];//���
	CFacet F[6];//���
	//int N1, N2;//N1Ϊ���������Ƭ����,N2Ϊһ�������������Ƭ����

	
	CLighting *pLight;//����
	CMaterial *pMaterial;//����	
	CProjection projection;//ͶӰ
};

