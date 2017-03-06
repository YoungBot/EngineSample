//==========================================================
//AABB3D.cpp
//==========================================================
#include "AABB3D.hpp"

const AABB3D AABB3D::ZERO_TO_ONE(Vector3(0.0f,0.0f,0.0f),Vector3(1.0f,1.0f,1.0f));

AABB3D::AABB3D()
{

}

AABB3D::~AABB3D()
{

}
///------------------------------------------------------
///
///------------------------------------------------------

AABB3D::AABB3D(const AABB3D& copy )
{
	mins = copy.mins;
	maxs = copy.maxs;
}
///------------------------------------------------------
///
///------------------------------------------------------

AABB3D::AABB3D( float initialX, float initialY, float initialZ )
{
	if(initialX <= 0)
	{
		mins.x = initialX;
		maxs.x = 0;		
	}
	else
	{
		mins.x = 0;
		maxs.x = initialX;
	}
	if(initialY <= 0)
	{
		mins.y = initialY;
		maxs.y = 0;
	}
	else
	{
		mins.y = 0;
		maxs.y = initialY;
	}
	if(initialZ <= 0)
	{
		mins.z = initialZ;
		maxs.z = 0;
	}
	else
	{
		mins.z = 0;
		maxs.z = initialZ;
	}
}
///------------------------------------------------------
///
///------------------------------------------------------

AABB3D::AABB3D( float minX, float minY, float minZ, float maxX, float maxY, float maxZ )
{
	mins.x = minX;
	mins.y = minY;
	mins.z = minZ;
	maxs.x = maxX;
	maxs.y = maxY;
	maxs.z = maxZ;
	//what should we do if the input is not correct
	//e.g. mins>maxs
}
///------------------------------------------------------
///
///------------------------------------------------------

AABB3D::AABB3D( const Vector3& center, float radiusX, float radiusY, float radiusZ )
{
	mins.x = center.x - radiusX;
	mins.y = center.y - radiusY;
	mins.z = center.z - radiusZ;
	maxs.x = center.x + radiusX;
	maxs.y = center.y + radiusY;
	maxs.z = center.z + radiusZ;
}
///------------------------------------------------------
///
///------------------------------------------------------

AABB3D::AABB3D( const Vector3& Mins, const Vector3& Maxs )
{
	mins = Mins;
	maxs = Maxs;
}

///------------------------------------------------------
///Mutators:
///------------------------------------------------------

void AABB3D::StretchToIncludePoint( const Vector3& point)
{
	if(mins.x > point.x )
	{
		mins.x = point.x;
	}
	if(maxs.x < point.x)
	{
		maxs.x = point.x;
	}
	if(mins.y > point.y)
	{
		mins.y = point.y;
	}
	if (maxs.y <point.y)
	{
		maxs.y = point.y;
	}
	if(mins.z > point.z)
	{
		mins.z = point.z;
	}
	if (maxs.z <point.z)
	{
		maxs.z = point.z;
	}
}


///------------------------------------------------------
///Accessors / queries:
///------------------------------------------------------
bool AABB3D::IsPointInside( const Vector3& point ) const
{
	if (  mins.x >= point.x 
		||mins.y >= point.y
		||mins.z >= point.z
		||maxs.x <= point.x
		||maxs.y <= point.y
		||maxs.z <= point.z)
	{
		return false;
	}
	else
		return true;
}


