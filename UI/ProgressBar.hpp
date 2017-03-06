//==========================================================
//ProgressBar.hpp
//==========================================================
#pragma once
#ifndef _PROGRESSBAR_HPP_
#define _PROGRESSBAR_HPP_
#include "BaseWidget2.hpp"
class GLMeshRenderer;
enum ProgressBarStyle
{
	PROGRESSBAR_INVALID = -1,
	PROGRESSBAR_LEFT_TO_RIGHT,
	PROGRESSBAR_RIGHT_TO_LEFT,
	PROGRESSBAR_TOP_TO_BOTTOM,
	PROGRESSBAR_BOTTOM_TO_TOP,
	NUM_PROGRESSBAR_STYLE,
};

class ProgressBar :public BaseWidget2
{
public:
	ProgressBar();
	ProgressBar(const XMLNode& node);
	virtual void Draw(const Matrix4x4& Ortho, const Matrix4x4& I);
	virtual void Update(float deltaSecond, Vector2& mousePosition);
	void SetPercentage(float num);
	void SetMinsMaxs(const Vector2& mins, const Vector2& maxs);
	void SetStyle(ProgressBarStyle style) { m_progressBarStyle = style; }
	//////////////////////////////////////////////////////////////////////////
private:
	void SetRenderer();
	Vertex3D_PCT* CreateVerts(int& size);
	void GetEdgeVerts(Vertex3D_PCT* edgeVerts);
	Vertex3D_PCT* GetTextVerts(int& size);
	GLMeshRenderer* m_renderer;
	GLMeshRenderer* m_textRenderer;
	float m_percentage;
	ProgressBarStyle m_progressBarStyle;
};

#endif