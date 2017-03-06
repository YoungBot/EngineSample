//==========================================================
//Character.hpp
//==========================================================

#pragma once
#include "Engine/Math/Vector2.hpp"

class Character
{
public:
	//<char id = "32" x = "508" y = "68" width = "3" height = "1" xoffset = "-1" yoffset = "31" xadvance = "8" page = "0" chnl = "15" / >
	Character();
	Character(short ID, const Vector2& XY, const Vector2& WH, const Vector2& GLYPHWH, const Vector2& m_OffsetXY, float m_XAdvance);
	~Character();
	short m_ID;
	Vector2 m_XY;
	Vector2 m_WH;
	Vector2 m_GLYPHWH;
	Vector2 m_OffsetXY;
	float m_XAdvance;
};