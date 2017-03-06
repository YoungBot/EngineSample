//==========================================================
//AABB2D.hpp
//==========================================================
#pragma once

#ifndef _AABB2D_H_
#define _AABB2D_H_

#include "Engine/Math/Vector2.hpp"



class AABB2D
{

public:
	Vector2 mins;
	Vector2 maxs;
///------------------------------------------------------
///
///------------------------------------------------------	
//public static const data member:

	~AABB2D();
	AABB2D();
	AABB2D( const AABB2D& copy );
explicit AABB2D( float initialX, float initialY );
explicit AABB2D( float minX, float minY, float maxX, float maxY );
explicit AABB2D( const Vector2& mins, const Vector2& maxs );
explicit AABB2D( const Vector2& center, float radiusX, float radiusY );
///------------------------------------------------------
///Mutators:
///------------------------------------------------------
void StretchToIncludePoint( const Vector2& point );
inline void AddPadding( float xPaddingRadius, float yPaddingRadius );
inline void Translate( const Vector2& translation );
inline void SetMinsAndMaxs(const Vector2& Mins, const Vector2& Maxs);
///------------------------------------------------------
///Accessors / queries:
///------------------------------------------------------
bool IsPointInside( const Vector2& point ) const;
inline const Vector2 CalcSize() const;
inline const Vector2 CalcCenter() const;
inline const Vector2 GetPointAtNormalizedPositionWithinBox( const Vector2& normalizedPosition ) const;
inline const Vector2 GetNormalizedPositionForPointWithinBox( const Vector2& point ) const;

///------------------------------------------------------
///Operators:
///------------------------------------------------------
inline const AABB2D operator + ( const Vector2& translation ) const;
inline const AABB2D operator - ( const Vector2& antiTranslation ) const;
inline void operator += ( const Vector2& translation );
inline void operator -= ( const Vector2& antiTranslation );

static const AABB2D ZERO_TO_ONE;
};


#endif

void AABB2D::AddPadding( float xPaddingRadius, float yPaddingRadius )
{
	mins.x -= xPaddingRadius;
	mins.y -= yPaddingRadius;
	maxs.x += xPaddingRadius;
	maxs.y += yPaddingRadius;
}

void AABB2D::Translate( const Vector2& translation )
{
	mins += translation;
	maxs += translation;
	
}

void AABB2D::SetMinsAndMaxs(const Vector2& Mins, const Vector2& Maxs)
{
	mins = Mins;
	maxs = Maxs;
}

const Vector2 AABB2D::CalcSize() const
{
	Vector2 boxSize;
	boxSize.x = maxs.x-mins.x;
	boxSize.y = maxs.y-mins.y;
	return boxSize;
}
const Vector2 AABB2D::CalcCenter() const
{
	Vector2 boxCenter;
	boxCenter = (mins + maxs)* 0.5;
	return boxCenter;
}
const Vector2 AABB2D::GetPointAtNormalizedPositionWithinBox( const Vector2& normalizedPosition ) const
{
	Vector2 position;
	position = (maxs - mins) * normalizedPosition + mins;
	return position;
	
}
const Vector2 AABB2D::GetNormalizedPositionForPointWithinBox( const Vector2& point ) const
{
	Vector2 position;
	position.x = ( point.x - mins.x ) / ( maxs.x - mins.x );
	position.y = ( point.y - mins.y ) / ( maxs.y - mins.y );	
	return position;
}

///------------------------------------------------------
///operator
///------------------------------------------------------

const AABB2D AABB2D::operator + ( const Vector2& translation ) const
{
	AABB2D box;
	box.mins+= translation;
	box.maxs+= translation;
	return box;

}
const AABB2D AABB2D::operator - ( const Vector2& antiTranslation ) const
{
	AABB2D box;
	box.mins-= antiTranslation;
	box.maxs-= antiTranslation;
	return box;
}
void AABB2D::operator += ( const Vector2& translation )
{
	mins += translation;
	maxs += translation;
}
void AABB2D::operator -= ( const Vector2& antiTranslation )
{
	mins -= antiTranslation;
	maxs -= antiTranslation;
}