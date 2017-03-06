//==========================================================
//MathUtils.cpp
//==========================================================
#include "MathUtils.hpp"

MathUtils::MathUtils()
{
}

MathUtils::~MathUtils()
{
}


float MathUtils::CalcShortestAngularDisplacement( float startAngle, float destinationAngle )
{
	float angularDisp = destinationAngle - startAngle;
	while(angularDisp>360.0f)
	{
		angularDisp-=360.0f;
	}
	while(angularDisp<-360.0f)
	{
		angularDisp+=360.0f;
	}
	return angularDisp;
}
