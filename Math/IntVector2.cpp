//==========================================================
//IntVector2.cpp
//==========================================================
#include "IntVector2.hpp"
#include <math.h>

float IntVector2::CaculateDistance(IntVector2 startPos, IntVector2 endPos)
{
	float res = sqrt((float)(startPos.x - endPos.x)*(startPos.x - endPos.x) + (float)(startPos.y - endPos.y)*(startPos.y - endPos.y));
	return res;
}