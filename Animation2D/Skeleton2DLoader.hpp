//==========================================================
//Skeleton2DLoader.hpp
//==========================================================

#pragma once
#ifndef _SKELETON2DLOADER_HPP_
#define _SKELETON2DLOADER_HPP_


#include <string>
#include <map>
#include "Attachment2DLoader.hpp"
#include "Skeleton2DData.hpp"
class Skeleton2DLoaderImplementation;
class Skeleton2DLoader 
{
public:
	//Skeleton2DLoader (const Attachment2DLoader& attachment);
	Skeleton2DLoader(const char* jsonFileName, const char* atlasFileName);
	~Skeleton2DLoader ();
	static bool LoadAllSkeletonsFromFile();
	static Skeleton2DData* GetSkeletonDataByName(const std::string& name);
	Skeleton2DData* ReadSkeletonData();

protected:
	static std::map<std::string,Skeleton2DData*>* s_skeletonDatas;
	Skeleton2DLoaderImplementation* m_implementation;
	std::string m_jsonFilePath;
	std::string m_atlasFilePath;
};


#endif
