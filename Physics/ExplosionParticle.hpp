//==========================================================
//ExplosionPartical.hpp
//==========================================================

#pragma once

#include "Particle.hpp"

class ExplosionParticle
{
public:
	ExplosionParticle();
	ExplosionParticle(const Vector3& position, int particalNumber, Vector3 forceVector, Vector3 gravityVector, float mass, float lifeTime, float cofficient);
	~ExplosionParticle();

	void StartUp();
	void Update(float deltaSecond);
	void Draw(OpenGLRenderer* renderer);

	Vector3 m_explosionPosition;
	int m_particleNumber;
	Vector3 m_forceVector;
	Vector3 m_gravityVector;
	float m_mass;
	float m_lifeTime;
	float m_cofficient;
	bool m_willBounce;
	std::vector<Particle> m_particles;
};