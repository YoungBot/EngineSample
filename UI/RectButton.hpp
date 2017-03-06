//==========================================================
//RectButton.hpp
//==========================================================
#pragma once
#ifndef _RECTBUTTON_HPP_
#define _RECTBUTTON_HPP_
#include "Button2.hpp"
struct XMLNode;
class RectButton : public Button2
{
public:
	RectButton();
	RectButton(BaseWidget2 copy);
	RectButton(const std::string& str);
	RectButton(const XMLNode& node);
	void Startup();
	virtual void Draw(const Matrix4x4& Ortho, const Matrix4x4& I);
	virtual void Update(float deltaSecond, Vector2& mousePosition);
	void Update(float deltaSecond, Vector2& mousePosition, NamedProperties* np = nullptr);
	Vertex3D_PCT* CreateVerts(int& size);
	void GetEdgeVerts(Vertex3D_PCT* edgeVerts);
	Vertex3D_PCT* GetTextVerts(int& size);
	void SetMinsAndMaxs(const Vector2& mins, const Vector2& maxs);
	void SetTexCo(const Vector2& mins, const Vector2& maxs);
	Vector2 GetTexCoTopLeft() const;
	Vector2 GetTexCoBotRight() const;
	void UpdateVerts();
	void SetText(const std::string& text);
};

#endif