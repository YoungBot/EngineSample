//==========================================================
//Math2D.cpp
//==========================================================
#include "Engine/Math/Math2D.hpp"

bool Math2D::DoDiscsOverlap( const Disc2D& first, const Disc2D& second )
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

bool Math2D::DoShapesOverlap( const AABB2D& box, const Disc2D& disc )
{	
	if(disc.center.x+disc.radius< box.mins.x)
	{
		return false;
	}
	if(disc.center.x-disc.radius> box.maxs.x)
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
	if((CalcDistanceSquared(box.mins,disc.center)>disc.radius*disc.radius)
		&&(CalcDistanceSquared(box.maxs,disc.center)>disc.radius*disc.radius) 
		&&(CalcDistanceSquared(Vector2(box.mins.x,box.maxs.y),disc.center)>disc.radius*disc.radius)
		&&(CalcDistanceSquared(Vector2(box.maxs.x,box.mins.y),disc.center)>disc.radius*disc.radius))
	{
		return false;
	}
	
	return true;
}
bool Math2D::DoShapesOverlap( const Disc2D& disc, const AABB2D& box )
{

	if(disc.center.x+disc.radius< box.mins.x)
	{
		return false;
	}
	if(disc.center.x-disc.radius> box.maxs.x)
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
	if((CalcDistanceSquared(box.mins,disc.center)<disc.radius*disc.radius)
		||(CalcDistanceSquared(box.maxs,disc.center)<disc.radius*disc.radius) 
		||(CalcDistanceSquared(Vector2(box.mins.x,box.maxs.y),disc.center)<disc.radius*disc.radius)
		||(CalcDistanceSquared(Vector2(box.maxs.x,box.mins.y),disc.center)<disc.radius*disc.radius))
	{
		return true;
	}
	else 
		return false;
}

///------------------------------------------------------
///
///------------------------------------------------------
bool Math2D::DoAABBsOverlap( const AABB2D& first, const AABB2D& second )
{
	if(	first.mins.x >second.maxs.x ||
		first.mins.y > second.maxs.y||
		first.maxs.x < second.mins.x||
		first.maxs.y < second.mins.y)
	{
		return false;
	}
	else
		return true;
}