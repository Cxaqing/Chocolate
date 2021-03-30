#include "StdAfx.h"
#include "Cube.h"
#include <math.h>//包含数学头文件
#define  PI 3.1415926//PI的宏定义
#define ROUND(d) int(d + 0.5)//四舍五入宏定义

CCube::CCube(void)
{
}

CCube::~CCube(void)
{
}

void CCube::ReadVertex(void)//点表
{
	P[0].x = -0.8, P[0].y = -0.4, P[0].z = 0;
	P[1].x = 0.8, P[1].y = -0.4, P[1].z = 0;
	P[2].x = 0.8, P[2].y = 0.4, P[2].z = 0;
	P[3].x = -0.8, P[3].y = 0.4, P[3].z = 0;
	P[4].x = -1, P[4].y = -0.5, P[4].z = -0.5;
	P[5].x = 1, P[5].y = -0.5, P[5].z = -0.5;
	P[6].x = 1, P[6].y = 0.5, P[6].z = -0.5;
	P[7].x = -1, P[7].y = 0.5, P[7].z = -0.5;
}

void CCube::ReadFacet(void)//面表
{
	F[0].Number = 4;F[1].Index[0] = 0;F[1].Index[1] = 1;F[1].Index[2] = 2;F[1].Index[3] = 3;//前面
	F[1].Number = 4;F[0].Index[0] = 4;F[0].Index[1] = 7;F[0].Index[2] = 6;F[0].Index[3] = 5;//后面
	F[2].Number = 4;F[2].Index[0] = 0;F[2].Index[1] = 3;F[2].Index[2] = 7;F[2].Index[3] = 4;//左面
	F[3].Number = 4;F[3].Index[0] = 1;F[3].Index[1] = 5;F[3].Index[2] = 6;F[3].Index[3] = 2;//右面
	F[4].Number = 4;F[4].Index[0] = 2;F[4].Index[1] = 6;F[4].Index[2] = 7;F[4].Index[3] = 3;//顶面
	F[5].Number = 4;F[5].Index[0] = 0;F[5].Index[1] = 4;F[5].Index[2] = 5;F[5].Index[3] = 1;//底面
}

void CCube::SetScene(CLighting* pLight, CMaterial* pMaterial)
{
	this->pLight = pLight;
	this->pMaterial = pMaterial;
}

void CCube::Draw(CDC* pDC, CZBuffer* pZBuffer, BOOL bFlatShade)
{
	CP3 ViewPoint = projection.GetEye();//视点
	CP3 Point4[4];//立方体顶点数组
	CP2 ScreenPoint,temp;
	CTriangle triangle0,triangle1; //三角形
	for(int nFacet = 0; nFacet < 6; nFacet++)//面循环
	{
		CVector3 ViewVector(P[F[nFacet].Index[0]], ViewPoint);//面的视矢量
		ViewVector = ViewVector.Normalize();//规范化视矢量

		F[nFacet].SetFacetNormal(P[F[nFacet].Index[0]], P[F[nFacet].Index[1]], P[F[nFacet].Index[2]]);//计算面矢量
		CVector3 FacetNormal = F[nFacet].fNormal.Normalize();//规范化法矢量

		double dotproduct = DotProduct(ViewVector, FacetNormal);//面的视矢量与面的法向量
		if (dotproduct >= 0)//背面剔除算法
		{
			for (int nVertex = 0; nVertex < F[nFacet].Number; nVertex++)
			{
				Point4[nVertex] = projection.PerspectiveProjection(P[F[nFacet].Index[nVertex]]);
				Point4[nVertex].c = pLight->Illuminate(ViewPoint, P[F[nFacet].Index[nVertex]], FacetNormal, pMaterial);//调用光照函数
			}

			triangle0.SetPoint(Point4[0],Point4[1],Point4[2]);
			triangle0.Draw(pDC,pZBuffer);	
			triangle1.SetPoint(Point4[0],Point4[2],Point4[3]);
			triangle1.Draw(pDC,pZBuffer);

			//pZBuffer->SetPoint(Point4[0], Point4[1], Point4[2]);//下三角形
			//pZBuffer->GouraudShade(pDC);
			//pZBuffer->SetPoint(Point4[0], Point4[2], Point4[3]);//上三角形
			//pZBuffer->GouraudShade(pDC);
		}
	}
	//for(int nFacet = 0; nFacet < 6; nFacet++)//面循环
	//{
	//	for(int nPoint = 0;nPoint < F[nFacet].Number; nPoint++)//顶点循环
	//	{
	//		ScreenPoint = projection.PerspectiveProjection(P[F[nFacet].Index[nPoint]]);
	//		if(0 == nPoint)
	//		{
	//			pDC->MoveTo(ROUND(ScreenPoint.x), ROUND(ScreenPoint.y));
	//			temp = ScreenPoint;
	//		}
	//		else
	//		{
	//			pDC->LineTo(ROUND(ScreenPoint.x), ROUND(ScreenPoint.y));
	//		}
	//	}
	//	pDC->LineTo(ROUND(temp.x), ROUND(temp.y));//闭合四边形
	//}
}

	//CP2 ScreenPoint,temp;
	//for(int nFacet = 0; nFacet < 6; nFacet++)//面循环
	//{
	//	for(int nPoint = 0;nPoint < F[nFacet].Number; nPoint++)//顶点循环
	//	{
	//		ScreenPoint = projection.PerspectiveProjection(P[F[nFacet].Index[nPoint]]);
	//		if(0 == nPoint)
	//		{
	//			pDC->MoveTo(ROUND(ScreenPoint.x), ROUND(ScreenPoint.y));
	//			temp = ScreenPoint;
	//		}
	//		else
	//		{
	//			pDC->LineTo(ROUND(ScreenPoint.x), ROUND(ScreenPoint.y));
	//		}
	//	}
	//	pDC->LineTo(ROUND(temp.x), ROUND(temp.y));//闭合四边形
	//}
