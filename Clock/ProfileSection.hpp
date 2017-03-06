//==========================================================
//ProfileSection.hpp
//==========================================================

#pragma once
#ifndef _PROFILESECTION_HPP_
#define _PROFILESECTION_HPP_
#include <map>

struct ProfileSectionData
{
	double m_startTime;
	double m_endTime;
	std::string m_functionName;
	double m_totalTime;
	int m_numItRuns;
	ProfileSectionData(double startTime, double endTime, const std::string& functionName);
	void UpdateData(double startTime, double endTime);
	double GetCurrentElapsedTime(){ return m_endTime - m_startTime; }
	double GetAverageElapsedTime()
	{
		return (double)(m_totalTime / (double)m_numItRuns);
	}
	double GetTotalRunTime(){ return m_totalTime; }
};

class ProfileSection
{
public:
	ProfileSection(const char* functionName);
	~ProfileSection();
	void AddToMap();
	static double GetAverageElapsedTimeByName(const std::string& name);
	static double GetTotalElapsedTimeByName(const std::string& name);
private:
	double m_startTime;
	double m_endTime;
	std::string m_functionName;
};
extern std::map<std::string, ProfileSectionData*>* s_profileSectionMap;
#endif