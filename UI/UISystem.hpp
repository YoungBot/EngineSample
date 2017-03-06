//==========================================================
//UISystem.hpp
//==========================================================

#pragma once
#ifndef _UISYSTEM_HPP_
#define _UISYSTEM_HPP_

#include <string>
#include <vector>
#include <map>
#include "BaseWidget.hpp"
#include "BaseWidget2.hpp"
#include "Engine/Utility/xmlParser.h"

class UISystem
{
public:
	UISystem();
	int LoadAllBaseWidgetXMLs();
	int LoadAllBaseWidget2XMLs();
	int LoadAllSpecificWidgetXMLs();
	void Startup();
	BaseWidget* GetBaseWidgetByName(const std::string&);
	BaseWidget2* CreateWidgetByType(WidgetType2 type);
	BaseWidget2* CreateWidgetByTypeAndStyle(const XMLNode& node, const std::string& widgetName, const std::string& styleName);
	BaseWidget2* GetBaseWidget2ByName(const std::string& name);
	BaseWidget2* GetSpecificWidgetByName(const std::string& name);
	static void SetWidgetByStyle(const std::string& styleName, BaseWidget2* widget);
	static void RegistEvent();
	void AddNamedWidget(const std::string& name, BaseWidget2* widget);
	BaseWidget2* GetNamedWidgetByName(const std::string& name);
	void SetHiddenByName(const std::string& name, bool isHidden);
private:
	void CreateAndSaveBaseWidget(const std::string& name, const XMLNode& widgetNode, const XMLNode& stateNode);
	void CreateAndSaveBaseWidget2(const std::string& name, const XMLNode& stateNode);
	std::map<std::string,BaseWidget*> m_baseWidgets;
	std::map<std::string, BaseWidget2*> m_newBaseWidgets;
	std::map<std::string, BaseWidget2*> m_specificWidgets;
	std::map<std::string, BaseWidget2*> m_namedWidget;
	//BaseWidget m_registry[NUM_WIDGET_TYPE];
};
extern UISystem* s_theUISystem;
#endif