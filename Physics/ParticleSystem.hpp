//==========================================================
//ParticleSystem.hpp
//==========================================================

#pragma once
//#include "Particle.hpp"
#include "YoYoParticleModel.hpp"
#include "ExplosionParticle.hpp"
#include "FountainParticle.hpp"
#include "SpinParticle.hpp"
class ParticleSystem
{
public:
	ParticleSystem();
	//ParticleSystem();
	~ParticleSystem();
	void Update(float deltaSeconds);
	void Draw(OpenGLRenderer* renderer);
	std::string m_strategyName;
	std::vector<Particle*> m_particles;
	Vector3 m_position;


};

