//==========================================================
//EulerAngles.hpp
//==========================================================
#pragma once
#ifndef _EULERANGLES_HPP_
#define _EULERANGLES_HPP_


class EulerAngles
{
public:
	EulerAngles();
	EulerAngles(float yaw,float pitch,float roll);
	float yawDegreesAboutZ;
	float pitchDegreesAboutY;
	float rollDegreesAboutX;
	void  operator *= ( float scale );
	void  operator += ( const EulerAngles& eulerAnglesToAdd );
	~EulerAngles();
};
#endif

