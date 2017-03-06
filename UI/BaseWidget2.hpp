//==========================================================
//BaseWidget2.hpp
//==========================================================
#pragma once
#ifndef _BASEWIDGET2_HPP_
#define _BASEWIDGET2_HPP_

#include <vector>
#include <string>
#include "Engine/Renderer/RGBA.hpp"
#include "Engine/Math/Vector2.hpp"
#include "Engine/EventSystem/NamedProperties.hpp"
#include "Engine/Utility/xmlParser.h"


struct WidgetPropertiesForState
{
	NamedProperties fromWidget;
	NamedProperties fromStyle;
	NamedProperties fromCode;
};
enum PropertiesFrom
{
	PROPERTIES_FROM_BASE,
	PROPERTIES_FROM_STYLE,
	PROPERTIES_FROM_CODE
};
enum WidgetState2
{
	WIDGET_STATE_DEFAULT_,
	WIDGET_STATE_ENABLE_,//NORMAL/ACTIVE
	WIDGET_STATE_SELECTING_,
	WIDGET_STATE_SELECT_,//HIGHLIGHT
	WIDGET_STATE_DISABLING_,
	WIDGET_STATE_DISABLE_,//GREY-OUT
	WIDGET_STATE_PRESSED,//PRESSED
	WIDGET_STATE_HIDDEN,
	NUM_WIDGET_STATE_
};
enum StateTransition2
{
	ENABLE_TO_SELECT_,
	NUM_STATE_TRANSITION_
};
enum WidgetType2
{
	WIDGET_TYPE_DEFAULT_,
	WIDGET_TYPE_RECTBUTTON_,
	WIDGET_TYPE_SLIDER,
	WIDGET_TYPE_LABEL,
	WIDGET_TYPE_EDITABLELABEL,
	WIDGET_TYPE_PROGRESSBAR,
	WIDGET_TYPE_CHECKBOX,
	WIDGET_TYPE_RADIOWIDGET,
	WIDGET_TYPE_DROPDOWNWIDGET,
	NUM_WIDGET_TYPE_
};
class Matrix4x4;
struct Vertex3D_PCT;
struct XMLNode;
class BaseWidget2
{
public:
	BaseWidget2();
	BaseWidget2(BaseWidget2& copy);
	BaseWidget2(const XMLNode& node);
	virtual void Draw(const Matrix4x4& Ortho, const Matrix4x4& I) { I; Ortho; };
	virtual void Update(float deltaSecond, Vector2& mousePosition);
	void SetColorFromXMLByNameInState(const std::string& name,const XMLNode& node,PropertiesFrom from);
	template<typename T>
	PropertyGetResult GetValueInCurrentState(const std::string& propertyName, T& out_propertyValue) const;
	template<typename T>
	void SetValue(const std::string& propertyName, T& in_propertyValue);
	void SetHidden(bool isHidden);
	virtual Vector2 GetOffSet();
	Vector2 GetWorldMins();
	Vector2 GetWorldMaxs();
	void CopyWidgetPropertiesForState(WidgetPropertiesForState* copy);
	virtual void SetDragable(bool enable);
	virtual void Drag(Vector2& mousePosition);
	virtual void SetWidgetByStyle(const std::string styleName);
	void Init();
	//void SetName(const std::string& name);

	WidgetPropertiesForState m_forStates[NUM_WIDGET_STATE_];
	WidgetPropertiesForState m_currentStateProperty;
	WidgetState2 m_currentState;
	WidgetType2 m_widgetType;
	Vector2 m_mouseStartPosition;
	float m_timeCheck;
	bool m_isHidden;
	bool m_enableDrag;
	std::string m_name;
	BaseWidget2* m_parent;
};

template<typename T>
inline PropertyGetResult BaseWidget2::GetValueInCurrentState(const std::string& propertyName, T& out_propertyValue) const
{
	if (m_currentStateProperty.fromWidget.Get(propertyName, out_propertyValue) == RESULT_SUCCESS)
		return RESULT_SUCCESS;
	if (m_currentStateProperty.fromStyle.Get(propertyName, out_propertyValue) == RESULT_SUCCESS)
		return RESULT_SUCCESS;
	return m_currentStateProperty.fromCode.Get(propertyName, out_propertyValue);
}


template<typename T>
void BaseWidget2::SetValue(const std::string& propertyName, T& in_propertyValue)
{
	for (int i = 0; i < NUM_WIDGET_STATE_; i++)
	{
		m_forStates[i].fromWidget.Set(propertyName, in_propertyValue);
	}
}

#endif