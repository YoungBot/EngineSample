//==========================================================
//RayCast3D.hpp
//==========================================================

#pragma once

#ifndef _RAYCAST3D_HPP_
#define _RAYCAST3D_HPP_

#include "Engine/Math/EulerAngles.hpp"
#include "Engine/Math/Vector3.hpp"


class RayCast3D
{
public:
	RayCast3D();
	RayCast3D(float length);
	RayCast3D(Vector3 position,EulerAngles orientation,float length);
	~RayCast3D();
	//////////////////////////////////////////////////////////////////////////
	float m_length;
	EulerAngles m_orientation;
	Vector3 m_position;
	//////////////////////////////////////////////////////////////////////////
	Vector3 GetFinalDestination();
	Vector3 GetPositionByPercentage(float percentage);



};


#endif