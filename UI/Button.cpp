//==========================================================
//Button.cpp
//==========================================================
#include "Engine/UI/Button.hpp"
#include "Engine/Math/AABB2D.hpp"
#include "Engine/EventSystem/NamedProperties.hpp"
#include "Engine/EventSystem/KeyFrameSequence.hpp"
Button::Button(Vector2 mins, Vector2 maxs, RGBA color)
	:BaseWidget(mins,maxs,color)
{
}

Button::Button()
	:BaseWidget(Vector2(100.0f,100.0f),Vector2(200.0f,200.f),RGBA(1.0f,0.0f,1.0f))
{

}

///----------------------------------------------------------
///
///----------------------------------------------------------

void Button::Update(float deltaSecond, Vector2& mousePosition)
{
	m_timeCheck += deltaSecond;
	AABB2D box(m_mins[m_currentState], m_maxs[m_currentState]);
	if (box.IsPointInside(mousePosition))
	{
		m_currentState = WIDGET_STATE_SELECTING;
	}
	else
		m_currentState = WIDGET_STATE_ENABLE;

	CopyData();
	if (m_currentState == WIDGET_STATE_SELECTING)
	{
		KeyFrameSequence<RGBA> resultC;
		m_properties[WIDGET_STATE_SELECTING].Get("bgColor", resultC);
		RGBA C = resultC.GetValueAtParametric(m_timeCheck);
		m_BGColor[WIDGET_CURRENT_STATE] = C;
	}
	
}

