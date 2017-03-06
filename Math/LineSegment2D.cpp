//==========================================================
//LineSegment2D.cpp
//==========================================================

#include "Engine/Math/LineSegment2D.hpp"

LineSegment2D::LineSegment2D()
{

}

LineSegment2D::~LineSegment2D()
{

}


LineSegment2D::LineSegment2D(const LineSegment2D& copy)
{
	point1 = copy.point1;
	point2 = copy.point2;
}

LineSegment2D::LineSegment2D(const Vector2& initialP1,const Vector2& initialP2 )
{
	point1 = initialP1;
	point2 = initialP2;
}
LineSegment2D::LineSegment2D( float P1X, float P1Y, float P2X, float P2Y )
{
	point1.x = P1X;
	point1.y = P1Y;
	point2.x = P2X;
	point2.y = P2Y;
}

///------------------------------------------------------
///Mutators:
///------------------------------------------------------

