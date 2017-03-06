//==========================================================
//Vector3.cpp
//==========================================================

#include "Vector3.hpp"

Vector3::Vector3()
{
}
///------------------------------------------------------
///
///------------------------------------------------------

Vector3:: Vector3(const Vector3& copy )
{
	x=copy.x;
	y=copy.y;
	z=copy.z;
}
///------------------------------------------------------
///
///------------------------------------------------------

Vector3::Vector3 ( float initialX, float initialY, float initialZ )
{
	x = initialX;
	y = initialY;
	z = initialZ;
}
///------------------------------------------------------
///
///------------------------------------------------------

Vector3::~Vector3()
{

}
///------------------------------------------------------
///
///------------------------------------------------------

const Vector3 Vector3::ZERO(0.f, 0.f, 0.f);
const Vector3 Vector3::ONE(1.f, 1.f, 1.f);
///----------------------------------------------------------
///
///----------------------------------------------------------


void Vector3::GetXYZ( float& out_x, float& out_y, float& out_z ) const
{
	out_x = x;
	out_y = y;
	out_z = z;
}
///------------------------------------------------------
///
///------------------------------------------------------


const float* Vector3::GetAsFloatArray() const
{
	return &x;
}
float* Vector3::GetAsFloatArray()
{
	return &x;
}


float Vector3::CalcLength() const
{
	float length;
	length = sqrt( x * x + y * y + z * z);
	return length;
}
///------------------------------------------------------
///
///------------------------------------------------------

float Vector3::CalcLengthSquared()const
{
	float length;
	length = sqrt( x * x + y * y + z * z);
	return length*length;
}

void Vector3::SetXYZ( float newX, float newY, float newZ )
{
	x = newX;
	y = newY;
	z = newZ;
}
///------------------------------------------------------
///
///------------------------------------------------------

float Vector3::Normalize()
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

float Vector3::SetLength( float newLength )
{
	float inverse = Normalize();
	x= x * newLength;
	y= y * newLength;
	z= z * newLength;
	return inverse;
}
///------------------------------------------------------
///
///------------------------------------------------------

void Vector3::ScaleUniform( float scale )
{
	x*= scale;
	y*= scale;
	z*= scale;
}
///------------------------------------------------------
///
///------------------------------------------------------

void Vector3::ScaleNonUniform( const Vector3& perAxisScaleFactors )
{
	x*= perAxisScaleFactors.x;
	y*= perAxisScaleFactors.y;
	z*= perAxisScaleFactors.z;
}
///------------------------------------------------------
///
///------------------------------------------------------

void Vector3::InverseScaleNonUniform( const Vector3& perAxisDivisors )
{
	ScaleNonUniform(perAxisDivisors);
	x = 1/x;
	y = 1/y;
	z = 1/z;
}
///------------------------------------------------------
///
///------------------------------------------------------


bool Vector3::operator == ( const Vector3& vectorToEqual ) const
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

bool Vector3::operator != ( const Vector3& vectorToNotEqual ) const
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

const Vector3 Vector3::operator + ( const Vector3& vectorToAdd ) const
{
	Vector3 outputVec;
	outputVec.x = x + vectorToAdd.x ;
	outputVec.y = y + vectorToAdd.y ; 
	outputVec.z = z + vectorToAdd.z ;
	return outputVec;
}
///------------------------------------------------------
///
///------------------------------------------------------

const Vector3 Vector3::operator - ( const Vector3& vectorToSubtract ) const
{
	Vector3 outputVec;
	outputVec.x = x - vectorToSubtract.x ;
	outputVec.y = y - vectorToSubtract.y ; 
	outputVec.z = z - vectorToSubtract.z ;
	return outputVec;
}
///------------------------------------------------------
///
///------------------------------------------------------

const Vector3 Vector3::operator * ( float scale ) const
{
	Vector3 outputVec;
	outputVec.x = x * scale;
	outputVec.y = y * scale;
	outputVec.z = z * scale;
	return outputVec;
}
///------------------------------------------------------
///
///------------------------------------------------------

const Vector3 Vector3::operator * ( const Vector3& perAxisScaleFactors ) const
{
	Vector3 outputVec;
	outputVec.x=x* perAxisScaleFactors.x;
	outputVec.y=y* perAxisScaleFactors.y;
	outputVec.z=z* perAxisScaleFactors.z;
	return outputVec;
}
///------------------------------------------------------
///
///------------------------------------------------------

const Vector3 Vector3::operator / ( float inverseScale ) const
{
	Vector3 outputVec;
	if (inverseScale!=0.0f)
	{
		inverseScale = 1/inverseScale;
		outputVec.x = x * inverseScale;
		outputVec.y = y * inverseScale;
		outputVec.z = z * inverseScale;
		return outputVec;
	}
	else
		return Vector3(0.0f,0.0f,0.0f);
}
///------------------------------------------------------
///
///------------------------------------------------------

void  Vector3::operator *= ( float scale )
{
	x *= scale;
	y *= scale;
	z *= scale;
}
///------------------------------------------------------
///
///------------------------------------------------------

void  Vector3::operator *= ( const Vector3& perAxisScaleFactors )
{
	x *= perAxisScaleFactors.x;
	y *= perAxisScaleFactors.y;
	z *= perAxisScaleFactors.z;
}
///------------------------------------------------------
///
///------------------------------------------------------

void  Vector3::operator += ( const Vector3& vectorToAdd )
{
	x += vectorToAdd.x;
	y += vectorToAdd.y;
	z += vectorToAdd.z;
}
///------------------------------------------------------
///
///------------------------------------------------------

void  Vector3::operator -= ( const Vector3& vectorToSubtract )
{
	x -= vectorToSubtract.x;
	y -= vectorToSubtract.y;
	z -= vectorToSubtract.z;
}
///------------------------------------------------------
///
///------------------------------------------------------

void* Vector3::operator = (const Vector3 &copy)
{
	x = copy.x;
	y = copy.y;
	z = copy.z;
	return this;
}
///------------------------------------------------------
///
///------------------------------------------------------

float CalcDistance( const Vector3& positionA, const Vector3& positionB )
{
	Vector3 outputVec;
	outputVec = positionA - positionB;
	return outputVec.CalcLength();
}
///------------------------------------------------------
///
///------------------------------------------------------

float CalcDistanceSquared( const Vector3& positionA, const Vector3& positionB )
{
	Vector3 outputVec;
	outputVec = positionA - positionB;
	return outputVec.CalcLengthSquared();
}
///------------------------------------------------------
///
///------------------------------------------------------

const Vector3 operator * ( float scale, const Vector3& vectorToScale )
{
	Vector3 outputVec;
	outputVec.x = scale * vectorToScale.x;
	outputVec.y = scale * vectorToScale.y;
	outputVec.z = scale * vectorToScale.z;
	return outputVec;
}
///------------------------------------------------------
///
///------------------------------------------------------
float DotProduct( const Vector3& a, const Vector3& b )
{
	return (a.x * b.x + a.y * b.y + a.z*b.z) ;
}
///------------------------------------------------------
///
///------------------------------------------------------

Vector3 Vector3::Interpolate( Vector3& start, Vector3& end, float fractionFromStartToEnd )
{
	Vector3 result;
	result.x = start.x + fractionFromStartToEnd*(end.x-start.x);
	result.y = start.y + fractionFromStartToEnd*(end.y-start.y);
	result.z = start.z + fractionFromStartToEnd*(end.z-start.z);
	return result;
}
///------------------------------------------------------
///
///------------------------------------------------------
Vector3 Vector3::CrossProduct(const Vector3& a, const Vector3& b)
{
	Vector3 result;
	result.x = a.y*b.z - b.y*a.z;
	result.y = a.z*b.x - b.z*a.x;
	result.z = a.x*b.y - b.x*a.y;
	return result;
}