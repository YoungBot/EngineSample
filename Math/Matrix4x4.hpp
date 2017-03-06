#pragma once

#ifndef _Matrix4x4_HPP_
#define _Matrix4x4_HPP_
#include "Engine\Math\Vector2.hpp"
#include "Engine\Math\Vector3.hpp"
#include "Engine\Math\Vector4.hpp"

class Matrix4x4
{
public:
	Matrix4x4();
	Matrix4x4(const Matrix4x4& copy );
	Matrix4x4(const Vector2& iBasis, const Vector2& jBasis);
	Matrix4x4(const Vector2& iBasis, const Vector2& jBasis, const Vector2& translation);
	Matrix4x4(const Vector3& iBasis, const Vector3& jBasis, const Vector3& kBasis);
	Matrix4x4(const Vector3& iBasis, const Vector3& jBasis, const Vector3& kBasis, const Vector3& translation);
	Matrix4x4(const Vector4& iBasis, const Vector4& jBasis, const Vector4& kBasis, const Vector4& translation);
	~Matrix4x4();
	//////////////////////////////////////////////////////////////////////////
	void MakeIdentity();
	void* operator = (const Matrix4x4 &copy);
	//////////////////////////////////////////////////////////////////////////
	const float* GetAsFloatArray() const;
	float* GetAsFloatArray();
	//////////////////////////////////////////////////////////////////////////
	void Transform(Matrix4x4& transformMatrix);
	const Matrix4x4 GetTransformed(Matrix4x4& transformMatrix);
	Vector2 TransformPosition( const Vector2& position2D ) const; // Hardcoded to assume z=0, w=1
	Vector3 TransformPosition( const Vector3& position3D ) const; // Hardcoded to assume w=1
	Vector2 TransformDirection( const Vector2& direction2D ) const; // Hardcoded to assume z=0, w=0
	Vector3 TransformDirection( const Vector3& direction3D ) const; // Hardcoded to assume w=0
	Vector4 TransformVector( const Vector4& homogeneousVector ) const; // w is provided
	//////////////////////////////////////////////////////////////////////////
	void Translate( const Vector2& translation2D ); // z translation assumed to be 0
	void Translate( const Vector3& translation3D );
	void Transpose();
	void Scale( float uniformScale ); 
	void Scale( const Vector2& nonUniformScale2D ); // z scale assumed to be 1
	void Scale( const Vector3& nonUniformScale3D );
	void RotateDegreesAboutX( float degrees );
	void RotateDegreesAboutY( float degrees );
	void RotateDegreesAboutZ( float degrees );// Possibly also offered as RotateDegrees2D
	void RotateRadiansAboutX( float radians );
	void RotateRadiansAboutY( float radians );
	void RotateRadiansAboutZ( float radians );// Possibly also offered as RotateRadians2D
	//////////////////////////////////////////////////////////////////////////
	static Matrix4x4 CreateTranslation( const Vector2& translation2D ); // z translation assumed to be 0
	static Matrix4x4 CreateTranslation( const Vector3& translation3D );
	static Matrix4x4 CreateScale( float uniformScale );
	static Matrix4x4 CreateScale( const Vector2& nonUniformScale2D ); // z scale assumed to be 1
	static Matrix4x4 CreateScale( const Vector3& nonUniformScale3D );
	static Matrix4x4 CreateRotationDegreesAboutX( float degrees );
	static Matrix4x4 CreateRotationDegreesAboutY( float degrees );
	static Matrix4x4 CreateRotationDegreesAboutZ( float degrees ); // a.k.a. CreateRotationDegrees2D
	static Matrix4x4 CreateRotationRadiansAboutX( float radians );
	static Matrix4x4 CreateRotationRadiansAboutY( float radians );
	static Matrix4x4 CreateRotationRadiansAboutZ( float radians ); // a.k.a. CreateRotationRadians2D
	
	static void Mult(const Matrix4x4& l, const Matrix4x4& r, Matrix4x4& res);
	static const Matrix4x4 I;
	
	Vector4 m_iBasis;
	Vector4 m_jBasis;
	Vector4 m_kBasis;
	Vector4 m_translation;
};



#endif