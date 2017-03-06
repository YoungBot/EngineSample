//==========================================================
//Particle.cpp
//==========================================================

#include "Particle.hpp"
#include "Engine/Renderer/DebugShapeSystem.hpp"

Particle::Particle()
{
	m_position = Vector3(0.0f, 0.0f, 0.0f);
	m_velocity = Vector3(0.0f, 0.0f, 0.0f);
	m_mass = 0.0f;
	m_forceVector = Vector3(0.0f, 0.0f, 0.0f);
	m_canDrop = false;
}
Particle::Particle(const Vector3& position, const Vector3& velocity, float mass, Vector3 forceVector, float lifeTime,const RGBA& color)
{
	m_position = position;
	m_velocity = velocity;
	m_mass = mass;
	m_forceVector = forceVector;
	m_lifeTime = lifeTime;
	m_canDrop = false;
	m_color = color;
}
Particle::~Particle()
{

}
void Particle::Draw(OpenGLRenderer* renderer)
{
	//renderer->DrawSphere(m_position, 0.2f, m_color, DebugShape::DEPTH_TEST_ON);
	renderer->DrawStarPoint(m_position, m_color, DebugShape::DEPTH_TEST_ON);
}
void Particle::Update(float deltaSecond)
{
	deltaSecond;
}
