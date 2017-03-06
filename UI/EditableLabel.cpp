//==========================================================
//EditableLabel.cpp
//==========================================================
#include "EditableLabel.hpp"
#include "Engine/Input/InputSystem.hpp"
#include <windows.h>
#include "Engine/Math/AABB2D.hpp"
EditableLabel::EditableLabel()
	:Label()
	,m_isTyping(false)
	,m_isFixingSize(true)
{
	m_forStates[WIDGET_STATE_SELECT_].fromCode.Set("BGColor", RGBA(0.3f, 0.3f, 0.3f, 1.0f));
}

EditableLabel::EditableLabel(const XMLNode& node)
	:Label(node)
	,m_isTyping(false)
	, m_isFixingSize(true)
{
	
}

EditableLabel::EditableLabel(BaseWidget2 copy)
	:Label(copy)
{

}

void EditableLabel::Update(float deltaSecond, Vector2& mousePosition)
{
	//ResizeBox();
	m_currentStateProperty = m_forStates[m_currentState];
	Vector2 offset = GetOffSet();
	if (m_isTyping)
	{
		StartTyping();
		if (m_isFixingSize)
		{
			ResizeBox();
		}
		
	}
	m_timeCheck += deltaSecond;
	Vector2 maxs;
	GetValueInCurrentState("maxs", maxs);
	Vector2 mins;
	GetValueInCurrentState("mins", mins);
	AABB2D box(mins + offset, maxs + offset);
	//////////////////////////////////////////////////////////////////////////
	if (s_theInputSystem->IsMouseButtonDown(VK_LBUTTON) && s_theInputSystem->IsKeyDown('C'))
	{
		if (box.IsPointInside(mousePosition))
		{
			SetDragable(true);
		}		
	}
	else
		SetDragable(false);
	if (m_enableDrag)
	{
		Drag(mousePosition);
		return;
	}
	
	if (s_theInputSystem->WasMouseButtonJustDown(VK_LBUTTON))
	{
		if (box.IsPointInside(mousePosition))
		{
			m_isTyping = true;
			m_currentState = WIDGET_STATE_SELECT_;
		}
		else
		{
			m_currentState = WIDGET_STATE_ENABLE_;
			m_isTyping = false;
		}
			
	}
	
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void EditableLabel::Drag(Vector2& mousePosition)
{
	if (m_mouseStartPosition == Vector2(0.0f, 0.0f))
	{
		m_mouseStartPosition = mousePosition;
	}
	Vector2 newoffset = mousePosition - m_mouseStartPosition;
	Vector2 offset(0.0f, 0.0f);
	GetValueInCurrentState("offset", offset);
	for (unsigned int i = 0; i < NUM_WIDGET_STATE_; i++)
	{
		m_forStates[i].fromWidget.Set("offset", offset + newoffset);
	}
	
	m_mouseStartPosition = mousePosition;
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void EditableLabel::StartTyping()
{
	for (int i = 0; i < NUMBER_OF_VIRTUAL_KEYS; i++)
	{
		if (s_theInputSystem->WasKeyJustDown(i))
		{
			if (s_theInputSystem->WasKeyJustDown(VK_BACK))
			{
				RemoveLastCharacter();
				return;
			}
			if (s_theInputSystem->IsKeyDown(VK_SHIFT))
			{
				if (i >= 65 && i <= 90)
				{
					InsertCharacter(i);
					return;
				}
				if (i == 57)
				{
					InsertCharacter(i);
					return;
				}
				if (i == 48)
				{
					InsertCharacter(i);
					return;
				}
			}
			if (i == 32)
			{
				InsertCharacter(i);
				return;
			}
			if (i >= 65 && i <= 90)
			{
				InsertCharacter(i + 32);
				return;
			}
			if (i >= 188 && i <= 191)
			{
				InsertCharacter(i - 144);
				return;
			}
			if (i == 186)
			{
				InsertCharacter(59);
				return;
			}
			if (i <= 57 && i >= 48)
			{
				InsertCharacter(i);
				return;
			}

		}
	}
}

void EditableLabel::InsertCharacter(const unsigned int key)
{
	std::string currentText = "";
	for (int i = 0; i < NUM_WIDGET_STATE_; i++)
	{
		m_forStates[i].fromWidget.Get("text", currentText);
		currentText.push_back((char)key);
		m_forStates[i].fromWidget.Set("text", currentText);
		currentText = "";
	}
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void EditableLabel::RemoveLastCharacter()
{
	std::string currentText = "";
	for (int i = 0; i < NUM_WIDGET_STATE_; i++)
	{
		PropertyGetResult result = m_forStates[i].fromWidget.Get("text", currentText);

		if (result == RESULT_FAILED_NO_SUCH_PROPERTY)
		{
			GetValueInCurrentState("text", currentText);
			m_forStates[i].fromWidget.Set("text",currentText);
		}

		if (currentText.size() > 0)
			currentText.pop_back();
		else
			continue;
		m_forStates[i].fromWidget.Set("text", currentText);
	}
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void EditableLabel::ResizeBox()
{
	Vector2 offset = GetOffSet();
	Vector2 maxs;
	GetValueInCurrentState("maxs", maxs);
	Vector2 mins;
	GetValueInCurrentState("mins", mins);
	float textScale;
	GetValueInCurrentState("textScale", textScale);
	std::string text;
	GetValueInCurrentState("text", text);
	float length = text.size() * textScale *0.7f +10.0f;
	maxs.x = mins.x + length;

	for (int i = 0; i < NUM_WIDGET_STATE_; i++)
	{
		m_forStates[i].fromWidget.Set("maxs", maxs);
	}
	
}
