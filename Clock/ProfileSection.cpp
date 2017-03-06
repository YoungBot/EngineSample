//==========================================================
//ProfileSection.cpp
//==========================================================

#include "ProfileSection.hpp"
#include "Engine/Time/Time.hpp"
#include <string>
#include "Engine/Utility/Utility.hpp"
std::map<std::string, ProfileSectionData*>* s_profileSectionMap = NULL;


///----------------------------------------------------------
///
///----------------------------------------------------------

ProfileSectionData::ProfileSectionData(double startTime, double endTime, const std::string& functionName)
	:m_startTime(0.0f)
	, m_endTime(0.0f)
	, m_functionName("")
	, m_totalTime(0.0)
	, m_numItRuns(1)
{
	
	m_startTime = startTime;
	m_endTime = endTime;
	m_functionName = functionName;
	m_totalTime = m_endTime - m_startTime;
	
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void ProfileSectionData::UpdateData(double startTime, double endTime)
{
	m_startTime = startTime;
	m_endTime = endTime;
	m_totalTime += endTime - startTime;
	m_numItRuns++;
}

///----------------------------------------------------------
///
///----------------------------------------------------------

ProfileSection::ProfileSection(const char* functionName)
	:m_startTime(0.0f)
	, m_endTime(0.0f)
	, m_functionName("")
{
	if (s_profileSectionMap == nullptr)
	{
		s_profileSectionMap = new std::map < std::string, ProfileSectionData* > ;
	}
	m_startTime = GetCurrentSeconds();
	m_functionName = functionName;
}
///----------------------------------------------------------
///
///----------------------------------------------------------

ProfileSection::~ProfileSection()
{
	m_endTime = GetCurrentSeconds();
	//RECOVERABLE_ASSERTION(m_endTime != m_startTime, "error");
	AddToMap();
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void ProfileSection::AddToMap()
{
	
	std::map<std::string, ProfileSectionData*>::iterator profileSectionIter =  s_profileSectionMap->find(m_functionName);
	if (profileSectionIter == s_profileSectionMap->end())
	{
		ProfileSectionData* newData = new ProfileSectionData(m_startTime,m_endTime,m_functionName);
		newData->m_numItRuns = 1;
		s_profileSectionMap->insert(std::pair<std::string, ProfileSectionData*>(m_functionName, newData));
	}
	else
	{
		profileSectionIter->second->UpdateData(m_startTime, m_endTime);
	}
	
}

double ProfileSection::GetAverageElapsedTimeByName(const std::string& name)
{
	std::map<std::string, ProfileSectionData*>::iterator iter = s_profileSectionMap->find(name);
	if (iter != s_profileSectionMap->end())
	{
		return (*iter).second->GetAverageElapsedTime();		
	}
	return 0.0f;
}

double ProfileSection::GetTotalElapsedTimeByName(const std::string& name)
{
	std::map<std::string, ProfileSectionData*>::iterator iter = s_profileSectionMap->find(name);
	if (iter != s_profileSectionMap->end())
	{
		return (*iter).second->GetTotalRunTime();
	}
	return 0.0f;
}

///----------------------------------------------------------
///
///----------------------------------------------------------

