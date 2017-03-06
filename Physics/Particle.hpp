//==========================================================
//Particle.hpp
//==========================================================

#pragma once
#include "Engine/Math/Vector3.hpp"
#include "Engine/Renderer/OpenGLRenderer.hpp"

class Particle
{
public:
	//enum ParticleType
	//{
	//	INVALID_PARTICLE_TYPE = -1,
	//};
	Particle();
	Particle(const Vector3& position, const Vector3& velocity, float mass, Vector3 forceVector,float lifeTime,const RGBA& color);
	~Particle();

	void Update(float deltaSecond);
	void Draw(OpenGLRenderer* renderer);
	Vector3 m_position;
	Vector3 m_velocity;
	float m_mass;
	Vector3 m_forceVector;
	float m_lifeTime;
	bool m_canDrop;
	RGBA m_color;

};