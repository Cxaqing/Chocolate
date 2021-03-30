#pragma once
#include "Point2.h"

class CPoint3 : public CPoint2
{
public:
	CPoint3(void);
	virtual ~CPoint3(void);
	CPoint3(int, int, double);
	CPoint3(int, int, double, CRGB);
	friend bool operator != (CPoint3 &P1, CPoint3 &P2);
public:
	double z;
};

