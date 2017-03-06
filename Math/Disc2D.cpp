//==========================================================
//Disc2D.cpp
//==========================================================
#include "Engine/Math/Dics2D.hpp"

const Disc2D Disc2D::UNIT_CIRCLE(0.0f,0.0f,1.0f);

Disc2D::Disc2D()
{
}

Disc2D::~Disc2D() 
{

}

Disc2D::Disc2D( const Disc2D& copy )
{
	center = copy.center;
	radius = copy.radius;	
}
Disc2D::Disc2D( float initialX, float initialY, float initialRadius )
{
	center.SetXY(initialX,initialY);
	radius = initialRadius;
}

Disc2D::Disc2D( const Vector2& initialCenter, float initialRadius )
{
	center = initialCenter;
	radius = initialRadius;
}

