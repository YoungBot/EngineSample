//==========================================================
//IntVector2.hpp
//==========================================================

#pragma once

#ifndef _INTVector2_HPP_
#define _INTVector2_HPP_

class IntVector2
{
public:
	IntVector2();
	~IntVector2();
	IntVector2(int x,int y);
	static float CaculateDistance(IntVector2 startPos, IntVector2 endPos);
	int x;
	int y;


	inline const IntVector2 operator + (const IntVector2& vectorToAdd) const;
	inline const IntVector2 operator - (const IntVector2& vectorToAdd) const;
	inline  bool operator < (const IntVector2& compare) const;
};

inline IntVector2::IntVector2()
{

}

inline IntVector2::IntVector2(int x,int y)
{
	this->x = x;
	this->y = y;
}

inline IntVector2::~IntVector2()
{

}

inline const IntVector2 IntVector2::operator + ( const IntVector2& vectorToAdd ) const
{
	IntVector2 outputVec;
	outputVec.x += vectorToAdd.x ;
	outputVec.y += vectorToAdd.y ; 
	return outputVec;
}

inline const IntVector2 IntVector2::operator - ( const IntVector2& vectorToAdd ) const
{
	IntVector2 outputVec;
	outputVec.x -= vectorToAdd.x ;
	outputVec.y -= vectorToAdd.y ; 
	return outputVec;
}

///------------------------------------------------------
///
///------------------------------------------------------

inline bool IntVector2::operator < (const IntVector2& compare) const
{
	if (y<compare.y)
	{
		return true;
	}
	else if (y > compare.y)
	{
		return false;
	}
	else
		return ( x < compare.x);
}
#endif