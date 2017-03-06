//==========================================================
//YoYoParticleModel.hpp
//==========================================================

#pragma once
#include "Particle.hpp"

class YoYoParticleModel
{
	struct myState
	{
		Vector3 pos;
		Vector3 vel;
		myState():pos(Vector3(0.0f,0.0f,0.0f)),vel(Vector3(0.0f,0.0f,0.0f)){}
		myState operator * (float scale)
		{
			myState result;
			pos *= scale;
			vel *= scale;
			return result;
		}
		myState operator + (myState add)
		{
			myState result;
			pos += add.pos;
			vel += add.vel;
			return result;
		}
	};
public:
	YoYoParticleModel();
	YoYoParticleModel(float stringLength, float cofficient, Vector3 gravityVector, float stringCofficient, float stiffness, float mass);
	~YoYoParticleModel();

	void Update(float deltaSecond);
	void Draw(OpenGLRenderer* renderer);
	void RK4(myState& preState, myState& resultState,float deltaT);
	void func(myState& preState, myState& resultState, float deltaT);
	Particle m_topParticle;
	Particle m_yoyoParticle;
	float m_stringLength;
	float m_cofficient;
	float m_stringCofficient;
	Vector3 m_gravityVector;
	float m_stiffness;
	float m_yoyoMass;
};

