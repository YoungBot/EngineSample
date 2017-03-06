//==========================================================
//ExplosionPartical.cpp
//==========================================================

#include "ExplosionParticle.hpp"

ExplosionParticle::ExplosionParticle()
{
	m_particles.clear();
	m_willBounce = false;
}
ExplosionParticle::~ExplosionParticle()
{

}
ExplosionParticle::ExplosionParticle(const Vector3& position, int particleNumber, Vector3 forceVector, Vector3 gravityVector, float mass, float lifeTime, float cofficient)
{
	m_explosionPosition = position;
	m_particleNumber = particleNumber;
	m_forceVector = forceVector;
	m_gravityVector = gravityVector;
	m_mass = mass;
	m_lifeTime = lifeTime;
	m_cofficient = cofficient;
	m_particles.clear();
	m_willBounce = false;
	StartUp();
}

void ExplosionParticle::StartUp()
{
	
	for (int i = 0; i < m_particleNumber; i++)
	{
		float velocityX = MathUtils::GetRandomFloatInRange(-1.0f, 1.0f);
		float velocityY = MathUtils::GetRandomFloatInRange(-1.0f, 1.0f);
		float velocityZ = MathUtils::GetRandomFloatInRange(-1.0f, 1.0f);
		Vector3 velocity(velocityX*velocityY,velocityY*velocityZ,velocityZ*velocityX);
		Particle newParticle(m_explosionPosition, velocity, m_mass, m_forceVector, m_lifeTime, RGBA(MathUtils::GetRandomFloatZeroToOne(), MathUtils::GetRandomFloatZeroToOne(), MathUtils::GetRandomFloatZeroToOne()));
		m_particles.push_back(newParticle);
	}
}

void ExplosionParticle::Update(float deltaSecond)
{
	//float velocityX = MathUtils::GetRandomFloatInRange(-1.0f, 1.0f);
	//float velocityY = MathUtils::GetRandomFloatInRange(-1.0f, 1.0f);
	//float velocityZ = MathUtils::GetRandomFloatInRange(-1.0f, 1.0f);
	//Vector3 velocity(velocityX*velocityY, velocityY*velocityZ, velocityZ*velocityX);
	//Particle newParticle(m_explosionPosition, velocity, m_mass, m_forceVector, m_lifeTime, RGBA(MathUtils::GetRandomFloatZeroToOne(), MathUtils::GetRandomFloatZeroToOne(), MathUtils::GetRandomFloatZeroToOne()));
	//m_particles.push_back(newParticle);
	//m_particleNumber++;

	for (int i = 0; i < m_particleNumber; i++)
	{
		Vector3 prev_position = m_particles[i].m_position;
		Vector3 prev_velocity = m_particles[i].m_velocity;

		Vector3 next_position;
		Vector3 next_velocity;

		Vector3 delta_prev_position;
		Vector3 delta_prev_velocity;

		delta_prev_position = prev_velocity;

		delta_prev_velocity.x = 0.0f;
		delta_prev_velocity.y = 0.0f;
		Vector3 e = prev_velocity;
		e.Normalize();
		Vector3 Fc = -m_cofficient * e;
		Vector3 Fk = m_forceVector;
		Vector3 A = Fc + Fk;

		
		delta_prev_velocity = A*deltaSecond;
		delta_prev_velocity.z = -m_gravityVector.z*deltaSecond;
		next_position = prev_position + delta_prev_position;
		next_velocity = prev_velocity + delta_prev_velocity;

		m_particles[i].m_position = next_position;
		m_particles[i].m_velocity = next_velocity;
		if (m_willBounce == true && m_particles[i].m_position.z<-10.0f)
		{
			m_particles[i].m_velocity.z *= -1.0f;
		}
	}
	//totalTime += deltaSecond;
	
}

void ExplosionParticle::Draw(OpenGLRenderer* renderer)
{
	for (int i = 0; i < m_particleNumber; i++)
	{
		m_particles[i].Draw(renderer);
	}
}