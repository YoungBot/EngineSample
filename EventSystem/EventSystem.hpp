//==========================================================
//EventSystem.hpp
//==========================================================
#pragma once
#ifndef _EVENTSYSTEM_HPP_
#define _EVENTSYSTEM_HPP_
#include <string>
#include <vector>
#include <map>
#include "Engine/Utility/Utility.hpp"
#include "NamedProperties.hpp"
typedef void(EventCallback)(NamedProperties& args);
class NamedProperties;
class EventObjectSubscription
{
public:
	virtual void ExecuteCallback(NamedProperties& args) = 0;
};
class CallbackSubscription : public EventObjectSubscription
{
public:	
	CallbackSubscription(EventCallback* callback)
		:m_callback(callback){}
	EventCallback* m_callback;
	virtual void ExecuteCallback(NamedProperties& args) override;
};
inline void CallbackSubscription::ExecuteCallback(NamedProperties& args)
{
	m_callback(args);
}
//////////////////////////////////////////////////////////////////////////
class SubscriberList
{
public:
	std::vector<EventCallback*> m_callbacks;
};
//////////////////////////////////////////////////////////////////////////
template <typename T_ObjType>
class TypedObjSubscription : public EventObjectSubscription
{
public:
	typedef void(T_ObjType::*MethodPtr)(NamedProperties&);
	TypedObjSubscription(T_ObjType& obj, MethodPtr method)
		:m_object(obj)
		,m_method(method){}
	virtual void ExecuteCallback(NamedProperties& args) override;
private:
	MethodPtr m_method;
	T_ObjType& m_object;
};

template <typename T_ObjType>
inline void TypedObjSubscription<T_ObjType>::ExecuteCallback(NamedProperties& args)
{
	(m_object.*m_method)(args);
}
//////////////////////////////////////////////////////////////////////////
class EventSystem
{
public:
	EventSystem();
	static bool CreateInstance();
	static EventSystem& GetInstance();
	int FireEvent(const std::string& eventName, NamedProperties& args);
	bool RegisterEvent(const std::string& eventName, EventCallback* cb);
	bool UnRegisterEvent(const std::string& eventName, EventCallback* cb);
	template<typename T_ObjType, typename T_MethodPtrType>
	bool RegisterEventSubscribe(const std::string& eventName, T_ObjType& obj, T_MethodPtrType method);
private:
	static EventSystem* s_theEventSystem;
	//std::map<std::string,SubscriberList> m_eventSubscriptions;
	std::map<std::string, std::vector<EventObjectSubscription*>> m_subscribers;
};

template<typename T_ObjType, typename T_MethodPtrType>
inline bool EventSystem::RegisterEventSubscribe(const std::string& eventName, T_ObjType& obj, T_MethodPtrType method)
{
	std::vector<EventObjectSubscription*>& subscriptions = m_subscribers[eventName];
	EventObjectSubscription* subscriber = new TypedObjSubscription<T_ObjType>(obj, method);
	subscriptions.push_back(subscriber);
	return true;
}

#endif