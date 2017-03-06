//==========================================================
//DebugShapeSystem.cpp
//==========================================================

#include "Engine/Renderer/DebugShapeSystem.hpp"
DebugShapeSystem* s_debugShapeSystem = nullptr;
DebugShapeSystem::DebugShapeSystem()
{
	m_debugShapes.clear();
}

DebugShapeSystem::~DebugShapeSystem()
{
}

void DebugShapeSystem::Draw(OpenGLRenderer* renderer)
{
	if (m_debugShapes.size()>0)
	{
		for (unsigned int i = 0; i < m_debugShapes.size(); i++)
		{
			m_debugShapes[i]->Draw(renderer);
		}
	}
	
}

void DebugShapeSystem::Update(float deltaSecond)
{
	if (m_debugShapes.size()>0)
	{
		for (unsigned int i = 0; i < m_debugShapes.size(); i++)
		{
			m_debugShapes[i]->Update(deltaSecond);
		}
	}
}

void DebugShapeSystem::DrawSphere(const Vector3& center, float radius, RGBA& Color, DebugShape::DepthTestType depthTestType, float deathTime)
{
	DebugShape* newShape = new DebugShape(DebugShape::SHAPE_TYPE_SPHERE);
	newShape->m_firstPoint = center;
	newShape->m_radius = radius;
	newShape->m_color = Color;
	newShape->m_deathTime = deathTime;
	newShape->m_depthTestType = depthTestType;
	newShape->m_isTimeLimit = true;
	if (deathTime == -1.0f)
	{
		newShape->m_isTimeLimit = false;
	}
	m_debugShapes.push_back(newShape);
}
void DebugShapeSystem::DrawAABB3DFrame(const Vector3& mins, const Vector3& maxs, RGBA& Color, DebugShape::DepthTestType depthTestType, float deathTime)
{
	DebugShape* newShape = new DebugShape(DebugShape::SHAPE_TYPE_AABB3DFRAME);
	newShape->m_firstPoint = mins;
	newShape->m_secondPoint = maxs;
	newShape->m_color = Color;
	newShape->m_deathTime = deathTime;
	newShape->m_depthTestType = depthTestType;
	newShape->m_isTimeLimit = true;
	if (deathTime == -1.0f)
	{
		newShape->m_isTimeLimit = false;
	}
	m_debugShapes.push_back(newShape);
}
void DebugShapeSystem::DrawAABB3D(const Vector3& mins, const Vector3& maxs, RGBA& Color, DebugShape::DepthTestType depthTestType, float deathTime)
{
	DebugShape* newShape = new DebugShape(DebugShape::SHAPE_TYPE_AABB3D);
	newShape->m_firstPoint = mins;
	newShape->m_secondPoint = maxs;
	newShape->m_color = Color;
	newShape->m_deathTime = deathTime;
	newShape->m_depthTestType = depthTestType;
	newShape->m_isTimeLimit = true;
	if (deathTime == -1.0f)
	{
		newShape->m_isTimeLimit = false;
	}
	m_debugShapes.push_back(newShape);
}
void DebugShapeSystem::DrawLineSegment(const Vector3& startPos, const Vector3& endPos, RGBA& Color, DebugShape::DepthTestType depthTestType, float deathTime)
{
	DebugShape* newShape = new DebugShape(DebugShape::SHAPE_TYPE_LINESEGMENT);
	newShape->m_firstPoint = startPos;
	newShape->m_secondPoint = endPos;
	newShape->m_color = Color;
	newShape->m_deathTime = deathTime;
	newShape->m_depthTestType = depthTestType;
	newShape->m_isTimeLimit = true;
	if (deathTime == -1.0f)
	{
		newShape->m_isTimeLimit = false;
	}
	m_debugShapes.push_back(newShape);
}
void DebugShapeSystem::DrawPoint(const Vector3& position, RGBA& Color, DebugShape::DepthTestType depthTestType, float deathTime)
{
	DebugShape* newShape = new DebugShape(DebugShape::SHAPE_TYPE_POINT);
	newShape->m_firstPoint = position;	
	newShape->m_color = Color;
	newShape->m_deathTime = deathTime;
	newShape->m_depthTestType = depthTestType;
	newShape->m_isTimeLimit = true;
	if (deathTime == -1.0f)
	{
		newShape->m_isTimeLimit = false;
	}
	m_debugShapes.push_back(newShape);
}
void DebugShapeSystem::DrawArrow(const Vector3& startPos, const Vector3& endPos, RGBA& Color, DebugShape::DepthTestType depthTestType, float deathTime)
{
	DebugShape* newShape = new DebugShape(DebugShape::SHAPE_TYPE_ARROW);
	newShape->m_firstPoint = startPos;
	newShape->m_secondPoint = endPos;
	newShape->m_color = Color;
	newShape->m_deathTime = deathTime;
	newShape->m_depthTestType = depthTestType;
	newShape->m_isTimeLimit = true;
	if (deathTime == -1.0f)
	{
		newShape->m_isTimeLimit = false;
	}
	m_debugShapes.push_back(newShape);
}