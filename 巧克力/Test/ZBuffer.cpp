#include "StdAfx.h"
#include "ZBuffer.h"
#include "math.h"


CZBuffer::CZBuffer()
{
}


CZBuffer::~CZBuffer()
{
	for(int i=0;i<Width;i++)
	{
		delete[] zBuffer[i];
		zBuffer[i]=NULL;
	}
	if(zBuffer!=NULL)
	{
		delete zBuffer;
		zBuffer=NULL;
	}	
}

void CZBuffer::SetPoint(CP3 P0, CP3 P1, CP3 P2)
{
	point0.x = Round(P0.x);
	point0.y = Round(P0.y);
	point0.z = P0.z;     //伪深度坐标为0~1范围，不能四舍五入，否则都为0了
	point0.c = P0.c;
	point1.x = Round(P1.x);
	point1.y = Round(P1.y);
	point1.z = P1.z;
	point1.c = P1.c;
	point2.x = Round(P2.x);
	point2.y = Round(P2.y);
	point2.z = P2.z;
	point2.c = P2.c;
}
void CZBuffer::FillTriangle(CDC *pDC)  //填充三角形
{
	if(point0 != point1 && point0 != point2 && point1 != point2)
	{
		SortVertex();  // point0点为y坐标最小的点，point1点为y坐标最大的点，point2点y坐标居中
		//定义三角形覆盖的扫描线条数
		int nTotalScanLine = point1.y - point0.y  + 1;
		//定义span的起点与终点数组
		SpanLeft = new CPoint2[nTotalScanLine];   //跨度左边数组
		SpanRight = new CPoint2[nTotalScanLine];  //跨度右边数组
		//判断三角形与POP1主边的位置关系，0-1-2为右手系
		int nDeltz = (point1.x - point0.x) * (point2.y - point1.y) - (point1.y - point0.y)*(point2.x - point1.x);  //P0P1叉乘P1P2求法矢量
		if(nDeltz > 0)  //三角形位于POP1主边的左侧
		{
			nIndex = 0;
			EdgeFlag(point0, point2, TRUE);
			EdgeFlag(point2, point1, TRUE);
			nIndex = 0;
			EdgeFlag(point0, point1, FALSE);
		}
		else if(nDeltz < 0)
		{
			nIndex = 0;
			EdgeFlag(point0, point1, TRUE);
			nIndex = 0;
			EdgeFlag(point0, point2, FALSE);
			EdgeFlag(point2, point1, FALSE);
		}
		GouraudShade(pDC);
		if(SpanLeft)
		{
			delete []SpanLeft;
			SpanLeft = NULL;
		}
		if(SpanRight)
		{
			delete []SpanRight;
			SpanRight = NULL;
		}
	}
}
void CZBuffer::GouraudShade(CDC *pDC)  //光滑着色
{
	double CurDeep = 0.0;   //当前扫描线深度
	double DeepStep = 0.0;
	CVector3 V01(point0,point1),V02(point0,point2);
	CVector3 fNormal = CrossProduct(V01,V02);
	double A = fNormal.x;
	double B = fNormal.y;
	double C = fNormal.z;   //平面方程Ax+By+Cz+D = 0的系数
	double D = -A * point0.x - B * point0.y - C * point0.z;  //当前扫描线随着x增长的深度步长
	if(fabs(C) < 1e-4)
		C = 1.0;
	DeepStep = -A/C;        //计算扫描线深度步长增量
	for(int y = point0.y; y < point1.y; y++)  //下闭上开
	{
		int n = y - point0.y;
		BOOL bInFlag = FALSE;
		for(int x = SpanLeft[n].x; x < SpanRight[n].x; x++)
		{
			 if(bInFlag == FALSE)
			 {
				 CurDeep = -(A * x + B * y +D)/C;
				 bInFlag = TRUE;
				 x -= 1;    //回退    
			 }
			 else
			 {
				 CRGB clr = LinearInterpolation(x, SpanLeft[n].x, SpanRight[n].x, SpanLeft[n].c, SpanRight[n].c);
				 if(CurDeep <= zBuffer[x + Width/2][y + Height/2])
				 {
					 zBuffer[x + Width/2][y + Height/2] = CurDeep;
					 pDC->SetPixelV(x, y, RGB(clr.red * 255, clr.green * 255, clr.blue * 255));
				 }
				 CurDeep += DeepStep;
				 bInFlag = FALSE;
			 }
		}
	}
}

void CZBuffer::EdgeFlag(CPoint3 PStart, CPoint3 PEnd, BOOL bFeature)  //打边标记算法
{
	if(PEnd.y == PStart.y)
			return ;
		int dx = PEnd.x - PStart.x;
		int dy = PEnd.y - PStart.y;
		double m = double(dx)/dy;
		double x = PStart.x;
		for(int y = PStart.y; y < PEnd.y; y++)
		{
			CRGB crColor = LinearInterpolation(y, PStart.y, PEnd.y, PStart.c, PEnd.c);
			if(bFeature)
				SpanLeft[nIndex++] = CPoint2(Round(x), y, crColor);
			else
				SpanRight[nIndex++] = CPoint2(Round(x), y, crColor);
			x += m;
		}
}

void  CZBuffer::SortVertex()  //三角形顶点排序
{
	/*CPoint3 pt[3];
	pt[0] = point0;
	pt[1] = point1;
	pt[2] = point2;
	for(int i = 0; i < 2; i++)
	{
		for(int j = i + 1;j < 3; j++)
		{
			int k = i;
			if(pt[k].y >= pt[j].y)
				k = j;
			if(k == j)
			{
				CPoint3 ptTemp = pt[i];
				pt[i] = pt[k];
				pt[k] = ptTemp;
			}
		}
	}
	point0 = pt[0];
	point1 = pt[2];
	point2 = pt[1];*/
	CPoint3 t;
	while(1)   //死循环出不去：无=号
	{
		if(point0.y>point2.y)
		{
			t = point0;
			point0 = point2;
			point2 = t; 
		}
		t = point2;
		point2 = point1;
		point1 = t; 
		if(point0.y<=point2.y && point2.y<=point1.y)
			break;
	}
}

CRGB  CZBuffer::LinearInterpolation(double t, double mStart, double mEnd, CRGB cStart, CRGB cEnd) //颜色线性插值
{
	CRGB color;
	color = (t - mEnd)/(mStart - mEnd) * cStart +(t - mStart)/(mEnd - mStart) * cEnd;
	return color;
}

void CZBuffer::InitialDepthBuffer(int Width,int Height,double Depth)  //初始化深度缓冲器
{
	this->Width = Width,this->Height = Height;
	zBuffer = new double *[Width];
	for(int i = 0;i < Width;i++)
		zBuffer[i] = new double[Height];
	for(int i = 0;i < Width;i++)//初始化深度缓冲
		for(int j = 0;j < Height;j++)
			zBuffer[i][j] = Depth;
}
