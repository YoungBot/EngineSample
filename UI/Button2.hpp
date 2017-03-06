//==========================================================
//Button2.hpp
//==========================================================
#pragma once
#ifndef _BUTTON2_HPP_
#define _BUTTON2_HPP_
#include "BaseWidget2.hpp"

class GLMeshRenderer;
struct XMLNode;
class Button2 : public BaseWidget2
{
public:
	Button2();
	Button2(BaseWidget2 copy);
	Button2(const XMLNode& node);
	virtual void Draw(const Matrix4x4& Ortho, const Matrix4x4& I);
	void SetText(const std::string& text, RGBA color, float scale, WidgetState2 state = WIDGET_STATE_ENABLE_);
	void SetRenderer();
	virtual void Update(float deltaSecond, Vector2& mousePosition);// { deltaSecond; mousePosition; };
	void SetEvent(const std::string& eventName);
	virtual void CallEvent(NamedProperties* properties = nullptr);
	GLMeshRenderer* m_renderer;
	GLMeshRenderer* m_textRenderer;
	std::string m_eventName;
};

#endif