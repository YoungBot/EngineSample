//==========================================================
//EditableLabel.hpp
//==========================================================
#pragma once
#ifndef _EDITABLELABLE_HPP_
#define _EDITABLELABLE_HPP_
#include "Label.hpp"
struct XMLNode;
class EditableLabel : public Label
{
public:
	EditableLabel();
	EditableLabel(BaseWidget2 copy);
	EditableLabel(const XMLNode& node);
	virtual void Update(float deltaSecond, Vector2& mousePosition);
	virtual void Drag(Vector2& mousePosition);
	void StartTyping();
	bool m_isTyping;
	bool m_isFixingSize;
private:
	void InsertCharacter(const unsigned int key);
	void RemoveLastCharacter();
	void ResizeBox();
};


#endif