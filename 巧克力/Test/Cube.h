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
	void ReadVertex(void);//读入点表
	void ReadFacet(void);//读入面表
	void SetScene(CLighting* pLight, CMaterial* pMaterial);//设置场景
	void Draw(CDC* pDC, CZBuffer* pZBuffer, BOOL bFlatShade);//绘制图形
	//void Draw(CDC* pDC);//绘制图形	
public:	
	CP3 P[8];//点表
	CFacet F[6];//面表
	//int N1, N2;//N1为环周向的面片组数,N2为一个截面周向的面片数量

	
	CLighting *pLight;//光照
	CMaterial *pMaterial;//材质	
	CProjection projection;//投影
};

