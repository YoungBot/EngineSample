//==========================================================
//Disc3D.cpp
//==========================================================
#include "Engine/Math/Dics3D.hpp"

const Disc3D Disc3D::UNIT_CIRCLE(0.0f,0.0f,0.0f,1.0f);

Disc3D::Disc3D()
{
}

Disc3D::~Disc3D() 
{

}

Disc3D::Disc3D( const Disc3D& copy )
{
	center = copy.center;
	radius = copy.radius;	
}
Disc3D::Disc3D( float initialX, float initialY, float initialZ, float initialRadius )
{
	center.SetXYZ(initialX,initialY,initialZ);
	radius = initialRadius;
}

Disc3D::Disc3D( const Vector3& initialCenter, float initialRadius )
{
	center = initialCenter;
	radius = initialRadius;
}

