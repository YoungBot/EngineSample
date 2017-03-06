//==========================================================
//Dics2D.hpp
//==========================================================
#pragma once

#ifndef _DISC2D_HPP_ 
#define _DISC2D_HPP_
#include "Engine/Math/Vector2.hpp"



class Disc2D
{
public:
	Vector2 center;
	float	radius;
///------------------------------------------------------
///
///------------------------------------------------------	

///------------------------------------------------------
///Constructors / destructors:
///------------------------------------------------------	

	~Disc2D();
	Disc2D();
	Disc2D( const Disc2D& copy );

	explicit Disc2D( float initialX, float initialY, float initialRadius );
	explicit Disc2D( const Vector2& initialCenter, float initialRadius );

///------------------------------------------------------
///Mutators:
///------------------------------------------------------

	inline void StretchToIncludePoint( const Vector2& point );

	inline void AddPadding( float paddingRadius );
	inline void Translate( const Vector2& translation );
///------------------------------------------------------
///Accessors / queries:
///------------------------------------------------------

	inline bool IsPointInside( const Vector2& point ) const;
///------------------------------------------------------
///Operators:
///------------------------------------------------------

	inline const Disc2D operator + ( const Vector2& translation ) const;
	inline const Disc2D operator - ( const Vector2& antiTranslation ) const;
	inline void operator += ( const Vector2& translation );
	inline void operator -= ( const Vector2& antiTranslation );

	static const Disc2D UNIT_CIRCLE;

};

#endif
 

void Disc2D:: StretchToIncludePoint( const Vector2& point )
{
	radius = CalcDistance(point,center);
}

void Disc2D::AddPadding( float paddingRadius )
{
	radius += paddingRadius;
}

void Disc2D::Translate( const Vector2& translation )
{
	center += translation;
}

bool Disc2D::IsPointInside( const Vector2& point ) const
{
	if (CalcDistanceSquared(point,center)>radius*radius)
		return false;
	else
		return true;
}
///------------------------------------------------------
///operator
///------------------------------------------------------
const Disc2D Disc2D::operator + ( const Vector2& translation ) const
{
	Vector2 newCenter;
	newCenter = center+translation;
	Disc2D newDisc(newCenter,radius);
	return newDisc;
}
const Disc2D Disc2D::operator - ( const Vector2& antiTranslation ) const
{
	Vector2 newCenter;
	newCenter = center-antiTranslation;
	Disc2D newDisc(newCenter,radius);
	return newDisc;
}
void Disc2D::operator += ( const Vector2& translation )
{
	center+=translation;
}
void Disc2D::operator -= ( const Vector2& antiTranslation )
{
	center-=antiTranslation;
}
