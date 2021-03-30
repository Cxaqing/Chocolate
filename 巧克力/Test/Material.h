#pragma once
#include "RGB.h"

class CMaterial
{
public:
	CMaterial(void);
	virtual~CMaterial(void);
	void SetAmbient(CRGB c);//���û���������	
	void SetDiffuse(CRGB c);//������������
	void SetSpecular(CRGB c);//���þ��淴����
	void SetExponent(double n);//���ø߹�ָ��
public:
	CRGB M_Ambient;//����������
	CRGB M_Diffuse;//�����䷴����
	CRGB M_Specular;//���淴����
	double M_n;//�߹�ָ��
};