//==========================================================
//BaseWidget2.cpp
//==========================================================
#include "BaseWidget2.hpp"
#include "Engine/Utility/Utility.hpp"
#include "Engine/Utility/xmlParser.h"
#include "UISystem.hpp"
BaseWidget2::BaseWidget2()
	:m_widgetType(WIDGET_TYPE_DEFAULT_)
	,m_currentState(WIDGET_STATE_ENABLE_)
	,m_isHidden(false)
	,m_timeCheck(0.0f)
	,m_parent(nullptr)
	,m_enableDrag(false)
	,m_mouseStartPosition(Vector2(0.0f,0.0f))
	,m_name("")
{
	for (int i = 0; i < NUM_WIDGET_STATE_; i++)
	{
		m_forStates[i].fromCode.Set("BGColor",RGBA(1.0F,0.0F,0.0F,1.0F));
		m_forStates[i].fromCode.Set("edgeColor", RGBA(0.0F, 0.0F, 1.0F, 1.0F));
		m_forStates[i].fromCode.Set("edgeThickness", 5.0f);
		m_forStates[i].fromCode.Set("offset", Vector2(0.0f, 0.0f));
		//m_forStates[i].fromCode.Set("backgroundTextureName","Data/Images/brickTexture.png");
	}
	m_currentStateProperty = m_forStates[0];
}

BaseWidget2::BaseWidget2(const XMLNode& node)
	:m_widgetType(WIDGET_TYPE_DEFAULT_)
	, m_currentState(WIDGET_STATE_ENABLE_)
	, m_isHidden(false)
	, m_timeCheck(0.0f)
	, m_parent(nullptr)
	, m_enableDrag(false)
	, m_mouseStartPosition(Vector2(0.0f, 0.0f))
	, m_name("")
{
	for (int i = 0; i < NUM_WIDGET_STATE_; i++)
	{
		m_forStates[i].fromCode.Set("BGColor", RGBA(1.0F, 0.0F, 0.0F, 1.0F));
		m_forStates[i].fromCode.Set("edgeColor", RGBA(0.0F, 0.0F, 1.0F, 1.0F));
		m_forStates[i].fromCode.Set("edgeThickness", 5.0f);
		//m_forStates[i].fromCode.Set("backgroundTextureName", "Data/Images/brickTexture.png");
	}
	m_currentStateProperty = m_forStates[0];
	//////////////////////////////////////////////////////////////////////////
	int j = 0;
	XMLNode stateNode = node.getChildNode(j);
	while (!stateNode.isEmpty())
	{
		SetColorFromXMLByNameInState("BGColor", stateNode, PROPERTIES_FROM_BASE);
		SetColorFromXMLByNameInState("edgeColor", stateNode, PROPERTIES_FROM_BASE);
		//////////////////////////////////////////////////////////////////////////
		const char* stateNum = stateNode.getAttribute("state");
		int currentState;
		if (stateNum != NULL)
			currentState = atoi(stateNum);
		const char* edgeThickness = stateNode.getAttribute("edgeThickness");
		if (edgeThickness != NULL)
		{
			float thickness = (float)atof(edgeThickness);
			m_forStates[currentState].fromWidget.Set("edgeThickness", thickness);
		}
		const char* bgt = stateNode.getAttribute("backgroundTextureName");
		if (bgt != NULL)
		{
			std::string direction(bgt);
			m_forStates[currentState].fromWidget.Set("backgroundTextureName", direction);
		}
		j++;
		stateNode = node.getChildNode(j);
	}
}
///----------------------------------------------------------
///
///----------------------------------------------------------

BaseWidget2::BaseWidget2(BaseWidget2& copy)
	:m_widgetType(copy.m_widgetType)
	, m_currentState(copy.m_currentState)
	, m_isHidden(copy.m_isHidden)
	, m_timeCheck(copy.m_timeCheck)
	, m_parent(nullptr)
	, m_enableDrag(copy.m_enableDrag)
	, m_mouseStartPosition(Vector2(0.0f, 0.0f))
	, m_name(copy.m_name)
{
	CopyWidgetPropertiesForState(copy.m_forStates);
	m_currentStateProperty = m_forStates[0];
}

///----------------------------------------------------------
///
///----------------------------------------------------------

void BaseWidget2::Update(float deltaSecond, Vector2& mousePosition)
{
	deltaSecond;
	mousePosition;
	m_currentStateProperty = m_forStates[m_currentState];
}

///----------------------------------------------------------
///
///----------------------------------------------------------

void BaseWidget2::SetColorFromXMLByNameInState(const std::string& name, const XMLNode& node, PropertiesFrom from)
{
	const char* colorStr = node.getAttribute(name.c_str());
	const char* stateNum = node.getAttribute("state");
	int currentState;
	if (stateNum != NULL)
		currentState = atoi(stateNum);
		
	//////////////////////////////////////////////////////////////////////////
	if (colorStr != NULL)
	{
		std::string color = colorStr;
		std::vector<std::string> colorRgbaStr;
		unsigned char colorChar[4];
		colorRgbaStr.push_back(Utility::CutString(color, ',').c_str());
		colorRgbaStr.push_back(Utility::CutString(color, ',').c_str());
		colorRgbaStr.push_back(Utility::CutString(color, ',').c_str());
		colorRgbaStr.push_back(Utility::CutString(color, ',').c_str());
		for (unsigned int i = 0; i < colorRgbaStr.size(); i++)
		{
			if (colorRgbaStr[i] == "")
				colorChar[i] = 0;
			else
				colorChar[i] = (unsigned char)atoi(colorRgbaStr[i].c_str());
			if (i == 3 && colorRgbaStr[3] == "")
			{
				colorChar[i] = 255;
			}
		}
		RGBA currentColor = RGBA(colorChar[0], colorChar[1], colorChar[2], colorChar[3]);
		if (from == PROPERTIES_FROM_BASE)
			m_forStates[currentState].fromWidget.Set(name, currentColor);
		else
			m_forStates[currentState].fromStyle.Set(name, currentColor);


	}
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void BaseWidget2::SetHidden(bool isHidden)
{
	m_isHidden = isHidden;
	m_currentState = WIDGET_STATE_HIDDEN;
}
///----------------------------------------------------------
///
///----------------------------------------------------------

Vector2 BaseWidget2::GetOffSet()
{
	Vector2 offset(0.0f, 0.0f);
	Vector2 currentOffset(0.0f, 0.0f);
	if (m_parent!=nullptr)
	{
		//fromCode		
		PropertyGetResult result = m_parent->m_forStates[m_currentState].fromCode.Get("parentsOffset",offset);
		PropertyGetResult result2 = m_forStates[m_currentState].fromCode.Get("offset", currentOffset);
		//PropertyGetResult result = m_parent->m_currentStateProperty.fromCode.Get("parentsOffset", offset);
		if (result == RESULT_SUCCESS || result2 == RESULT_SUCCESS)
		{
			//Vector2 currentOffset(0.0f, 0.0f);
			//m_currentStateProperty.fromCode.Get("offset", currentOffset);
			m_currentStateProperty.fromCode.Set("parentsOffset", currentOffset+offset);
		}
		//fromStyle
		offset = Vector2(0.0f, 0.0f);
		currentOffset = Vector2(0.0f, 0.0f);
		result = m_parent->m_forStates[m_currentState].fromStyle.Get("parentsOffset", offset);
		result2 = m_forStates[m_currentState].fromStyle.Get("offset", currentOffset);
		//result = m_parent->m_currentStateProperty.fromStyle.Get("parentsOffset", offset);
		if (result == RESULT_SUCCESS || result2 == RESULT_SUCCESS)
		{
			//Vector2 currentOffset(0.0f, 0.0f);
			//m_currentStateProperty.fromStyle.Get("offset", currentOffset);
			m_currentStateProperty.fromStyle.Set("parentsOffset", currentOffset + offset);
		}
		//fromWidget
		offset = Vector2(0.0f, 0.0f);
		currentOffset = Vector2(0.0f, 0.0f);
		result = m_parent->m_forStates[m_currentState].fromWidget.Get("parentsOffset", offset);
		result2 = m_forStates[m_currentState].fromWidget.Get("offset", currentOffset);
		//result = m_parent->m_currentStateProperty.fromWidget.Get("parentsOffset", offset);
		if (result == RESULT_SUCCESS || result2 == RESULT_SUCCESS)
		{
			//Vector2 currentOffset(0.0f, 0.0f);
			//m_currentStateProperty.fromWidget.Get("offset", currentOffset);
			m_currentStateProperty.fromWidget.Set("parentsOffset", currentOffset + offset);
		}
		GetValueInCurrentState("parentsOffset", offset);
		return offset;
	}
	else
	{
		PropertyGetResult result = m_forStates[m_currentState].fromCode.Get("offset", offset);
		if (result == RESULT_SUCCESS)
		{
			m_forStates[m_currentState].fromCode.Set("parentsOffset", offset);
		}		
		result = m_forStates[m_currentState].fromStyle.Get("offset", offset);
		if (result == RESULT_SUCCESS)
		{
			m_forStates[m_currentState].fromStyle.Set("parentsOffset", offset);
		}			
		result = m_forStates[m_currentState].fromWidget.Get("offset", offset);
		if (result == RESULT_SUCCESS)
		{
			m_forStates[m_currentState].fromWidget.Set("parentsOffset", offset);
		}		
		return Vector2(0.0f, 0.0f);
	}
}
///----------------------------------------------------------
///
///----------------------------------------------------------
Vector2 BaseWidget2::GetWorldMins()
{
	Vector2 mins;
	Vector2 offset = GetOffSet();
	PropertyGetResult result = GetValueInCurrentState("mins", mins);
	if (result != RESULT_SUCCESS)
	{
		return Vector2(10000.0f,10000.0f);
	}
	return mins + offset;
}
///----------------------------------------------------------
///
///----------------------------------------------------------

Vector2 BaseWidget2::GetWorldMaxs()
{
	Vector2 maxs;
	Vector2 offset = GetOffSet();
	PropertyGetResult result = GetValueInCurrentState("maxs", maxs);
	if (result != RESULT_SUCCESS)
	{
		return Vector2(-10000.0f, -10000.0f);
	}
	
	return maxs + offset;
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void BaseWidget2::CopyWidgetPropertiesForState(WidgetPropertiesForState* copy)
{
	for (int i = 0; i < 8; i++)
	{
		m_forStates[i].fromCode = NamedProperties(copy[i].fromCode);
		m_forStates[i].fromWidget = NamedProperties(copy[i].fromWidget);
		m_forStates[i].fromStyle = NamedProperties(copy[i].fromStyle);
		//m_forStates[i].fromCode = (copy[i].fromCode);
		//m_forStates[i].fromWidget = (copy[i].fromWidget);
		//m_forStates[i].fromStyle = (copy[i].fromStyle);
	}
}

///----------------------------------------------------------
///
///----------------------------------------------------------

void BaseWidget2::SetDragable(bool enable)
{
	m_enableDrag = enable;
	if (enable == false)
	{
		m_mouseStartPosition = Vector2(0.0f, 0.0f);
	}
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void BaseWidget2::Drag(Vector2& mousePosition)
{
	if (m_mouseStartPosition == Vector2(0.0f, 0.0f))
	{
		m_mouseStartPosition = mousePosition;
	}
	Vector2 newoffset = mousePosition - m_mouseStartPosition;
	Vector2 offset(0.0f,0.0f);
	GetValueInCurrentState("offset", offset);
	for (unsigned int i = 0; i < NUM_WIDGET_STATE_; i++)
	{
		m_forStates[i].fromWidget.Set("offset", offset + newoffset);
		m_forStates[i].fromWidget.Set("parentsOffset", offset + newoffset);
	}
	m_mouseStartPosition = mousePosition;
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void BaseWidget2::SetWidgetByStyle(const std::string styleName)
{
	UISystem::SetWidgetByStyle(styleName, this);
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void BaseWidget2::Init()
{
	m_currentStateProperty = m_forStates[m_currentState];
}


