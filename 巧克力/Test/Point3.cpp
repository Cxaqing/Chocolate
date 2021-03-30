#include "stdafx.h"
#include "Point3.h"


CPoint3::CPoint3(void)
{
}

CPoint3::~CPoint3(void)
{
}

CPoint3::CPoint3(int x, int y, double z) :CPoint2(x, y)
{
	this->z = z;
}

CPoint3::CPoint3(int x, int y, double z, CRGB c):CPoint2(x,y,c)
{
	this->z = z;
}
bool operator != (CPoint3 &P1,  CPoint3 &P2)
{
	if(P1.x == P2.x && P1.y == P2.y && P1.z == P2.z)
		return false;
	else
		return true;
}