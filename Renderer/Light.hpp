//==========================================================
//Light.hpp
//==========================================================
#pragma once

#ifndef _LIGHT_HPP_
#define _LIGHT_HPP_

#include "Engine/Math/Vector2.hpp"
#include "Engine/Math/Vector3.hpp"
#include "Engine/Math/Vector4.hpp"
class Light
{
public:
	Light();
	Light(Vector3 position, Vector3 direction,Vector4 lightColor,float weight,float angle, float spotPower,float minsf, float minIntensity,float maxIntensity);	
	Vector3 m_lightPosition;
	Vector3 m_lightDirection;
	Vector4 m_lightColor;
	float m_lVWeight;
	float m_lightAngle;
	float m_spotPower;
	float m_minSf;
	float m_minIntensity;
	float m_maxIntensity;
};



#endif
