//==========================================================
//LineSegment3D.hpp
//==========================================================

#pragma once

#ifndef  _LINESEGMENT3D_HPP_
#define  _LINESEGMENT3D_HPP_

#include "Engine/Math/Vector3.hpp"

class LineSegment3D
{
public:
	Vector3 point1;
	Vector3 point2;

	LineSegment3D();
	~LineSegment3D();
	LineSegment3D(const LineSegment3D& copy);
	
	explicit LineSegment3D(const Vector3& initialP1,const Vector3& initialP2 );
	explicit LineSegment3D( float P1X, float P1Y, float P1Z, float P2X, float P2Y, float P2Z);
	
///------------------------------------------------------
///Mutators:
///------------------------------------------------------
	inline void AddLength( float addLength );
	inline void Translate( const Vector3& translation );
	inline const Vector3 GetPointAtParametricValue( float parametricValue );
///------------------------------------------------------
///Operators:
///------------------------------------------------------

	inline const LineSegment3D operator + (  const Vector3& translation  ) const;
	inline const LineSegment3D operator - (  const Vector3& antiTranslation ) const;
	inline void operator += (  const Vector3& translation  );
	inline void operator -= ( const Vector3& antiTranslation  );

};

#endif

void LineSegment3D::Translate( const Vector3& translation )
{
	point1+= translation;
	point2+= translation;
}
///------------------------------------------------------
///
///------------------------------------------------------
const Vector3 LineSegment3D::GetPointAtParametricValue( float parametricValue )
{
	Vector3 result;
	result = point1 + (point2-point1) * parametricValue;

	return result;
}

///------------------------------------------------------
///Operators:
///------------------------------------------------------

const LineSegment3D LineSegment3D:: operator + (  const Vector3& translation ) const
{
	LineSegment3D newLine;
	newLine.point1 += translation;
	newLine.point2 += translation;
	return newLine;
}
const LineSegment3D LineSegment3D:: operator - (  const Vector3& antiTranslation ) const
{
	LineSegment3D newLine;
	newLine.point1 -= antiTranslation;
	newLine.point2 -= antiTranslation;
	return newLine;
}
void LineSegment3D::operator += ( const Vector3& translation )
{
	point1 += translation;
	point2 += translation;
}
void LineSegment3D::operator -= ( const Vector3& antiTranslation )
{
	point1 -= antiTranslation;
	point2 -= antiTranslation;
}

