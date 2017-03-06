//==========================================================
//EventSystem.cpp
//==========================================================
#include "EventSystem.hpp"
#include <assert.h>
EventSystem* EventSystem::s_theEventSystem = nullptr;
EventSystem::EventSystem()
{
	//m_eventSubscriptions.clear();
}

bool EventSystem::CreateInstance()
{
	s_theEventSystem = new EventSystem();
	return true;
}

EventSystem& EventSystem::GetInstance()
{
	if (!s_theEventSystem)
	{
		assert(1);//Freak Out
	}
	return *s_theEventSystem;
}

int EventSystem::FireEvent(const std::string& eventName, NamedProperties& args)
{
	//std::map<std::string, SubscriberList>::iterator found = m_eventSubscriptions.find(eventName);
	//if (found == m_eventSubscriptions.end())
	//{
	//	return 0;
	//}
	//SubscriberList subscribers = found->second;
	//for (EventCallback* callback: subscribers.m_callbacks)
	//{
	//	callback(args);
	//}
	//return subscribers.m_callbacks.size();
	int count = 0;
	auto found = m_subscribers.find(eventName);
	if (found == m_subscribers.end())
		return 0;
	else
	{
		std::vector<EventObjectSubscription*>& thisSubscribers = found->second;
		for (EventObjectSubscription* subscriber : thisSubscribers)
		{
			if (subscriber!=nullptr)
			{
				subscriber->ExecuteCallback(args);
				count++;
			}			
		}
	}
	return count;
}
///----------------------------------------------------------
///
///----------------------------------------------------------

//int EventSystem::FireEvent(const std::string& eventName)
//{
//	auto found = m_subscribers.find(eventName);
//	if (found == m_subscribers.end())
//		return 0;
//	else
//	{
//		std::vector<EventObjectSubcription*>& thisSubscribers = found->second;
//		for (EventObjectSubcription* subscriber: thisSubscribers)
//		{
//			subscriber->ExecuteCallback(args);
//		}
//	}
//}

///----------------------------------------------------------
///
///----------------------------------------------------------

bool EventSystem::RegisterEvent(const std::string& eventName, EventCallback* cb)
{
	//std::map<std::string, SubscriberList>::iterator found = m_eventSubscriptions.find(eventName);
	//if (found == m_eventSubscriptions.end())
	//{
	//	SubscriberList list;
	//	list.m_callbacks.push_back(cb);
	//	m_eventSubscriptions.insert(std::pair<std::string, SubscriberList>(eventName, list));
	//	return true;
	//}k
	//else
	//{
	//	//SubscriberList subscribers = found->second;
	//	for (std::vector<EventCallback*>::iterator iter = found->second.m_callbacks.begin(); iter != found->second.m_callbacks.end();++iter)
	//	{
	//		if (*iter == cb)
	//		{
	//			return false;
	//		}
	//	}
	//	found->second.m_callbacks.push_back(cb);
	//	return true;
	//}
	std::vector<EventObjectSubscription*>& subscriptions = m_subscribers[eventName];
	EventObjectSubscription* subscriber = new CallbackSubscription(cb);
	subscriptions.push_back(subscriber);
	return true;
}
///----------------------------------------------------------
///
///----------------------------------------------------------

bool EventSystem::UnRegisterEvent(const std::string& eventName, EventCallback* cb)
{
	auto found = m_subscribers.find(eventName);
	if (found == m_subscribers.end())
	{
		return false;
	}
	else
	{
		std::vector<EventObjectSubscription*>& currentSubscriptions = found->second;
		for (std::vector<EventObjectSubscription*>::iterator iter = currentSubscriptions.begin(); iter != currentSubscriptions.end(); ++iter)
		{
			CallbackSubscription* p = dynamic_cast<CallbackSubscription*>(*iter);
			if (p != nullptr && p->m_callback == cb)
			{
				currentSubscriptions.erase(iter);
				return true;
			}
		}
		return false;
	}
}


