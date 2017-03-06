//==========================================================
//RayCast3D.cpp
//==========================================================
#include "RayCast3D.hpp"

RayCast3D::RayCast3D()
{

}

RayCast3D::RayCast3D(float length)
{
	m_length = length;
}

RayCast3D::RayCast3D(Vector3 position,EulerAngles orientation,float length)
{
	m_length = length;
	m_orientation = orientation;
	m_position = position;
}

RayCast3D::~RayCast3D()
{

}

Vector3 RayCast3D::GetPositionByPercentage(float percentage)
{
	float sinPitch = sin(m_orientation.pitchDegreesAboutY*DEG2RAD);
	float cosYaw = cos(m_orientation.yawDegreesAboutZ*DEG2RAD);
	float sinYaw = sin(m_orientation.yawDegreesAboutZ*DEG2RAD);
	Vector3 direction(sinPitch*cosYaw,sinPitch*sinYaw,-sinPitch);
	direction.Normalize();
	direction*=m_length;
	direction*=percentage;
	Vector3 destination = direction+ m_position;
	return destination;
}

Vector3 RayCast3D::GetFinalDestination()
{
	float sinPitch = sin(m_orientation.pitchDegreesAboutY*DEG2RAD);
	float cosYaw = cos(m_orientation.yawDegreesAboutZ*DEG2RAD);
	float sinYaw = sin(m_orientation.yawDegreesAboutZ*DEG2RAD);
	Vector3 direction(sinPitch*cosYaw,sinPitch*sinYaw,-sinPitch);
	direction.Normalize();
	direction*=m_length;
	Vector3 destination = direction+ m_position;
	return destination;
}

