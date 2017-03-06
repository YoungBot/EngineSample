//==========================================================
//AABB2D.cpp
//==========================================================
#include "AABB2D.hpp"

const AABB2D AABB2D::ZERO_TO_ONE(Vector2(0.0f,0.0f),Vector2(1.0f,1.0f));

AABB2D::AABB2D()
{

}

AABB2D::~AABB2D()
{

}

AABB2D::AABB2D(const AABB2D& copy )
{
	mins = copy.mins;
	maxs = copy.maxs;
}
AABB2D::AABB2D( float initialX, float initialY )
{
	if(initialX <= 0)
	{
		mins.x = initialX;
		maxs.x = 0;		
	}
	else
	{
		mins.x = 0;
		maxs.x = initialX;
	}
	if(initialY <= 0)
	{
		mins.y = initialY;
		maxs.y = 0;
	}
	else
	{
		mins.y = 0;
		maxs.y = initialY;
	}
}

AABB2D::AABB2D( float minX, float minY, float maxX, float maxY )
{
	mins.x = minX;
	mins.y = minY;
	maxs.x = maxX;
	maxs.y = maxY;
	//what should we do if the input is not correct
	//e.g. mins>maxs
}

AABB2D::AABB2D( const Vector2& center, float radiusX, float radiusY )
{
	mins.x = center.x - radiusX;
	mins.y = center.y - radiusY;
	maxs.x = center.x + radiusX;
	maxs.y = center.y + radiusY;
}

AABB2D::AABB2D( const Vector2& Mins, const Vector2& Maxs )
{
	mins = Mins;
	maxs = Maxs;
}

///------------------------------------------------------
///Mutators:
///------------------------------------------------------

void AABB2D::StretchToIncludePoint( const Vector2& point)
{
	if(mins.x > point.x )
	{
		mins.x = point.x;
	}
	if(maxs.x < point.x)
	{
		maxs.x = point.x;
	}
	if(mins.y > point.y)
	{
		mins.y = point.y;
	}
	if (maxs.y <point.y)
	{
		maxs.y = point.y;
	}
}


///------------------------------------------------------
///Accessors / queries:
///------------------------------------------------------
bool AABB2D::IsPointInside( const Vector2& point ) const
{
	if (  mins.x >= point.x 
		||mins.y >= point.y
		||maxs.x <= point.x
		||maxs.y <= point.y)
	{
		return false;
	}
	else
		return true;
}


