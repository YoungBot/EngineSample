//==========================================================
//MathUtils.hpp
//==========================================================
#ifndef	MATHUTILS_HPP
#define	MATHUTILS_HPP 

#include <stdlib.h>
#include <math.h>
#include <assert.h>

#ifndef PI
const float PI = 3.1415926f;
#endif // !PI

const float	DegreePI = 180.0f;
const float RAD2DEG = (float)DegreePI/PI ;
const float DEG2RAD = (float)PI/DegreePI;

class MathUtils
{

public:
	MathUtils();
	~MathUtils();
	static 	inline float ConvertRadiansToDegrees( float radians );
	static 	inline float ConvertDegreesToRadians( float degrees );
	static 	inline int GetRandomIntLessThan( int maxValueNotInclusive );
	static 	inline int GetRandomIntInRange( int minValueInclusive, int maxValueInclusive );
	static 	inline float GetRandomFloatZeroToOne();
	static 	inline float GetRandomFloatInRange( float minimumInclusive, float maximumInclusive );
	
	static  inline float CalcShortestAngularDisplacement( float startAngle, float destinationAngle );
	static	inline bool IsPowerOfTwo( int x );
	static  inline float RangeMap( float inValue, float inStart, float inEnd, float outStart, float outEnd );
	static  inline float Clamp( float inValue, float min, float max );
	static  inline float SmoothStart( float normalizedValue );
	static  inline float SmoothStop( float normalizedValue );
	static  inline float SmoothStep( float normalizedValue );
	static  inline float AsymptoticAdd( float normalizedValueA, float normalizedValueB );
	static  inline float Interpolate( float start, float end, float fractionFromStartToEnd );	
	static  inline int   RoundDownToInt(float f);
	static  inline int RoundUpToInt(float f);
};



float MathUtils:: Clamp( float inValue, float min, float max )
{

	if (inValue<min)
	{
		return min;
	}
	else if (inValue>max)
	{
		return max;
	}
	else
		return inValue;
}

float MathUtils::SmoothStart( float normalizedValue )
{
	return normalizedValue*normalizedValue;
}
float MathUtils::SmoothStop( float normalizedValue )
{
	return 1-(normalizedValue-1)*(normalizedValue-1);
}
float MathUtils::SmoothStep( float normalizedValue )
{
	float square = normalizedValue*normalizedValue;
	return 3*square -2*square*normalizedValue;
}
float MathUtils::RangeMap( float inValue, float inStart, float inEnd, float outStart, float outEnd )
{
	return (inValue-inStart) / (inEnd-inStart) * (outEnd-outStart) + outStart;
}

bool MathUtils::IsPowerOfTwo( int x )
{
	if ( ((x & ( x - 1 )) ==0) && x>0)
	{
		return true;
	}
	else
		return false;
}

float MathUtils::AsymptoticAdd( float normalizedValueA, float normalizedValueB )
{
	return 1-((1-normalizedValueA)*(1-normalizedValueB));
}

float MathUtils::Interpolate( float start, float end, float fractionFromStartToEnd )
{
	float result;
	result = start + fractionFromStartToEnd*(end-start);
	return result;
}

///------------------------------------------------------
///	convert Number
///------------------------------------------------------
float MathUtils::ConvertDegreesToRadians( float degrees )
{

	return degrees * DEG2RAD;

}

float MathUtils::ConvertRadiansToDegrees( float radians )
{
	return radians * RAD2DEG;
}
///------------------------------------------------------
///Get random Number
///------------------------------------------------------
int MathUtils::GetRandomIntLessThan( int maxValueNotInclusive )
{
	int randomInt;
	randomInt =  rand() % maxValueNotInclusive; 
	return randomInt;
}
int MathUtils::GetRandomIntInRange( int minValueInclusive, int maxValueInclusive )
{
	if(minValueInclusive < maxValueInclusive)
	{

		int randomInt;
		randomInt =  ( rand() % (maxValueInclusive - minValueInclusive +1 ) )+ minValueInclusive; 
		return randomInt;

	}
	else
	{
		return 0; //Need to be edited
	}
}
float MathUtils::GetRandomFloatZeroToOne()
{
	float randomFloat;
	randomFloat =   rand()* (1/ float(RAND_MAX));  
	return randomFloat;
}
float MathUtils::GetRandomFloatInRange( float minimumInclusive, float maximumInclusive )
{
	if(minimumInclusive < maximumInclusive)
	{	
		float randomFloat;
		randomFloat =   rand()  /  ( float(RAND_MAX) / (maximumInclusive-minimumInclusive) ) + minimumInclusive;  
		return randomFloat;
	}
	else
	{
		return 0; //Need to be edited
	}
}

int  MathUtils::RoundDownToInt(float f)
{
	if(f<0.0f)
	{
		
		return (int)(f)-1;
	}
	else
		return int(f);
}
///----------------------------------------------------------
///
///----------------------------------------------------------

int  MathUtils::RoundUpToInt(float f)
{
	if (f < 0.0f)
	{

		return (int)(f);
	}
	else
		return int(f);
}

#endif