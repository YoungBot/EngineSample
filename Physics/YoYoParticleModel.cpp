//==========================================================
//YoYoParticleModel.cpp
//==========================================================
#include "YoYoParticleModel.hpp"
YoYoParticleModel::YoYoParticleModel()
{
}

YoYoParticleModel::~YoYoParticleModel()
{
}

YoYoParticleModel::YoYoParticleModel(float stringLength, float cofficient, Vector3 gravityVector, float stringCofficient, float stiffness, float mass)
{
	m_stringLength = stringLength;
	m_cofficient = cofficient;
	m_gravityVector = gravityVector;
	m_stringCofficient = stringCofficient;
	m_stiffness = stiffness;
	m_yoyoMass = mass;
	m_topParticle = Particle(Vector3(10.0f, 10.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 0.0f, Vector3(0.0f, 0.0f, 0.0f), 1.0f, RGBA(MathUtils::GetRandomFloatZeroToOne(), MathUtils::GetRandomFloatZeroToOne(), MathUtils::GetRandomFloatZeroToOne()));
	m_yoyoParticle = Particle(Vector3(10.0f, 10.0f, -m_stringLength), Vector3(0.0f, 0.0f, 0.0f), 1.0f, Vector3(0.0f, 0.0f, 0.0f), 1.0f, RGBA(MathUtils::GetRandomFloatZeroToOne(), MathUtils::GetRandomFloatZeroToOne(), MathUtils::GetRandomFloatZeroToOne()));
}

void YoYoParticleModel::Update(float deltaSecond)
{
	static float time = 0.0f;
	static int count = 0;
	time += deltaSecond;
	if (time>=0.1f)
	{
		time = 0.0f;
		m_topParticle.m_position += Vector3(MathUtils::GetRandomFloatZeroToOne(), MathUtils::GetRandomFloatZeroToOne(), MathUtils::GetRandomFloatZeroToOne());		
		count++;

	}
	if (count >=20)
	{
		m_topParticle.m_position.x = -m_topParticle.m_position.x;
		m_topParticle.m_position.y = -m_topParticle.m_position.y;
		m_topParticle.m_position.z = -m_topParticle.m_position.z;
		m_topParticle.m_position *= 0.1f;
		count = 0;
	}
	//////////////////////////////////////////////////////////////////////////
		Vector3 prev_position = m_yoyoParticle.m_position;
		Vector3 prev_velocity = m_yoyoParticle.m_velocity;
			  
		Vector3 next_position;
		Vector3 next_velocity;
			 
		Vector3 delta_prev_position;
		Vector3 delta_prev_velocity;
		
		delta_prev_position = prev_velocity;

		delta_prev_velocity.x = 0.0f;
		delta_prev_velocity.y = 0.0f;
		Vector3 e = (m_yoyoParticle.m_position - m_topParticle.m_position);
		e.Normalize();
		Vector3 Fk = -m_stiffness*((m_yoyoParticle.m_position - m_topParticle.m_position).CalcLength()-m_stringLength) * e;
		Vector3 Fc = -m_cofficient * (DotProduct(e,(m_yoyoParticle.m_velocity-m_topParticle.m_velocity))) *e ;
		Vector3 A = Fk + Fc - m_yoyoParticle.m_mass*m_gravityVector - m_stringCofficient*m_yoyoParticle.m_velocity;
		
		delta_prev_velocity.z = -m_gravityVector.z*deltaSecond;
		delta_prev_velocity = A*deltaSecond;

		//myState prev;
		//prev.pos = prev_position;
		//prev.vel = prev_velocity;
		//myState next;
		//RK4(prev, next, deltaSecond);






		
		

		next_position = prev_position + delta_prev_position;
		next_velocity = prev_velocity + delta_prev_velocity;
	
		m_yoyoParticle.m_position = next_position;
		m_yoyoParticle.m_velocity = next_velocity;
		//m_yoyoParticle.m_position = next.pos;
		//m_yoyoParticle.m_velocity = next.vel;
}
void YoYoParticleModel::Draw(OpenGLRenderer* renderer)
{
	m_yoyoParticle.Draw(renderer);
	m_topParticle.Draw(renderer);
	renderer->DrawLineSegment(m_yoyoParticle.m_position, m_topParticle.m_position, RGBA(1.0F, 0.0F, 1.0F), 1);
}
void YoYoParticleModel::func(myState& preState, myState& resultState,float deltaT)
{
	resultState.pos = preState.vel*deltaT;

	Vector3 e = (m_yoyoParticle.m_position - m_topParticle.m_position);
	e.Normalize();
	Vector3 Fk = -m_stiffness*((m_yoyoParticle.m_position - m_topParticle.m_position).CalcLength() - m_stringLength) * e;
	Vector3 Fc = -m_cofficient * (DotProduct(e, (m_yoyoParticle.m_velocity - m_topParticle.m_velocity))) *e;
	Vector3 A = Fk + Fc - m_yoyoParticle.m_mass*m_gravityVector - m_stringCofficient*m_yoyoParticle.m_velocity;
	
	Vector3 delta_prev_velocity = A*deltaT;
	delta_prev_velocity.z = -m_gravityVector.z*deltaT;
	resultState.vel = delta_prev_velocity;
	
}
void YoYoParticleModel::RK4(myState& preState, myState& resultState, float deltaT)
{
	preState;
	myState deltaState1;
	myState deltaState2;
	myState deltaState3;
	myState deltaState4;
	myState s1;
	s1.pos = m_yoyoParticle.m_position;
	s1.vel = m_yoyoParticle.m_velocity;
	myState s2;
	func(s1, deltaState1, deltaT);
	s2 = s1 + deltaState1*(deltaT / 2);
	myState s3;
	func(s2, deltaState2, deltaT);
	s3 = s1 + deltaState2*(deltaT / 2);
	myState s4;
	func(s3, deltaState3, deltaT);
	s4 = s1 + deltaState3*deltaT;
	func(s4, deltaState4, deltaT);
	resultState = s1 + (deltaState1 + (deltaState2 * 2) + (deltaState3 * 2) + (deltaState4)* 2)*(deltaT / 6) ;

}
