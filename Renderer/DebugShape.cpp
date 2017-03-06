//==========================================================
//DebugShape.cpp
//==========================================================

#include "DebugShape.hpp"

DebugShape::DebugShape()
{
	m_isTimeLimit = false;
	m_deathTime = 0.0f;
	m_shapeType = INVALID_SHAPE_TYPE;
	m_firstPoint = Vector3(0.0f, 0.0f, 0.0f);
	m_secondPoint = Vector3(0.0f, 0.0f, 0.0f);
	m_radius = 0.0f;
	m_color = RGBA(1.0f, 1.0f, 1.0f);
}

DebugShape::~DebugShape()
{
}

DebugShape::DebugShape(ShapeType shapeType)
{
	m_isTimeLimit = false;
	m_deathTime = 0.0f;
	m_shapeType = shapeType;
	m_firstPoint = Vector3(0.0f, 0.0f, 0.0f);
	m_secondPoint = Vector3(0.0f, 0.0f, 0.0f);
	m_radius = 0.0f;
	m_color = RGBA(1.0f, 1.0f, 1.0f);
}

void DebugShape::Draw(OpenGLRenderer* renderer)
{
	if (m_isTimeLimit && m_deathTime<0.0f)
	{
		return;
	}
	if (m_shapeType == SHAPE_TYPE_POINT)
	{
		renderer->DrawStarPoint(m_firstPoint, m_color,(unsigned int)m_depthTestType);
	}
	else if (m_shapeType == SHAPE_TYPE_LINESEGMENT)
	{
		renderer->DrawLineSegment(m_firstPoint, m_secondPoint, m_color, (unsigned int)m_depthTestType);
	}
	else if (m_shapeType == SHAPE_TYPE_ARROW)
	{
		renderer->DrawArrow(m_firstPoint, m_secondPoint, m_color, (unsigned int)m_depthTestType);
	}
	else if (m_shapeType == SHAPE_TYPE_SPHERE)
	{
		renderer->DrawSphere(m_firstPoint, m_radius, m_color, (unsigned int)m_depthTestType);
	}
	else if (m_shapeType == SHAPE_TYPE_AABB3D)
	{
		renderer->DrawAABB3D(m_firstPoint, m_secondPoint, m_color, (unsigned int)m_depthTestType);
	}
	else if (m_shapeType == SHAPE_TYPE_AABB3DFRAME)
	{
		renderer->DrawAABB3DFrame(m_firstPoint, m_secondPoint, m_color, (unsigned int)m_depthTestType);
	}
}
///------------------------------------------------------
///
///------------------------------------------------------
void DebugShape::Update(float deltaTime)
{
	if (m_isTimeLimit && m_deathTime>=0.0f)
	{
		m_deathTime -= deltaTime;
	}
	
}