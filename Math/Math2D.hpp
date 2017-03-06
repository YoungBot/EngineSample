//==========================================================
//Math2D.hpp
//==========================================================
#pragma once

#ifndef _MATH2D_HPP_
#define _MATH2D_HPP_

#include "Engine/Math/AABB2D.hpp"
#include "Engine/Math/Dics2D.hpp"
#include "Engine/Math/LineSegment2D.hpp"
#include "Engine/Renderer/RGBA.hpp"

class Math2D
{
public:
	static	 bool DoAABBsOverlap( const AABB2D& first, const AABB2D& second );
	static   bool DoDiscsOverlap( const Disc2D& first, const Disc2D& second );
	static   bool DoShapesOverlap( const AABB2D& box, const Disc2D& disc );
	static   bool DoShapesOverlap( const Disc2D& disc, const AABB2D& box );

	static  inline const Vector2 Interpolate( const Vector2& start, const Vector2& end, float fractionFromStartToEnd );
	static  inline const RGBA Interpolate(const RGBA& start, const RGBA& end, float fractionFromStartToEnd);
	static  inline const Disc2D Interpolate( const Disc2D& start, const Disc2D& end, float fractionFromStartToEnd );
	static  inline const AABB2D Interpolate( const AABB2D& start, const AABB2D& end, float fractionFromStartToEnd );
	static  inline const LineSegment2D Interpolate( const LineSegment2D& start, const LineSegment2D& end, float fractionFromStartToEnd );

};



///------------------------------------------------------
///
///------------------------------------------------------


///------------------------------------------------------
///
///------------------------------------------------------
const Vector2 Math2D::Interpolate( const Vector2& start, const Vector2& end, float fractionFromStartToEnd )
{
	Vector2 result;
	result = start + ( end - start ) * fractionFromStartToEnd;
	return result;
}
///------------------------------------------------------
///
///------------------------------------------------------
const Disc2D Math2D::Interpolate( const Disc2D& start, const Disc2D& end, float fractionFromStartToEnd )
{
	Vector2 center;
	float	radius;
	center = start.center + (end.center - start.center) * fractionFromStartToEnd;
	radius = start.radius + (end.radius - start.radius) * fractionFromStartToEnd;
	return Disc2D(center,radius);
}
///------------------------------------------------------
///
///------------------------------------------------------
const AABB2D Math2D::Interpolate( const AABB2D& start, const AABB2D& end, float fractionFromStartToEnd )
{
	AABB2D result;
	result.mins = start.mins + (end.mins - start.mins) * fractionFromStartToEnd;
	result.maxs = start.maxs + (end.maxs - start.maxs) * fractionFromStartToEnd;
	return result;
}
///------------------------------------------------------
///
///------------------------------------------------------
const LineSegment2D Math2D::Interpolate( const LineSegment2D& start, const LineSegment2D& end, float fractionFromStartToEnd )
{
	LineSegment2D result;
	result.point1 = start.point1 + (end.point1 - start.point1) * fractionFromStartToEnd;
	result.point2 = start.point2 + (end.point2 - start.point2) * fractionFromStartToEnd;
	return result;
}

const RGBA Math2D::Interpolate(const RGBA& start, const RGBA& end, float fractionFromStartToEnd)
{
	RGBA result;
	result.R = (unsigned char)(start.R + (end.R - start.R) * fractionFromStartToEnd);
	result.G = (unsigned char)(start.G + (end.G - start.G) * fractionFromStartToEnd);
	result.B = (unsigned char)(start.B + (end.B - start.B) * fractionFromStartToEnd);
	result.A = (unsigned char)(start.A + (end.A - start.A) * fractionFromStartToEnd);
	return result;
}
#endif