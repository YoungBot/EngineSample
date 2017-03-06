//==========================================================
//Button.hpp
//==========================================================
#pragma once
#ifndef _BUTTON_HPP_
#define _BUTTON_HPP_
#include "BaseWidget.hpp"

class Button : public BaseWidget
{
public:
	Button();
	Button(Vector2 mins, Vector2 maxs, RGBA color);
	virtual void Update(float deltaSecond, Vector2& mousePosition);
};

#endif
