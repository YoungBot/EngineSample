//==========================================================
//StringSystem.hpp
//==========================================================
#pragma once

#include "Particle.hpp"
#include "Engine/Math/Vector2.hpp"


struct StringVerts
{
	Vector3 m_position;
	float m_mass;
	bool m_isPinned;
	Vector3 m_velocity;
	void StartUp();
	StringVerts(Vector3 position, float mass)
	{
		m_position = position; 
		m_mass = mass; 
		m_isPinned = false;
		m_velocity = Vector3(0.0f, 0.0f, 0.0f);
	}
};

class StringSystem
{
public:
	StringSystem();
	StringSystem(float stringLength, float cofficient, Vector3 gravityVector, float stringCofficient, float stiffness, float mass,int rowNum,int colNum);
	void StartUp();
	void Update(float deltaTime,OpenGLRenderer* renderer);
	void Draw(OpenGLRenderer* renderer);
	NTBVertex3D_PCT* createTBN(int& size);
	void Unpin();
	float m_stringLength;
	float m_cofficient;
	float m_stringCofficient;
	Vector3 m_gravityVector;
	float m_stiffness;
	float m_yoyoMass;
	int m_row;
	int m_col;
	std::vector<StringVerts> m_verts;
};

