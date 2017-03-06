//==========================================================
//RGBA.cpp
//==========================================================
#include "Engine/Renderer/RGBA.hpp"



RGBA::RGBA(float r,float g,float b,float a):
	R((unsigned char)(r*255))
	,G((unsigned char)(g*255))
	,B((unsigned char)(b*255))
	,A((unsigned char)(a*255))
{
}

RGBA::RGBA(int r,int g,int b,int a):
	R((unsigned char)r)
	,G((unsigned char)g)
	,B((unsigned char)b)
	,A((unsigned char)a)	
{
}

RGBA::RGBA(unsigned char r,unsigned char g,unsigned char b,unsigned char a):
	R(r)
	,G(g)
	,B(b)
	,A(a)	
{
}

RGBA::RGBA(float r,float g,float b):
	R((unsigned char)(r*255))
	,G((unsigned char)(g*255))
	,B((unsigned char)(b*255))
	,A((unsigned char)(255))
{
}
RGBA::~RGBA()
{

}

bool RGBA::operator!=(const RGBA& rgbaToNotEqual) const
{
	if (R == rgbaToNotEqual.R &&G == rgbaToNotEqual.G && B == rgbaToNotEqual.B && A == rgbaToNotEqual.A)
	{
		return false;
	}
	return true;
}

const RGBA RGBA::BLACK(0.0f, 0.0f, 0.0f, 1.0f);
const RGBA RGBA::WHITE (1.0f, 1.0f, 1.0f, 1.0f);