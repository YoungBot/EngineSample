//==========================================================
//Vector2.cpp
//==========================================================
#include "Vector2.hpp"


///------------------------------------------------------
///	construct and destruct
///------------------------------------------------------
Vector2::Vector2()
{
	
}

Vector2::Vector2( const Vector2& copy )
	:x(copy.x)
	,y(copy.y)
{
	
}

Vector2::Vector2 ( float initialX, float initialY )
	:x(initialX)
	,y(initialY)
{
	
}
Vector2::~Vector2()
{
}
///----------------------------------------------------------
///
///----------------------------------------------------------
const Vector2 Vector2::ZERO(0.0f,0.0f);
const Vector2 Vector2::ONE(1.0f,1.0f);


///------------------------------------------------------
///Accessors
///------------------------------------------------------

void Vector2::GetXY( float& out_x, float& out_y ) const
{
	out_x = x;
	out_y = y;
}

const float* Vector2::GetAsFloatArray() const
{
	float* FloatArray= new float[2]; //FloatArray[2];
	FloatArray[0] = x;
	FloatArray[1] = y;

	return FloatArray;
}

float* Vector2::GetAsFloatArray()
{
	return &x;
}

float Vector2::CalcLength() const
{
	float length;
	length = sqrt( x * x + y * y );
	return length;
}

float Vector2::CalcLengthSquared() const
{
	float LengthSquared;
	LengthSquared = x * x + y * y;
	return LengthSquared;
}

float Vector2::CalcHeadingRadians() const
{
	float Degrees;
	Degrees = atan2(y,x);
	return Degrees;
}

float Vector2::CalcHeadingDegrees() const
{
	float Degrees,Radians;
	Degrees = atan2(y,x);
	Radians = Degrees * RAD2DEG;
	return Radians;

}

///------------------------------------------------------
///	Mutators
///------------------------------------------------------

void Vector2::SetXY( float newX, float newY )
{
	x = newX;
	y = newY;
}
void Vector2::Rotate90Degrees()
{
	float Length,Degrees;
	Length = CalcLength();
	Degrees = atan2( y , x ) + PI/2;

	x = Length * cos(Degrees);
	y = Length * sin(Degrees);

	
}

void Vector2::RotateNegative90Degrees()
{
	float Length,Degrees;
	Length = CalcLength();
	Degrees = atan2( y , x ) - PI/2;

	x = Length * cos(Degrees);
	y = Length * sin(Degrees);
}

void Vector2::RotateDegrees( float degrees )
{
	float Length,Degrees;
	Length = CalcLength();
	Degrees = atan2( y , x )+ degrees *DEG2RAD;

	x = Length * cos(Degrees);
	y = Length * sin(Degrees);


}

void Vector2::RotateRadians( float radians )
{
	float Length,Radians;
	Length = CalcLength();
	Radians =  atan2( y , x ) + radians;
	

	x = Length * cos(Radians);
	y = Length * sin(Radians);
}

float Vector2::Normalize()
{
	float Length;
	Length =sqrt( x * x + y * y);
	float inverse = 0.0F;

	if ( Length != 0 )
	{
		inverse = (1.0f / Length);
		x *= inverse;
		y *= inverse;
	}

	return inverse;

}

float Vector2::SetLength( float newLength )
{	
	float inverse = Normalize();
	x= x * newLength;
	y= y * newLength;

	return inverse;
}
void Vector2::ScaleUniform( float scale )
{
	x*= scale;
	y*= scale;
}

void Vector2::ScaleNonUniform( const Vector2& perAxisScaleFactors )
{
	x*= perAxisScaleFactors.x;
	y*= perAxisScaleFactors.y;
}
void Vector2::InverseScaleNonUniform( const Vector2& perAxisDivisors )
{
	ScaleNonUniform(perAxisDivisors);
	x = 1/x;
	y = 1/y;
}
void Vector2::SetUnitLengthAndHeadingDegrees( float headingDegrees )
{
	float Radians = headingDegrees * DEG2RAD;
	x = cos(Radians);
	y = sin(Radians);	
}
void Vector2::SetUnitLengthAndHeadingRadians( float headingRadians )
{
	
	x = cos(headingRadians);
	y = sin(headingRadians);
}
void Vector2::SetLengthAndHeadingDegrees( float newLength, float headingDegrees )
{
	x = cos(headingDegrees*DEG2RAD) * newLength;
	y = sin(headingDegrees*DEG2RAD) * newLength;
}

void Vector2::SetLengthAndHeadingRadians( float newLength, float headingRadians )
{
	x = cos(headingRadians) * newLength;
	y = sin(headingRadians) * newLength;
}
///------------------------------------------------------
///
///------------------------------------------------------
bool Vector2::operator == ( const Vector2& vectorToEqual ) const
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
bool Vector2::operator != ( const Vector2& vectorToNotEqual ) const
{
	if (CalcLengthSquared() == vectorToNotEqual.CalcLengthSquared() && CalcHeadingDegrees() == vectorToNotEqual.CalcHeadingDegrees())
	{
		return false;
	}
	else
	{
		return true;
	}
}
const Vector2 Vector2::operator + ( const Vector2& vectorToAdd ) const
{
	Vector2 outputVec;
	outputVec.x = x + vectorToAdd.x ;
	outputVec.y = y + vectorToAdd.y ; 

	return outputVec;
}
const Vector2 Vector2::operator - ( const Vector2& vectorToSubtract ) const
{
	Vector2 outputVec;
	outputVec.x = x - vectorToSubtract.x ;
	outputVec.y = y - vectorToSubtract.y ; 

	return outputVec;
}
const Vector2 Vector2::operator * ( float scale ) const
{
	Vector2 outputVec;
	outputVec.x= x* scale;
	outputVec.y=y* scale;
	return outputVec;
}
const Vector2 Vector2::operator * ( const Vector2& perAxisScaleFactors ) const
{
	Vector2 outputVec;
	outputVec.x=x* perAxisScaleFactors.x;
	outputVec.y=y* perAxisScaleFactors.y;
	return outputVec;
}
const Vector2 Vector2::operator / ( float inverseScale ) const
{
	Vector2 outputVec;
	outputVec.x = x / inverseScale;
	outputVec.y = y / inverseScale;
	return outputVec;
}
void  Vector2::operator *= ( float scale )
{
	x *= scale;
	y *= scale;
}
void  Vector2::operator *= ( const Vector2& perAxisScaleFactors )
{
	x *= perAxisScaleFactors.x;
	y *= perAxisScaleFactors.y;
}
void  Vector2::operator += ( const Vector2& vectorToAdd )
{
	x += vectorToAdd.x;
	y += vectorToAdd.y;
}
void  Vector2::operator -= ( const Vector2& vectorToSubtract )
{
	x -= vectorToSubtract.x;
	y -= vectorToSubtract.y;
}
void* Vector2::operator = (const Vector2 &copy)
{
	x = copy.x;
	y = copy.y;
	return this;
}

///------------------------------------------------------
///
///------------------------------------------------------

float CalcDistance( const Vector2& positionA, const Vector2& positionB )
{
	Vector2 outputVec;
	outputVec = positionA - positionB;
	return outputVec.CalcLength();
}
float CalcDistanceSquared( const Vector2& positionA, const Vector2& positionB )
{
	Vector2 outputVec;
	outputVec = positionA - positionB;
	return outputVec.CalcLengthSquared();
}
const Vector2 operator * ( float scale, const Vector2& vectorToScale )
{
	Vector2 outputVec;
	outputVec.x = scale * vectorToScale.x;
	outputVec.y = scale * vectorToScale.y;
	return outputVec;
}
float DotProduct( const Vector2& a, const Vector2& b )
{
	return (a.x * b.x + a.y * b.y) ;
}
