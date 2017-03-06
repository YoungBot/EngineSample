//==========================================================
//Clock.cpp
//==========================================================

#include "Clock.hpp"
Clock* g_masterClock = Clock::CreateMasterClock();
struct Alarm
{
	std::string m_eventName;
	float m_timeInSeconds;
	float m_remainingTime;
	bool m_isDie;
	void* m_data;
	callback_t m_cb;
	float GetSecondsElapsed(){ return m_timeInSeconds - m_remainingTime; }
	float GetPercentElapsed(){ return (m_timeInSeconds-m_remainingTime)/m_timeInSeconds; }
	float GetPercentRemaining(){ return m_remainingTime / m_timeInSeconds; }
	float GetSecondRemaining(){ return m_remainingTime; }
	void AlarmUpdate(float deltaSecond);
	bool GetIsDead(){ return m_isDie; }
	Alarm(const std::string& event_name, float time_in_seconds, void *data, callback_t cb);
};
Alarm::Alarm(const std::string&event_name, float time_in_seconds, void *data, callback_t cb)
	: m_eventName(event_name)
	, m_timeInSeconds(time_in_seconds)
	, m_remainingTime(time_in_seconds)
	, m_data(data)
	, m_cb(cb)
	, m_isDie(false)
{
	
}
///----------------------------------------------------------
///
///----------------------------------------------------------
void Alarm::AlarmUpdate(float deltaSecond)
{
	m_remainingTime -= deltaSecond;
	if (m_remainingTime<=0.0f)
	{
		m_cb(m_eventName.c_str(), m_data);
		m_isDie = true;
	}
}
///----------------------------------------------------------
///
///----------------------------------------------------------

Clock::Clock()
	 : m_deltaSecond(0.0f)
	 , m_current(0.0)
	 , m_isPaused(false)
	 , m_timeScale(1.0f)
	 , m_parent(nullptr)
	 , m_maxDeltaSecond(0.5f)
{
	m_children.clear();
	m_alarms.clear();
}

Clock::Clock(Clock* parent)
	: m_deltaSecond(0.0f)
	, m_current(0.0)
	, m_isPaused(false)
	, m_timeScale(1.0f)
	, m_parent(parent)
	, m_maxDeltaSecond(0.5f)
{
	m_children.clear();
	m_alarms.clear();
	parent->AddChild(this);
}

///----------------------------------------------------------
///
///----------------------------------------------------------

Clock::~Clock()
{

}
///----------------------------------------------------------
///
///----------------------------------------------------------

void Clock::AdvanceTime(double deltaSeconds)
{
	if (deltaSeconds>m_maxDeltaSecond)
		deltaSeconds = m_maxDeltaSecond;

	deltaSeconds *= m_timeScale;
	if (m_isPaused)
		deltaSeconds = 0.0f;
	m_current += deltaSeconds;
	m_deltaSecond = deltaSeconds;
	ClockUpdate(deltaSeconds);
	for (std::vector<Clock*>::iterator childClockItor = m_children.begin(); childClockItor != m_children.end(); childClockItor++)
	{
		(*childClockItor)->AdvanceTime(deltaSeconds);
	}

}
///----------------------------------------------------------
///
///----------------------------------------------------------

void Clock::SetParent(Clock* parent)
{
	if (parent != nullptr)
		m_parent = parent;
	else
		m_parent = nullptr;
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void Clock::AddChild(Clock* newClock)
{
	if (newClock != nullptr)
	{
		m_children.push_back(newClock);
	}
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void Clock::ClockUpdate(double deltaSecond)
{
	deltaSecond;
	std::vector<std::string> deadAlarmNames;
	for (std::map < std::string, Alarm* >::iterator alarmIter = m_alarms.begin(); alarmIter != m_alarms.end(); ++alarmIter)
	{
		alarmIter->second->AlarmUpdate((float)m_deltaSecond);
		if (alarmIter->second->GetIsDead())
		{
			deadAlarmNames.push_back(alarmIter->second->m_eventName);
		}		
	}
	for (unsigned int i = 0; i < deadAlarmNames.size(); i++)
	{
		std::map < std::string, Alarm* >::iterator alarmIter = m_alarms.find(deadAlarmNames[i]);
		if (alarmIter != m_alarms.end())
		{
			m_alarms.erase(alarmIter);
		}
	}
	
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void Clock::SetAlarm(const std::string& event_name, float time_in_seconds, void *data, callback_t cb)
{
	Alarm* alarm = new Alarm(event_name, time_in_seconds, data, cb);
	m_alarms.insert(std::pair<std::string, Alarm*>(event_name, alarm));
}
///----------------------------------------------------------
///
///----------------------------------------------------------

Alarm* Clock::GetAlarmByName(const std::string& name)
{
	std::map < std::string, Alarm* >::iterator alarmIter = m_alarms.find(name);
	if (alarmIter != m_alarms.end())
		return alarmIter->second;
	else
		return nullptr;
}
///----------------------------------------------------------
///
///----------------------------------------------------------

Clock* Clock::CreateMasterClock()
{
	Clock* masterClock = new Clock();
	return masterClock;
}

///----------------------------------------------------------
///
///----------------------------------------------------------



