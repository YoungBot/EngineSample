//==========================================================
//EulerAngles.cpp
//==========================================================

#include "Engine/Math/EulerAngles.hpp"

EulerAngles::EulerAngles()
{

}
EulerAngles::EulerAngles(float yaw,float pitch,float roll)
{
	yawDegreesAboutZ = yaw;
	pitchDegreesAboutY = pitch;
	rollDegreesAboutX = roll;
}
EulerAngles::~EulerAngles()
{

}

void  EulerAngles::operator += ( const EulerAngles& eulerAnglesToAdd )
{
	yawDegreesAboutZ +=eulerAnglesToAdd.yawDegreesAboutZ;
	pitchDegreesAboutY += eulerAnglesToAdd.pitchDegreesAboutY;
	rollDegreesAboutX += eulerAnglesToAdd.rollDegreesAboutX;
}

void  EulerAngles::operator *= (float scale)
{
	yawDegreesAboutZ *=scale;
	pitchDegreesAboutY *=scale;
	rollDegreesAboutX *=scale;
}