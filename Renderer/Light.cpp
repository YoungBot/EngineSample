//==========================================================
//Light.cpp
//==========================================================
#include "Light.hpp"

Light::Light()
{

}
//////////////////////////////////////////////////////////////////////////
Light::Light(Vector3 position, Vector3 direction,Vector4 color, float weight, float angle, float spotPower, float minsf,float minIntensity, float maxIntensity)
	:m_lightPosition(position), m_lightDirection(direction),m_lightColor(color), m_lVWeight(weight), m_lightAngle(angle), m_spotPower(spotPower), m_minSf(minsf),m_minIntensity(minIntensity), m_maxIntensity(maxIntensity)
{

}