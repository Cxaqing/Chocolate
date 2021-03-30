#include "StdAfx.h"
#include "Material.h"

CMaterial::CMaterial(void)
{
	M_Ambient = CRGB(0.2, 0.2, 0.2);//环境反射率
	M_Diffuse = CRGB(0.8, 0.8, 0.8);//漫反射率
	M_Specular = CRGB(0.0, 0.0, 0.0);//镜面反射率
	M_n = 1.0;//高光指数
}

CMaterial::~CMaterial(void)
{

}

void CMaterial::SetAmbient(CRGB c)
{
	M_Ambient = c;
}

void CMaterial::SetDiffuse(CRGB c)
{
	M_Diffuse = c;
}

void CMaterial::SetSpecular(CRGB c)
{
	M_Specular = c;
}

void CMaterial::SetExponent(double n)
{
	M_n = n;
}
