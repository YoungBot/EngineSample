//==========================================================
//DebugShape.hpp
//==========================================================

#pragma once
#include "Engine/Renderer/OpenGLRenderer.hpp"
#include "Engine/Renderer/RGBA.hpp"
#ifndef DEBUGSHAPE_HPP
#define DEBUGSHAPE_HPP


class DebugShape
{
public:
	enum ShapeType
	{
		SHAPE_INVALID = -1,
		SHAPE_TYPE_POINT,
		SHAPE_TYPE_LINESEGMENT,
		SHAPE_TYPE_ARROW,
		SHAPE_TYPE_SPHERE,
		SHAPE_TYPE_AABB3D,
		SHAPE_TYPE_AABB3DFRAME,
		INVALID_SHAPE_TYPE,
		NUM_SHAPE_TYPES
	};
	enum DepthTestType
	{
		DEPTH_TEST_TYPE_INVALID = -1,
		DEPTH_TEST_ON,
		DEPTH_TEST_OFF,
		DEPTH_TEST_DUAL_MODE,
		NUM_DEPTH_TEST_TYPES
	};

	DebugShape();
	DebugShape(ShapeType shapeType);
	~DebugShape();
	void Draw(OpenGLRenderer* renderer);
	void Update(float deltaTime);
	
	bool m_isTimeLimit;
	float m_deathTime;
	ShapeType m_shapeType;
	Vector3 m_firstPoint;
	Vector3 m_secondPoint;
	float m_radius;
	RGBA m_color;
	DepthTestType m_depthTestType;


};



#endif