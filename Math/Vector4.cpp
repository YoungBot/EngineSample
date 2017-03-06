//==========================================================
//Vector4.cpp
//==========================================================

#include "Vector4.hpp"

Vector4::Vector4()
{
}
///------------------------------------------------------
///
///------------------------------------------------------

Vector4:: Vector4(const Vector4& copy )
{
	x=copy.x;
	y=copy.y;
	z=copy.z;
	w=copy.w;
}
///------------------------------------------------------
///
///------------------------------------------------------

Vector4::Vector4 ( float initialX, float initialY, float initialZ, float initialW )
{
	x = initialX;
	y = initialY;
	z = initialZ;
	w = initialW;
}
///------------------------------------------------------
///
///------------------------------------------------------

Vector4::~Vector4()
{

}
///------------------------------------------------------
///
///------------------------------------------------------

void Vector4::GetXYZW( float& out_x, float& out_y, float& out_z, float& out_w ) const
{
	out_x = x;
	out_y = y;
	out_z = z;
	out_w = w;
}
///------------------------------------------------------
///
///------------------------------------------------------


const float* Vector4::GetAsFloatArray() const
{
	return &x;
}
float* Vector4::GetAsFloatArray()
{
	return &x;
}


float Vector4::CalcLength() const
{
	float length;
	length = sqrt( x * x + y * y + z * z + w * w);
	return length;
}
///------------------------------------------------------
///
///------------------------------------------------------

float Vector4::CalcLengthSquared()const
{
	float length;
	length = sqrt( x * x + y * y + z * z + w * w);
	return length*length;
}

void Vector4::SetXYZW( float newX, float newY, float newZ, float newW )
{
	x = newX;
	y = newY;
	z = newZ;
	w = newW;
}
///------------------------------------------------------
///
///------------------------------------------------------

float Vector4::Normalize4D()
{
	float Length;
	Length =sqrt( x * x + y * y + z * z + w * w);
	float inverse = 0.0f;
	if ( Length != 0 )
	{
		inverse = (1.0f / Length);
		x *= inverse;
		y *= inverse;
		z *= inverse;
		w *= inverse;
	}
	return inverse;
}
///------------------------------------------------------
///
///------------------------------------------------------
float Vector4::Normalize3D()
{
	float Length;
	Length =sqrt( x * x + y * y + z * z);
	float inverse = 0.0F;
	if ( Length != 0 )
	{
		inverse = (1.0f / Length);
		x *= inverse;
		y *= inverse;
		z *= inverse;
	}
	return inverse;
}
///------------------------------------------------------
///
///------------------------------------------------------

float Vector4::SetLength( float newLength )
{
	float inverse = Normalize4D();
	x= x * newLength;
	y= y * newLength;
	z= z * newLength;
	w= w * newLength;
	return inverse;
}

///------------------------------------------------------
///
///------------------------------------------------------

void Vector4::ScaleUniform( float scale )
{
	x*= scale;
	y*= scale;
	z*= scale;
	w*= scale;
}
///------------------------------------------------------
///
///------------------------------------------------------

void Vector4::ScaleNonUniform( const Vector4& perAxisScaleFactors )
{
	x*= perAxisScaleFactors.x;
	y*= perAxisScaleFactors.y;
	z*= perAxisScaleFactors.z;
	w*= perAxisScaleFactors.w;
}
///------------------------------------------------------
///
///------------------------------------------------------

void Vector4::InverseScaleNonUniform( const Vector4& perAxisDivisors )
{
	ScaleNonUniform(perAxisDivisors);
	if (x==0 || y ==0|| z==0 || w==0)
	{
		return;
	}
	
	
	x = 1/x;
	y = 1/y;
	z = 1/z;
	w = 1/w;
}
///------------------------------------------------------
///
///------------------------------------------------------


bool Vector4::operator == ( const Vector4& vectorToEqual ) const
{
	if (CalcLengthSquared() == vectorToEqual.CalcLengthSquared())
	{
		return true;
	}
	else
	{
		return false;
	}
}
///------------------------------------------------------
///
///------------------------------------------------------

bool Vector4::operator != ( const Vector4& vectorToNotEqual ) const
{
	if (x == vectorToNotEqual.x && y==vectorToNotEqual.y && z == vectorToNotEqual.z)
	{
		return false;
	}
	else 
		return true;
}
///------------------------------------------------------
///
///------------------------------------------------------

const Vector4 Vector4::operator + ( const Vector4& vectorToAdd ) const
{
	Vector4 outputVec;
	outputVec.x = x + vectorToAdd.x ;
	outputVec.y = y + vectorToAdd.y ; 
	outputVec.z = z + vectorToAdd.z ;
	outputVec.w = w + vectorToAdd.w ;
	return outputVec;
}
///------------------------------------------------------
///
///------------------------------------------------------

const Vector4 Vector4::operator - ( const Vector4& vectorToSubtract ) const
{
	Vector4 outputVec;
	outputVec.x = x - vectorToSubtract.x ;
	outputVec.y = y - vectorToSubtract.y ; 
	outputVec.z = z - vectorToSubtract.z ;
	outputVec.w = w - vectorToSubtract.w ;
	return outputVec;
}
///------------------------------------------------------
///
///------------------------------------------------------

const Vector4 Vector4::operator * ( float scale ) const
{
	Vector4 outputVec;
	outputVec.x = x * scale;
	outputVec.y = y * scale;
	outputVec.z = z * scale;
	outputVec.w = w * scale;
	return outputVec;
}
///------------------------------------------------------
///
///------------------------------------------------------

const Vector4 Vector4::operator * ( const Vector4& perAxisScaleFactors ) const
{
	Vector4 outputVec;
	outputVec.x = x * perAxisScaleFactors.x;
	outputVec.y = y * perAxisScaleFactors.y;
	outputVec.z = z * perAxisScaleFactors.z;
	outputVec.w = w * perAxisScaleFactors.w;
	return outputVec;
}
///------------------------------------------------------
///
///------------------------------------------------------

const Vector4 Vector4::operator / ( float inverseScale ) const
{
	Vector4 outputVec;
	if (inverseScale!=0.0f)
	{
		inverseScale = 1/inverseScale;
		outputVec.x = x * inverseScale;
		outputVec.y = y * inverseScale;
		outputVec.z = z * inverseScale;
		outputVec.w = w * inverseScale;
		return outputVec;
	}
	else
		return Vector4(0.0f,0.0f,0.0f,0.0f);
}
///------------------------------------------------------
///
///------------------------------------------------------

void  Vector4::operator *= ( float scale )
{
	x *= scale;
	y *= scale;
	z *= scale;
	w *= scale;
}
///------------------------------------------------------
///
///------------------------------------------------------

void  Vector4::operator *= ( const Vector4& perAxisScaleFactors )
{
	x *= perAxisScaleFactors.x;
	y *= perAxisScaleFactors.y;
	z *= perAxisScaleFactors.z;
	w *= perAxisScaleFactors.w;
}
///------------------------------------------------------
///
///------------------------------------------------------

void  Vector4::operator += ( const Vector4& vectorToAdd )
{
	x += vectorToAdd.x;
	y += vectorToAdd.y;
	z += vectorToAdd.z;
	w += vectorToAdd.w;
}
///------------------------------------------------------
///
///------------------------------------------------------

void  Vector4::operator -= ( const Vector4& vectorToSubtract )
{
	x -= vectorToSubtract.x;
	y -= vectorToSubtract.y;
	z -= vectorToSubtract.z;
	w -= vectorToSubtract.w;
}
///------------------------------------------------------
///
///------------------------------------------------------

void* Vector4::operator = (const Vector4 &copy)
{
	x = copy.x;
	y = copy.y;
	z = copy.z;
	w = copy.w;
	return this;
}
///------------------------------------------------------
///
///------------------------------------------------------

void Vector4::SetVector3InVector4(const Vector3& inputVector3)
{
	x = inputVector3.x;
	y = inputVector3.y;
	z = inputVector3.z;
}
///------------------------------------------------------
///
///------------------------------------------------------

void Vector4::SetVector2InVector4(const Vector2& inputVector2)
{
	x = inputVector2.x;
	y = inputVector2.y;
}
///------------------------------------------------------
///
///------------------------------------------------------

float CalcDistance( const Vector4& positionA, const Vector4& positionB )
{
	Vector4 outputVec;
	outputVec = positionA - positionB;
	return outputVec.CalcLength();
}
///------------------------------------------------------
///
///------------------------------------------------------

float CalcDistanceSquared( const Vector4& positionA, const Vector4& positionB )
{
	Vector4 outputVec;
	outputVec = positionA - positionB;
	return outputVec.CalcLengthSquared();
}
///------------------------------------------------------
///
///------------------------------------------------------

const Vector4 operator * ( float scale, const Vector4& vectorToScale )
{
	Vector4 outputVec;
	outputVec.x = scale * vectorToScale.x;
	outputVec.y = scale * vectorToScale.y;
	outputVec.z = scale * vectorToScale.z;
	outputVec.w = scale * vectorToScale.w;
	return outputVec;
}
///------------------------------------------------------
///
///------------------------------------------------------
float DotProduct( const Vector4& a, const Vector4& b )
{
	return (a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w) ;
}
///------------------------------------------------------
///
///------------------------------------------------------

