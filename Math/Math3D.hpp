//==========================================================
//Math2D.hpp
//==========================================================
#pragma once

#ifndef _MATH3D_HPP_
#define _MATH3D_HPP_

#include "Engine/Math/AABB3D.hpp"
#include "Engine/Math/Dics3D.hpp"
#include "Engine/Math/LineSegment3D.hpp"

class Math3D
{
public:
	static	 bool DoAABBsOverlap( const AABB3D& first, const AABB3D& second );
	static   bool DoDiscsOverlap( const Disc3D& first, const Disc3D& second );
	static   bool DoShapesOverlap( const AABB3D& box, const Disc3D& disc );
	static   bool DoShapesOverlap( const Disc3D& disc, const AABB3D& box );

	static  inline const Vector3 Interpolate( const Vector3& start, const Vector3& end, float fractionFromStartToEnd );
	static  inline const Disc3D Interpolate( const Disc3D& start, const Disc3D& end, float fractionFromStartToEnd );
	static  inline const AABB3D Interpolate( const AABB3D& start, const AABB3D& end, float fractionFromStartToEnd );
	static  inline const LineSegment3D Interpolate( const LineSegment3D& start, const LineSegment3D& end, float fractionFromStartToEnd );

};



///------------------------------------------------------
///
///------------------------------------------------------


///------------------------------------------------------
///
///------------------------------------------------------
const Vector3 Math3D::Interpolate( const Vector3& start, const Vector3& end, float fractionFromStartToEnd )
{
	Vector3 result;
	result = start + ( end - start ) * fractionFromStartToEnd;
	return result;
}
///------------------------------------------------------
///
///------------------------------------------------------
const Disc3D Math3D::Interpolate( const Disc3D& start, const Disc3D& end, float fractionFromStartToEnd )
{
	Vector3 center;
	float	radius;
	center = start.center + (end.center - start.center) * fractionFromStartToEnd;
	radius = start.radius + (end.radius - start.radius) * fractionFromStartToEnd;
	return Disc3D(center,radius);
}
///------------------------------------------------------
///
///------------------------------------------------------
const AABB3D Math3D::Interpolate( const AABB3D& start, const AABB3D& end, float fractionFromStartToEnd )
{
	AABB3D result;
	result.mins = start.mins + (end.mins - start.mins) * fractionFromStartToEnd;
	result.maxs = start.maxs + (end.maxs - start.maxs) * fractionFromStartToEnd;
	return result;
}
///------------------------------------------------------
///
///------------------------------------------------------
const LineSegment3D Math3D::Interpolate( const LineSegment3D& start, const LineSegment3D& end, float fractionFromStartToEnd )
{
	LineSegment3D result;
	result.point1 = start.point1 + (end.point1 - start.point1) * fractionFromStartToEnd;
	result.point2 = start.point2 + (end.point2 - start.point2) * fractionFromStartToEnd;
	return result;
}


#endif