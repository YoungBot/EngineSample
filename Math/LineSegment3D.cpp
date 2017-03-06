//==========================================================
//LineSegment3D.cpp
//==========================================================

#include "Engine/Math/LineSegment3D.hpp"

LineSegment3D::LineSegment3D()
{

}

LineSegment3D::~LineSegment3D()
{

}


LineSegment3D::LineSegment3D(const LineSegment3D& copy)
{
	point1 = copy.point1;
	point2 = copy.point2;
}

LineSegment3D::LineSegment3D(const Vector3& initialP1,const Vector3& initialP2 )
{
	point1 = initialP1;
	point2 = initialP2;
}
LineSegment3D::LineSegment3D( float P1X, float P1Y, float P1Z, float P2X, float P2Y, float P2Z )
{
	point1.x = P1X;
	point1.y = P1Y;
	point1.z = P1Z;
	point2.x = P2X;
	point2.y = P2Y;
	point2.z = P2Z;
}

///------------------------------------------------------
///Mutators:
///------------------------------------------------------

