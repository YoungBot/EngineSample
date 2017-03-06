//==========================================================
//Skeleton2DLoader.cpp
//==========================================================
#include "Skeleton2DLoader.hpp"
#include "Skeleton2DData.hpp"
#include <spine/SkeletonJson.h>
#include <spine/Atlas.h>
#include <vector>
#include "Engine/Renderer/Texture.hpp"
#include "Engine/Utility/Utility.hpp"
#include "Engine/Utility/xmlParser.h"

std::map<std::string, Skeleton2DData*>* Skeleton2DLoader::s_skeletonDatas = nullptr;
class Skeleton2DLoaderImplementation
{
public:
	//Skeleton2DLoaderImplementation(spAttachmentLoader* attachmentLoader);
	Skeleton2DLoaderImplementation(const char* jsonFileName, const char* atlasFileName);
	spSkeletonJson* GetSkeletonJson(){ return m_json; }
	Skeleton2DData* GetSkeletonData(const char* fileName);
protected:
	spSkeletonJson* m_json;
};
///----------------------------------------------------------
///
///----------------------------------------------------------

Skeleton2DData* Skeleton2DLoaderImplementation::GetSkeletonData(const char* fileName)
{ 
	Skeleton2DData* data = new Skeleton2DData(spSkeletonJson_readSkeletonDataFile(m_json, fileName));
	return data;
}
///----------------------------------------------------------
///
///----------------------------------------------------------


Skeleton2DLoaderImplementation::Skeleton2DLoaderImplementation(const char* jsonFileName, const char* atlasFileName)
{
	//create atlas
	jsonFileName;
	atlasFileName;
	spAtlas* newAtlas = spAtlas_createFromFile(atlasFileName, nullptr);
	Texture* texture = (Texture*)newAtlas->rendererObject;
	m_json = spSkeletonJson_create(newAtlas);////////////////////////
}
///----------------------------------------------------------
///
///----------------------------------------------------------

Skeleton2DLoader::Skeleton2DLoader(const char* jsonFileName, const char* atlasFileName)
	: m_implementation(nullptr)
	, m_jsonFilePath(jsonFileName)
	, m_atlasFilePath(atlasFileName)
{
	m_implementation = new Skeleton2DLoaderImplementation(jsonFileName, atlasFileName);//CONSTRUCTER OF IMPLE
	
}
///----------------------------------------------------------
///
///----------------------------------------------------------

Skeleton2DData* Skeleton2DLoader::ReadSkeletonData()
{
	//m_implementation = new Skeleton2DLoaderImplementation((spAttachmentLoader*)attachment.GetImplementationSpecificAttachementLoader());
	return m_implementation->GetSkeletonData(m_jsonFilePath.c_str());
}
///----------------------------------------------------------
///
///----------------------------------------------------------

Skeleton2DLoader::~Skeleton2DLoader()
{

}
///----------------------------------------------------------
///
///----------------------------------------------------------

bool Skeleton2DLoader::LoadAllSkeletonsFromFile()
{
	//s_skeletonDatas->clear();
	s_skeletonDatas = new std::map < std::string, Skeleton2DData* > ;
	std::vector<std::string> allSkeletonFiles;
	Utility::FindAllFilesOfType("Data/Spine2D/", "*.xml", allSkeletonFiles);
	for (unsigned int i = 0; i < allSkeletonFiles.size(); i++)
	{
		std::string dir = "Data/Spine2D/";
		dir += allSkeletonFiles[i];
		XMLNode SkeletonParser = XMLNode::parseFile(dir.c_str(), "Skeletons");
		int j = 1;
		XMLNode currentSkeletonData = SkeletonParser.getChildNode();
		while (!currentSkeletonData.isEmpty())
		{
			std::string json = currentSkeletonData.getAttribute("Json");
			std::string atlas = currentSkeletonData.getAttribute("Atlas");
			std::string name = currentSkeletonData.getAttribute("Name");
			Skeleton2DLoader currentLoader = Skeleton2DLoader(json.c_str(), atlas.c_str());
			Skeleton2DData* currentData = currentLoader.ReadSkeletonData();
			s_skeletonDatas->insert(std::pair<std::string, Skeleton2DData*>(name,currentData));
			currentSkeletonData = SkeletonParser.getChildNode(j);
			++j;
		}
	}
	return true;
}
///----------------------------------------------------------
///
///----------------------------------------------------------

Skeleton2DData* Skeleton2DLoader::GetSkeletonDataByName(const std::string& name)
{
	std::map<std::string, Skeleton2DData*>::iterator dataIter = s_skeletonDatas->begin();
	while (dataIter!=s_skeletonDatas->end())
	{
		if (dataIter->first == name)
			return dataIter->second;
		++dataIter;
	}
	return nullptr;
}

