//==========================================================
//GroupWidget.hpp
//==========================================================
#pragma once
#ifndef _GROUPWIDGET_HPP_
#define _GROUPWIDGET_HPP_
#include <vector>
#include "BaseWidget2.hpp"
class Vector2;
class Matrix4x4;
class GLMeshRenderer;
class GroupWidget : public BaseWidget2
{
public:
	GroupWidget();
	void Update(float deltaSeconds, Vector2& cursorPos);
	void Draw(const Matrix4x4& ortho, const Matrix4x4& I);
	void AddWidget(BaseWidget2* newWidget);
	virtual void SetDragable(bool enable);
	virtual void SetWidgetByStyle(const std::string styleName);
	Vector2 GetMins();
	Vector2 GetMaxs();
	Vertex3D_PCT* CreateVerts(int& size);
	Vertex3D_PCT* GetTextVerts(int& size);
	std::vector<BaseWidget2*> m_widgets;
	GLMeshRenderer* m_renderer;
	GLMeshRenderer* m_textRenderer;
};


#endif