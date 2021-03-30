#pragma once
#include "Vector3.h"

class CFacet
{
public:
	CFacet(void);
	virtual ~CFacet(void);
	void SetPtNumber(int Number);
	void SetFacetNormal(CP3 Vertex0,CP3 Vertex1,CP3 Vertex2);//设置小面法矢量
public:
	int Number; //面的顶点数
	int Index[4];//面的顶点索引号
	CVector3 fNormal;//面的法矢量
};

