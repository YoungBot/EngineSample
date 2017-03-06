//==========================================================
//WidgetStyle.hpp
//==========================================================
#pragma once
#ifndef _WIDGETSTYLE_HPP_
#define _WIDGETSTYLE_HPP_
#include <string>
#include <map>
#include "BaseWidget2.hpp"
class NameProperties;

class WidgetStyle
{
public:
	WidgetStyle();
	static int LoadAllStyleFromXML();
	static WidgetStyle* GetStyleByName(const std::string& name);
	static void CreateAndSaveStyles(const std::string name, const XMLNode& node);
	static RGBA GetRGBAFromXMLbyName(const std::string& name, const XMLNode& node);

	NamedProperties m_nameProperties[NUM_WIDGET_STATE_];
	static std::map<std::string, WidgetStyle*> s_styles;
};
#endif