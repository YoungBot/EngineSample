//==========================================================
//DropdownWidget.hpp
//==========================================================
#pragma once
#ifndef _DROPDOWNWIDGET_HPP_
#define _DROPDOWNWIDGET_HPP_
#include "RectButton.hpp"

class DropdownWidget :public BaseWidget2
{
public:
	DropdownWidget();
	DropdownWidget(DropdownWidget* widget);
	DropdownWidget(const XMLNode& node);
	virtual void Draw(const Matrix4x4& Ortho, const Matrix4x4& I);
	virtual void Update(float deltaSecond, Vector2& mousePosition);
	void AddNewOption(const std::string& optionStr);
	void SwitchOption(int index);
	//Vertex3D_PCT* CreateVerts(int& size);
	//void GetEdgeVerts(Vertex3D_PCT* edgeVerts);
	//Vertex3D_PCT* GetTextVerts(int& size);
	std::vector<RectButton*> m_options;
	bool m_isExpend;
	GLMeshRenderer* m_renderer;
	GLMeshRenderer* m_textRenderer;
};
#endif