//==========================================================
//SliderWidget.hpp
//==========================================================
#pragma once
#ifndef _SLIDERWIDGET_HPP_
#define _SLIDERWIDGET_HPP_
#include "BaseWidget2.hpp"
class GLMeshRenderer;
struct XMLNode;

class SliderWidget : public BaseWidget2
{
public:
	SliderWidget();
	SliderWidget(SliderWidget* slider);
	SliderWidget(const XMLNode& node);
	virtual void Draw(const Matrix4x4& Ortho, const Matrix4x4& I);
	virtual void Update(float deltaSecond, Vector2& mousePosition);
	void SetRenderer();
	Vertex3D_PCT* CreateVerts(int& size);
	void GetSliderVerts(Vertex3D_PCT* sliderVerts);
	Vertex3D_PCT* GetTextVerts(int& size);
	float m_percentage;
	GLMeshRenderer* m_renderer;
	GLMeshRenderer* m_textRenderer;
	Vector2 m_mouseStartPositionForSlider;
	bool m_startSlide;
};

#endif