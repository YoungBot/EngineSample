//==========================================================
//AABB3D.hpp
//==========================================================
#pragma once

#ifndef _AABB3D_H_
#define _AABB3D_H_

#include "Engine/Math/Vector3.hpp"



class AABB3D
{

public:
	Vector3 mins;
	Vector3 maxs;
///------------------------------------------------------
///
///------------------------------------------------------	
//public static const data member:

	~AABB3D();
	AABB3D();
	AABB3D( const AABB3D& copy );
explicit AABB3D( float initialX, float initialY, float initialZ );
explicit AABB3D( float minX, float minY, float minZ, float maxX, float maxY, float maxZ );
explicit AABB3D( const Vector3& mins, const Vector3& maxs );
explicit AABB3D( const Vector3& center, float radiusX, float radiusY, float radiusZ );
///------------------------------------------------------
///Mutators:
///------------------------------------------------------
void StretchToIncludePoint( const Vector3& point );
inline void AddPadding( float xPaddingRadius, float yPaddingRadius, float zPaddingRadius );
inline void Translate( const Vector3& translation );
inline void SetMinsAndMaxs(const Vector3& Mins, const Vector3& Maxs);
///------------------------------------------------------
///Accessors / queries:
///------------------------------------------------------
bool IsPointInside( const Vector3& point ) const;
inline const Vector3 CalcSize() const;
inline const Vector3 CalcCenter() const;
inline const Vector3 GetPointAtNormalizedPositionWithinBox( const Vector3& normalizedPosition ) const;
inline const Vector3 GetNormalizedPositionForPointWithinBox( const Vector3& point ) const;

///------------------------------------------------------
///Operators:
///------------------------------------------------------
inline const AABB3D operator + ( const Vector3& translation ) const;
inline const AABB3D operator - ( const Vector3& antiTranslation ) const;
inline void operator += ( const Vector3& translation );
inline void operator -= ( const Vector3& antiTranslation );

static const AABB3D ZERO_TO_ONE;
};


#endif

void AABB3D::AddPadding( float xPaddingRadius, float yPaddingRadius, float zPaddingRadius )
{
	mins.x -= xPaddingRadius;
	mins.y -= yPaddingRadius;
	mins.z -= zPaddingRadius;
	maxs.x += xPaddingRadius;
	maxs.y += yPaddingRadius;
	maxs.z += zPaddingRadius;
}
///------------------------------------------------------
///
///------------------------------------------------------

void AABB3D::Translate( const Vector3& translation )
{
	mins += translation;
	maxs += translation;
	
}
///------------------------------------------------------
///
///------------------------------------------------------

void AABB3D::SetMinsAndMaxs(const Vector3& Mins, const Vector3& Maxs)
{
	mins = Mins;
	maxs = Maxs;
}
///------------------------------------------------------
///
///------------------------------------------------------

const Vector3 AABB3D::CalcSize() const
{
	Vector3 boxSize;
	boxSize.x = maxs.x-mins.x;
	boxSize.y = maxs.y-mins.y;
	boxSize.z = maxs.z-mins.z;
	return boxSize;
}
///------------------------------------------------------
///
///------------------------------------------------------

const Vector3 AABB3D::CalcCenter() const
{
	Vector3 boxCenter;
	boxCenter = (mins + maxs)* 0.5;
	return boxCenter;
}
///------------------------------------------------------
///
///------------------------------------------------------

const Vector3 AABB3D::GetPointAtNormalizedPositionWithinBox( const Vector3& normalizedPosition ) const
{
	Vector3 position;
	position = (maxs - mins) * normalizedPosition + mins;
	return position;
	
}
///------------------------------------------------------
///
///------------------------------------------------------

const Vector3 AABB3D::GetNormalizedPositionForPointWithinBox( const Vector3& point ) const
{
	Vector3 position;
	position.x = ( point.x - mins.x ) / ( maxs.x - mins.x );
	position.y = ( point.y - mins.y ) / ( maxs.y - mins.y );	
	position.z = ( point.z - mins.z ) / ( maxs.z - mins.z );
	return position;
}

///------------------------------------------------------
///operator
///------------------------------------------------------

const AABB3D AABB3D::operator + ( const Vector3& translation ) const
{
	AABB3D box;
	box.mins+= translation;
	box.maxs+= translation;
	return box;

}
///------------------------------------------------------
///
///------------------------------------------------------

const AABB3D AABB3D::operator - ( const Vector3& antiTranslation ) const
{
	AABB3D box;
	box.mins-= antiTranslation;
	box.maxs-= antiTranslation;
	return box;
}
///------------------------------------------------------
///
///------------------------------------------------------

void AABB3D::operator += ( const Vector3& translation )
{
	mins += translation;
	maxs += translation;
}
///------------------------------------------------------
///
///------------------------------------------------------

void AABB3D::operator -= ( const Vector3& antiTranslation )
{
	mins -= antiTranslation;
	maxs -= antiTranslation;
}