//==========================================================
//Camera3D.cpp
//==========================================================
#include "Camera3D.hpp"
Vector3 Camera3D::GetForwardVector()
{	
	float cosPitch = cos(m_orientation.pitchDegreesAboutY*DEG2RAD);
	float sinPitch = sin(m_orientation.pitchDegreesAboutY*DEG2RAD);
	float cosYaw = cos(m_orientation.yawDegreesAboutZ*DEG2RAD);
	float sinYaw = sin(m_orientation.yawDegreesAboutZ*DEG2RAD);
	Vector3 direction(cosPitch*cosYaw,cosPitch*sinYaw,-sinPitch);
	return direction;
}