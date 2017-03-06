//==========================================================
//Label.hpp
//==========================================================
#pragma once
#ifndef _LABLE_HPP_
#define _LABLE_HPP_
#include "BaseWidget2.hpp"
class GLMeshRenderer;
struct XMLNode;
class Label : public BaseWidget2
{
public:
	Label();
	Label(BaseWidget2 copy);
	Label(const XMLNode& node);
	virtual void Draw(const Matrix4x4& Ortho, const Matrix4x4& I);
	void SetText(const std::string& text, RGBA color, float scale, WidgetState2 state = WIDGET_STATE_ENABLE_);
	void SetRenderer();
	virtual void Update(float deltaSecond, Vector2& mousePosition);
	Vertex3D_PCT* CreateVerts(int& size);
	void GetEdgeVerts(Vertex3D_PCT* edgeVerts);
	Vertex3D_PCT* GetTextVerts(int& size);
	bool m_editable;
	bool m_isEditing;
	GLMeshRenderer* m_renderer;
	GLMeshRenderer* m_textRenderer;
};

#endif