//==========================================================
//Character.cpp
//==========================================================
#include "Character.hpp"

Character::Character(short ID, const Vector2& XY, const Vector2& WH, const Vector2& GLYPHWH, const Vector2& OffsetXY, float XAdvance) :
m_ID(ID), m_XY(XY), m_WH(WH), m_OffsetXY(OffsetXY), m_XAdvance(XAdvance), m_GLYPHWH(GLYPHWH)
{
	
}
//////////////////////////////////////////////////////////////////////////
Character::Character():
m_ID(-2), m_XY(Vector2(-1.0f, -1.0f)), m_WH(Vector2(-1.0f, -1.0f)), m_OffsetXY(Vector2(-1.0f, -1.0f)), m_XAdvance(-1.0f)
{

}
//////////////////////////////////////////////////////////////////////////
Character::~Character()
{

}