//==========================================================
//Vector2.hpp
//==========================================================
#pragma once
#ifndef _VECTOR2_HPP_
#define _VECTOR2_HPP_

#include "MathUtils.hpp"

class Vector2
{	
public:
	// MathUtils maths;
	float x;
	float y;
	Vector2();
	Vector2( const Vector2& copy )	;
	explicit Vector2 ( float initialX, float initialY );	
	~Vector2();

	void GetXY( float& out_x, float& out_y ) const;
	const float* GetAsFloatArray() const;
	float* GetAsFloatArray();
	float CalcLength() const;
	float CalcLengthSquared() const;
	float CalcHeadingDegrees() const;
	float CalcHeadingRadians() const;

	void SetXY( float newX, float newY );
	void Rotate90Degrees();
	void RotateNegative90Degrees();
	void RotateDegrees( float degrees );
	void RotateRadians( float radians );
	float Normalize();
	float SetLength( float newLength );		
	void ScaleUniform( float scale );
	void ScaleNonUniform( const Vector2& perAxisScaleFactors );
	void InverseScaleNonUniform( const Vector2& perAxisDivisors );
	void SetUnitLengthAndHeadingDegrees( float headingDegrees );
	void SetUnitLengthAndHeadingRadians( float headingRadians );
	void SetLengthAndHeadingDegrees( float newLength, float headingDegrees );
	void SetLengthAndHeadingRadians( float newLength, float headingRadians );

	bool operator == ( const Vector2& vectorToEqual ) const;
	bool operator != ( const Vector2& vectorToNotEqual ) const;
	const Vector2 operator + ( const Vector2& vectorToAdd ) const;
	const Vector2 operator - ( const Vector2& vectorToSubtract ) const;
	const Vector2 operator * ( float scale ) const;
	const Vector2 operator * ( const Vector2& perAxisScaleFactors ) const;
	const Vector2 operator / ( float inverseScale ) const;
	void  operator *= ( float scale );
	void  operator *= ( const Vector2& perAxisScaleFactors );
	void  operator += ( const Vector2& vectorToAdd );
	void  operator -= ( const Vector2& vectorToSubtract );
	void* operator = (const Vector2 &copy);

	friend float CalcDistance( const Vector2& positionA, const Vector2& positionB );
	friend float CalcDistanceSquared( const Vector2& positionA, const Vector2& positionB );
	friend const Vector2 operator * ( float scale, const Vector2& vectorToScale );
	friend float DotProduct( const Vector2& a, const Vector2& b );		

	static const Vector2 ZERO;
	static const Vector2 ONE;
};



#endif

