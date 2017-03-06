//==========================================================
//Clock.hpp
//==========================================================

#pragma once
#ifndef _CLOCK_HPP_
#define _CLOCK_HPP_
typedef void(*callback_t)(char const *event_name,void *arg);

struct Alarm;
#include <vector>
#include <map>
class Clock
{
public:
	Clock();
	Clock(Clock* parent);
	~Clock();
	double GetDelta(){ return m_deltaSecond; }
	double GetCurrent(){ return m_current; }
	bool GetIsPaused(){ return m_isPaused; }
	void SetIsPaused(const bool isPaused){ m_isPaused = isPaused; }
	float GetTimeScale(){ return m_timeScale; }
	void SetTimeScale(const float timeScale){ m_timeScale = timeScale; }
	void AdvanceTime(double deltaSeconds);
	Clock* GetParent(){ return m_parent; }
	void SetParent(Clock* parent);
	void SetMaxDeltaSecond(float maxDelta){ m_maxDeltaSecond = maxDelta;}
	std::vector<Clock*>& GetChildren(){ return m_children; }
	void AddChild(Clock* newClock);
	void ClockUpdate(double deltaSecond);
	void SetAlarm(const std::string& event_name, float time_in_seconds, void *data, callback_t cb);
	Alarm* GetAlarmByName(const std::string& name);
	static Clock* CreateMasterClock();
private:
	double m_deltaSecond;
	double m_maxDeltaSecond;
	double m_current;
	bool m_isPaused;
	float m_timeScale;	
	Clock* m_parent;
	std::vector<Clock*> m_children;
	std::map < std::string, Alarm* > m_alarms;

};
extern Clock* g_masterClock;

#endif