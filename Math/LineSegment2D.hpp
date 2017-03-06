//==========================================================
//LineSegment2D.hpp
//==========================================================

#pragma once

#ifndef  _LINESEGMENT2D_HPP_
#define  _LINESEGMENT2D_HPP_

#include "Engine/Math/Vector2.hpp"

class LineSegment2D
{
public:
	Vector2 point1;
	Vector2 point2;

	LineSegment2D();
	~LineSegment2D();
	LineSegment2D(const LineSegment2D& copy);
	
	explicit LineSegment2D(const Vector2& initialP1,const Vector2& initialP2 );
	explicit LineSegment2D( float P1X, float P1Y, float P2X, float P2Y );
	
///------------------------------------------------------
///Mutators:
///------------------------------------------------------
	inline void AddLength( float addLength );
	inline void Translate( const Vector2& translation );
	inline const Vector2 GetPointAtParametricValue( float parametricValue );
///------------------------------------------------------
///Operators:
///------------------------------------------------------

	inline const LineSegment2D operator + (  const Vector2& translation  ) const;
	inline const LineSegment2D operator - (  const Vector2& antiTranslation ) const;
	inline void operator += (  const Vector2& translation  );
	inline void operator -= ( const Vector2& antiTranslation  );

};

#endif

void LineSegment2D::Translate( const Vector2& translation )
{
	point1+= translation;
	point2+= translation;
}
///------------------------------------------------------
///
///------------------------------------------------------
const Vector2 LineSegment2D::GetPointAtParametricValue( float parametricValue )
{
	Vector2 result;
	result = point1 + (point2-point1) * parametricValue;

	return result;
}

///------------------------------------------------------
///Operators:
///------------------------------------------------------

const LineSegment2D LineSegment2D:: operator + (  const Vector2& translation ) const
{
	LineSegment2D newLine;
	newLine.point1 += translation;
	newLine.point2 += translation;
	return newLine;
}
const LineSegment2D LineSegment2D:: operator - (  const Vector2& antiTranslation ) const
{
	LineSegment2D newLine;
	newLine.point1 -= antiTranslation;
	newLine.point2 -= antiTranslation;
	return newLine;
}
void LineSegment2D::operator += ( const Vector2& translation )
{
	point1 += translation;
	point2 += translation;
}
void LineSegment2D::operator -= ( const Vector2& antiTranslation )
{
	point1 -= antiTranslation;
	point2 -= antiTranslation;
}

