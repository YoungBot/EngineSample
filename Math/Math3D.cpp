//==========================================================
//Math3D.cpp
//==========================================================
#include "Engine/Math/Math3D.hpp"

bool Math3D::DoDiscsOverlap( const Disc3D& first, const Disc3D& second )
{
	float distanceSquared = CalcDistanceSquared(first.center,second.center);
	if( distanceSquared > (first.radius +second.radius) * (first.radius +second.radius))
	{
		return false;
	}
	else
		return true;
}
///------------------------------------------------------
///
///------------------------------------------------------

bool Math3D::DoShapesOverlap( const AABB3D& box, const Disc3D& disc )
{	
	if(disc.center.x+disc.radius< box.mins.x)
	{
		return false;
	}
	if(disc.center.x-disc.radius> box.maxs.x)
	{
		return false;
	}
	if(disc.center.z-disc.radius> box.maxs.z)
	{
		return false;
	}
	if(disc.center.y+disc.radius< box.mins.y)
	{
		return false;
	}
	if(disc.center.y-disc.radius> box.maxs.y)
	{
		return false;
	}
	if(disc.center.z-disc.radius> box.maxs.z)
	{
		return false;
	}
	if(
		(CalcDistanceSquared(Vector3(box.mins.x,box.mins.y,box.mins.z),disc.center)>disc.radius*disc.radius)
		&&(CalcDistanceSquared(Vector3(box.mins.x,box.mins.y,box.maxs.z),disc.center)>disc.radius*disc.radius)
		&&(CalcDistanceSquared(Vector3(box.mins.x,box.maxs.y,box.mins.z),disc.center)>disc.radius*disc.radius)
		&&(CalcDistanceSquared(Vector3(box.mins.x,box.maxs.y,box.maxs.z),disc.center)>disc.radius*disc.radius)
		&&(CalcDistanceSquared(Vector3(box.maxs.x,box.mins.y,box.mins.z),disc.center)>disc.radius*disc.radius)
		&&(CalcDistanceSquared(Vector3(box.maxs.x,box.mins.y,box.maxs.z),disc.center)>disc.radius*disc.radius)
		&&(CalcDistanceSquared(Vector3(box.maxs.x,box.maxs.y,box.mins.z),disc.center)>disc.radius*disc.radius)
		&&(CalcDistanceSquared(Vector3(box.maxs.x,box.maxs.y,box.maxs.z),disc.center)>disc.radius*disc.radius))
	{
		return false;
	}
	
	return true;
}
bool Math3D::DoShapesOverlap( const Disc3D& disc, const AABB3D& box )
{

	if(disc.center.x+disc.radius< box.mins.x)
	{
		return false;
	}
	if(disc.center.x-disc.radius> box.maxs.x)
	{
		return false;
	}
	if(disc.center.z-disc.radius> box.maxs.z)
	{
		return false;
	}
	if(disc.center.y+disc.radius< box.mins.y)
	{
		return false;
	}
	if(disc.center.y-disc.radius> box.maxs.y)
	{
		return false;
	}
	if(disc.center.z-disc.radius> box.maxs.z)
	{
		return false;
	}
	if(
		(CalcDistanceSquared(Vector3(box.mins.x,box.mins.y,box.mins.z),disc.center)>disc.radius*disc.radius)
		&&(CalcDistanceSquared(Vector3(box.mins.x,box.mins.y,box.maxs.z),disc.center)>disc.radius*disc.radius)
		&&(CalcDistanceSquared(Vector3(box.mins.x,box.maxs.y,box.mins.z),disc.center)>disc.radius*disc.radius)
		&&(CalcDistanceSquared(Vector3(box.mins.x,box.maxs.y,box.maxs.z),disc.center)>disc.radius*disc.radius)
		&&(CalcDistanceSquared(Vector3(box.maxs.x,box.mins.y,box.mins.z),disc.center)>disc.radius*disc.radius)
		&&(CalcDistanceSquared(Vector3(box.maxs.x,box.mins.y,box.maxs.z),disc.center)>disc.radius*disc.radius)
		&&(CalcDistanceSquared(Vector3(box.maxs.x,box.maxs.y,box.mins.z),disc.center)>disc.radius*disc.radius)
		&&(CalcDistanceSquared(Vector3(box.maxs.x,box.maxs.y,box.maxs.z),disc.center)>disc.radius*disc.radius))
	{
		return false;
	}
		return false;
}

///------------------------------------------------------
///
///------------------------------------------------------
bool Math3D::DoAABBsOverlap( const AABB3D& first, const AABB3D& second )
{
	if(	first.mins.x >second.maxs.x ||
		first.mins.y > second.maxs.y||
		first.mins.z > second.maxs.z||
		first.maxs.x < second.mins.x||
		first.maxs.y < second.mins.y||
		first.maxs.z < second.mins.z)
	{
		return false;
	}
	else
		return true;
}