//==========================================================
//Skeleton2DData.hpp
//==========================================================
#pragma once
#ifndef _SKELETON2DDATA_HPP_
#define _SKELETON2DDATA_HPP_

class Skeleton2DDataImplementation;

class Skeleton2DData
{
public:
	Skeleton2DData(void* copyData);
	Skeleton2DData();
	~Skeleton2DData();
	Skeleton2DDataImplementation* GetImplementation(){ return m_implementation; }
	void* GetSkeleton2DData();
protected:
	Skeleton2DDataImplementation* m_implementation;
};

#endif