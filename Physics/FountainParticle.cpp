#include "FountainParticle.hpp"

FountainParticle::FountainParticle()
{
	m_particles.clear();
	m_willBounce = false;
}
FountainParticle::~FountainParticle()
{

}
FountainParticle::FountainParticle(const Vector3& position, const Vector3& exitDiscCenter, float exitRadius, int particleNumber, Vector3 forceVector, Vector3 gravityVector, float mass, float lifeTime, float cofficient)
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
	m_exitDiscCenter = exitDiscCenter;
	m_exitRadius = exitRadius;
	StartUp();
}

void FountainParticle::StartUp()
{
	float xMin;
	float xMax;
	float yMin;
	float yMax;
	for (int i = 0; i < m_particleNumber; i++)
	{	
		float upVelocity = MathUtils::GetRandomFloatZeroToOne();
		float upTime = (m_exitDiscCenter.z - m_explosionPosition.z) / upVelocity;
		xMax = (abs(m_exitDiscCenter.x - m_explosionPosition.x) + m_exitRadius)/upTime;
		xMin = (-abs(m_exitDiscCenter.x - m_explosionPosition.x) - m_exitRadius)/upTime;
		yMax = (abs(m_exitDiscCenter.y - m_explosionPosition.y) + m_exitRadius)/upTime;
		yMin = (-abs(m_exitDiscCenter.y - m_explosionPosition.y) - m_exitRadius)/upTime;
		Vector3 velocity(MathUtils::GetRandomFloatInRange(xMin, xMax), MathUtils::GetRandomFloatInRange(yMin, yMax), upVelocity);
		Particle newParticle(m_explosionPosition, 1.0f*velocity, m_mass, m_forceVector, m_lifeTime, RGBA(MathUtils::GetRandomFloatZeroToOne(), MathUtils::GetRandomFloatZeroToOne(), MathUtils::GetRandomFloatZeroToOne()));
		m_particles.push_back(newParticle);
	}
}

void FountainParticle::Update(float deltaSecond)
{
	float xMin;
	float xMax;
	float yMin;
	float yMax;
	float upVelocity = MathUtils::GetRandomFloatZeroToOne();
	float upTime = (m_exitDiscCenter.z - m_explosionPosition.z) / upVelocity;
	xMax = (abs(m_exitDiscCenter.x - m_explosionPosition.x) + m_exitRadius) / upTime;
	xMin = (-abs(m_exitDiscCenter.x - m_explosionPosition.x) - m_exitRadius) / upTime;
	yMax = (abs(m_exitDiscCenter.y - m_explosionPosition.y) + m_exitRadius) / upTime;
	yMin = (-abs(m_exitDiscCenter.y - m_explosionPosition.y) - m_exitRadius) / upTime;
	Vector3 velocity(MathUtils::GetRandomFloatInRange(xMin, xMax), MathUtils::GetRandomFloatInRange(yMin, yMax), upVelocity);
	Particle newParticle(m_explosionPosition, 1.0f*velocity, m_mass, m_forceVector, m_lifeTime, RGBA(MathUtils::GetRandomFloatZeroToOne(), MathUtils::GetRandomFloatZeroToOne(), MathUtils::GetRandomFloatZeroToOne()));
	m_particles.push_back(newParticle);
	m_particleNumber++;
	for (int i = 0; i < m_particleNumber; i++)
	{
		float tempgravity = -m_gravityVector.z;
		Vector3 tempForce = m_forceVector;
		if (m_particles[i].m_canDrop == false && m_particles[i].m_position.z < m_exitDiscCenter.z)
		{
			tempgravity = 0.0f;
			tempForce = Vector3(0.0f, 0.0f, 0.0f);
		}
		else
		{
			m_particles[i].m_canDrop = true;
			tempgravity = -m_gravityVector.z;
		}
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
		Vector3 A = Fc + tempForce;
		delta_prev_velocity = A*deltaSecond;
		delta_prev_velocity.z = tempgravity*deltaSecond;
		
		next_position = prev_position + delta_prev_position;
		next_velocity = prev_velocity + delta_prev_velocity;

		m_particles[i].m_position = next_position;
		m_particles[i].m_velocity = next_velocity;
		if (m_willBounce == true && m_particles[i].m_position.z < -10.0f)
		{
			m_particles[i].m_velocity.z *= -1.0f;
		}
	}

}

void FountainParticle::Draw(OpenGLRenderer* renderer)
{
	for (int i = 0; i < m_particleNumber; i++)
	{
		m_particles[i].Draw(renderer);
	}
}