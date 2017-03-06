//==========================================================
//SpinParticle.hpp
//==========================================================

#pragma once

#include "Particle.hpp"

class SpinParticle
{
public:
	SpinParticle();
	SpinParticle(const Vector3& position, float sspinRadius, int particalNumber, Vector3 forceVector, Vector3 gravityVector, float mass, float lifeTime, float cofficient);
	~SpinParticle();

	void StartUp();
	void Update(float deltaSecond);
	void Draw(OpenGLRenderer* renderer);

	Vector3 m_explosionPosition;
	int m_particleNumber;
	Vector3 m_forceVector;
	Vector3 m_gravityVector;
	Vector3 m_exitDiscCenter;
	float m_spinRadius;
	float m_mass;
	float m_lifeTime;
	float m_cofficient;
	bool m_willBounce;
	std::vector<Particle> m_particles;
}; 