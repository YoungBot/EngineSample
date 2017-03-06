//==========================================================
//CollisionDetection.hpp
//==========================================================
#include "Engine/Math/Vector3.hpp"

bool SphereIntersect(Vector3 p1, Vector3 q1, float r1, Vector3 p2, Vector3 q2, float r2)
{
	Vector3 e = q2 - q1 - p2 + p1;
	Vector3 x0 = q1 - p1;
	float edx0 = DotProduct(e, x0);
	float edx0s = edx0*edx0;
	float ee = DotProduct(e, e);
	float x0x0 = DotProduct(x0, x0);
	float root = (edx0s - ee*(x0x0 - r1*r2));
	if (root >= 0)
	{
		float t1 = (-edx0 - sqrt(root)) / ee;
		float t2 = (-edx0 + sqrt(root)) / ee;
		if (t1 <= 1 && t2 >= 0)
		{
			return true;
		}
		else
			return false;
	}
	else
	{
		return false;
	}
}

bool SphereImpact3D(float m1, Vector3& v1, float m2, Vector3& v2,Vector3 normalVector,float coefficient)
{
	float v1para = DotProduct(v1, normalVector);
	float v2para = DotProduct(v2, normalVector);
	Vector3 v1vert = v1 - DotProduct(v1, normalVector)*normalVector;
	Vector3 v2vert = v2 - DotProduct(v2, normalVector)*normalVector;
	float v1paraPrime = (m1*v1para + m2*v2para + coefficient*m2*(v2para-v1para))/(m1+m2);
	float v2paraPrime = (m1*v1para + m2*v2para - coefficient*m1*(v2para - v1para)) / (m1 + m2);

	v1 = v1paraPrime * normalVector + v1vert;
	v2 = v2paraPrime * normalVector + v2vert;
}