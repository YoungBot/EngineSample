//==========================================================
//CheckBox.hpp
//==========================================================
#pragma once
#ifndef _CHECKBOX_HPP_
#define _CHECKBOX_HPP_
#include "BaseWidget2.hpp"
#include <vector>
#include <string>
class GLMeshRenderer;
enum CheckBoxStyle
{
	RADIO_SINGLE_WIDGET,
	CHECKBOX_MULTIPLE,
	NUM_CHECKBOX_STYLE
};
class CheckBox : public BaseWidget2
{
public:
	CheckBox(CheckBoxStyle style);
	CheckBox();
	CheckBox(const XMLNode& node);
	virtual void Draw(const Matrix4x4& Ortho, const Matrix4x4& I);
	virtual void Update(float deltaSecond, Vector2& mousePosition);
	void AddOption(std::string newOption);
	void SetOptionByIndex(const std::string& option, int index);
	void SetStyle(CheckBoxStyle style);
	void AddSelection(int);
	//////////////////////////////////////////////////////////////////////////
private:
	void SetRenderer();
	Vertex3D_PCT* CreateVerts(int& size);
	void GetEdgeVerts(Vertex3D_PCT* edgeVerts);
	Vertex3D_PCT* GetTextVerts(int& size);

	GLMeshRenderer* m_renderer;
	GLMeshRenderer* m_textRenderer;
	std::vector<std::string> m_options;
	std::vector<unsigned int> m_selectedIndexes;
	CheckBoxStyle m_checkBoxStyle;
};

#endif