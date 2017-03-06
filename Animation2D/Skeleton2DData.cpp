//==========================================================
//Skeleton2DData.cpp
//==========================================================

#include "Skeleton2DData.hpp"
#include <spine/SkeletonData.h>
#include <string>
#include <vector>


class Skeleton2DDataImplementation
{
public:
	Skeleton2DDataImplementation(spSkeletonData* copyData);
	std::string GetVersion(){ std::string version(m_data->version); return version; };
	std::string GetHash(){ std::string hash(m_data->hash); return hash; };
	float GetWidth(){ return m_data->width; }
	float GetHeight(){ return m_data->height; }
	spSkeletonData* GetSkeletonData(){ return m_data; };
	
protected:
	spSkeletonData* m_data;
};
///----------------------------------------------------------
///
///----------------------------------------------------------

Skeleton2DDataImplementation::Skeleton2DDataImplementation(spSkeletonData* copyData)
{
	if (copyData==nullptr)
		m_data = nullptr;
	else
		m_data = new spSkeletonData(*copyData);
}
///----------------------------------------------------------
///
///----------------------------------------------------------

Skeleton2DData::Skeleton2DData()
	:m_implementation(nullptr)
{
	
}
///----------------------------------------------------------
///
///----------------------------------------------------------

Skeleton2DData::Skeleton2DData(void* copyData)
	: m_implementation(nullptr)
{
	m_implementation = new Skeleton2DDataImplementation((spSkeletonData*)copyData);
}
///----------------------------------------------------------
///
///----------------------------------------------------------

Skeleton2DData::~Skeleton2DData()
{

}
///----------------------------------------------------------
///
///----------------------------------------------------------

void* Skeleton2DData::GetSkeleton2DData()
{
	return m_implementation->GetSkeletonData();
}

