//==========================================================
//Dics3D.hpp
//==========================================================
#pragma once

#ifndef _DISC3D_HPP_ 
#define _DISC3D_HPP_
#include "Engine/Math/Vector3.hpp"



class Disc3D
{
public:
	Vector3 center;
	float	radius;
///------------------------------------------------------
///
///------------------------------------------------------	

///------------------------------------------------------
///Constructors / destructors:
///------------------------------------------------------	

	~Disc3D();
	Disc3D();
	Disc3D( const Disc3D& copy );

	explicit Disc3D( float initialX, float initialY, float initialZ, float initialRadius );
	explicit Disc3D( const Vector3& initialCenter, float initialRadius );

///------------------------------------------------------
///Mutators:
///------------------------------------------------------

	inline void StretchToIncludePoint( const Vector3& point );

	inline void AddPadding( float paddingRadius );
	inline void Translate( const Vector3& translation );
///------------------------------------------------------
///Accessors / queries:
///------------------------------------------------------

	inline bool IsPointInside( const Vector3& point ) const;
///------------------------------------------------------
///Operators:
///------------------------------------------------------

	inline const Disc3D operator + ( const Vector3& translation ) const;
	inline const Disc3D operator - ( const Vector3& antiTranslation ) const;
	inline void operator += ( const Vector3& translation );
	inline void operator -= ( const Vector3& antiTranslation );

	static const Disc3D UNIT_CIRCLE;

};

#endif
 

void Disc3D:: StretchToIncludePoint( const Vector3& point )
{
	radius = CalcDistance(point,center);
}

void Disc3D::AddPadding( float paddingRadius )
{
	radius += paddingRadius;
}

void Disc3D::Translate( const Vector3& translation )
{
	center += translation;
}

bool Disc3D::IsPointInside( const Vector3& point ) const
{
	if (CalcDistanceSquared(point,center)>radius*radius)
		return false;
	else
		return true;
}
///------------------------------------------------------
///operator
///------------------------------------------------------
const Disc3D Disc3D::operator + ( const Vector3& translation ) const
{
	Vector3 newCenter;
	newCenter = center+translation;
	Disc3D newDisc(newCenter,radius);
	return newDisc;
}
const Disc3D Disc3D::operator - ( const Vector3& antiTranslation ) const
{
	Vector3 newCenter;
	newCenter = center-antiTranslation;
	Disc3D newDisc(newCenter,radius);
	return newDisc;
}
void Disc3D::operator += ( const Vector3& translation )
{
	center+=translation;
}
void Disc3D::operator -= ( const Vector3& antiTranslation )
{
	center-=antiTranslation;
}
