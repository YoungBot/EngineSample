//==========================================================
//IntVector3.hpp
//==========================================================

#pragma once

#ifndef _INTVECTOR3_HPP_
#define _INTVECTOR3_HPP_

class IntVector3
{
public:
	IntVector3();
	~IntVector3();
	IntVector3(int x,int y,int z);
	int m_x;
	int m_y;
	int m_z;

	const IntVector3 operator + (const IntVector3& vectorToAdd) const;
	const IntVector3 operator - (const IntVector3& vectorToAdd) const;

};

inline IntVector3::IntVector3()
{

}

inline IntVector3::IntVector3(int x,int y,int z)
{
	m_x = x;
	m_y = y;
	m_z = z;
}

inline IntVector3::~IntVector3()
{

}

inline const IntVector3 IntVector3::operator + ( const IntVector3& vectorToAdd ) const
{
	IntVector3 outputVec;
	outputVec.m_x += vectorToAdd.m_x ;
	outputVec.m_y += vectorToAdd.m_y ; 
	outputVec.m_z += vectorToAdd.m_z ;

	return outputVec;
}

inline const IntVector3 IntVector3::operator - ( const IntVector3& vectorToAdd ) const
{
	IntVector3 outputVec;
	outputVec.m_x -= vectorToAdd.m_x ;
	outputVec.m_y -= vectorToAdd.m_y ; 
	outputVec.m_z -= vectorToAdd.m_z ;

	return outputVec;
}

#endif