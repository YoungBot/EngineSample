//==========================================================
//BaseWidget.hpp
//==========================================================

#pragma once
#ifndef _BASEWIDGET_HPP_
#define _BASEWIDGET_HPP_

#include <vector>
#include <string>
#include "Engine/Renderer/RGBA.hpp"
#include "Engine/Math/Vector2.hpp"
#include "Engine/EventSystem/NamedProperties.hpp"


enum WidgetState
{
	WIDGET_CURRENT_STATE,
	WIDGET_STATE_ENABLE,
	WIDGET_STATE_SELECTING,
	WIDGET_STATE_SELECT,
	WIDGET_STATE_DISABLING,
	WIDGET_STATE_DISABLE,
	NUM_WIDGET_STATE
};
enum StateTransition
{
	ENABLE_TO_SELECT,
	NUM_STATE_TRANSITION
};
enum WidgetType
{
	WIDGET_TYPE_DEFAULT,
	WIDGET_TYPE_BUTTON,
	NUM_WIDGET_TYPE
};

struct Vertex3D_PCT;
class Matrix4x4;
class GLMeshRenderer;
class NamedProperties;
struct XMLNode;
class BaseWidget
{
public: 
	BaseWidget();
	BaseWidget(const Vector2& mins, const Vector2& maxs, const RGBA& BGcolor, const RGBA& edgeColor = RGBA(1.0F,0.0F,1.0F,1.0F), const float edgeThickness=5.0f);
	
	void Draw(const Matrix4x4& Ortho, const Matrix4x4& I);
	void SetText(const std::string& text, RGBA color, float scale,WidgetState state = WIDGET_STATE_ENABLE);
	virtual void Update(float deltaSecond, Vector2& mousePosition);
	void SetRenderer();
	void SetAnimatedProperty();
	void CopyData();
	void SetDefaultByXML(const XMLNode& node);
	void SetStateByXML(WidgetState state, const XMLNode& node);
//private:
	Vertex3D_PCT* CreateVerts(int& size);	
	void GetEdgeVerts(Vertex3D_PCT* edgeVerts);
	Vertex3D_PCT* GetTextVerts(int& size);
	Vector2 m_mins[NUM_WIDGET_STATE];
	Vector2 m_maxs[NUM_WIDGET_STATE];
	RGBA m_BGColor[NUM_WIDGET_STATE];
	RGBA m_edgeColor[NUM_WIDGET_STATE];
	std::string m_text[NUM_WIDGET_STATE];
	std::string m_fontFileName[NUM_WIDGET_STATE];
	RGBA m_textColor[NUM_WIDGET_STATE];
	float m_textScale[NUM_WIDGET_STATE];
	float m_edgeThickness[NUM_WIDGET_STATE];
	WidgetState m_currentState;
	GLMeshRenderer* m_renderer;
	GLMeshRenderer* m_textRenderer;
	float m_timeCheck;
	NamedProperties m_properties[NUM_WIDGET_STATE];
	WidgetType m_type;
};

#endif