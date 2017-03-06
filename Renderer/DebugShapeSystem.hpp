//==========================================================
//DebugShapeSystem.hpp
//==========================================================
#pragma once

#include "DebugShape.hpp"

class DebugShapeSystem
{
public:
	DebugShapeSystem();
	~DebugShapeSystem();

	void Draw(OpenGLRenderer* renderer);
	void Update(float deltaSecond);
	void DrawSphere(const Vector3& center, float radius, RGBA& Color, DebugShape::DepthTestType depthTestType, float deathTime);
	void DrawAABB3DFrame(const Vector3& mins, const Vector3& maxs, RGBA& Color, DebugShape::DepthTestType depthTestType, float deathTime);
	void DrawAABB3D(const Vector3& mins, const Vector3& maxs, RGBA& Color, DebugShape::DepthTestType depthTestType, float deathTime);
	void DrawLineSegment(const Vector3& startPos, const Vector3& endPos, RGBA& Color, DebugShape::DepthTestType depthTestType, float deathTime);
	void DrawPoint(const Vector3& position, RGBA& Color, DebugShape::DepthTestType depthTestType, float deathTime);
	void DrawArrow(const Vector3& startPos, const Vector3& endPos, RGBA& Color, DebugShape::DepthTestType depthTestType, float deathTime);
	std::vector<DebugShape*> m_debugShapes;
};
extern DebugShapeSystem* s_debugShapeSystem;
