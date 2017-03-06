//==========================================================
//Camera3D.hpp
//==========================================================
#pragma once


#ifndef _CAMERA3D_HPP_
#define _CAMERA3D_HPP_


#include "RayCast3D.hpp"
class Camera3D
{
public:
	Camera3D(){};
	Camera3D(const Vector3& initialPosition, const EulerAngles& initialOrientation)
		:m_position(initialPosition)
		,m_orientation(initialOrientation)
	{
		m_rayCast.m_length = 8.0f;
		m_rayCast.m_orientation = m_orientation;
		m_rayCast.m_position = m_position;
	};
	//const Vector3 GetForwardVector() const;
	RayCast3D m_rayCast;
	Vector3 m_position;
	EulerAngles m_orientation;
	Vector3 GetForwardVector();
};
#endif