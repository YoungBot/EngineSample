//==========================================================
//Atlas2D.cpp
//==========================================================
#include "Atlas2D.hpp"
#include <spine/Atlas.h>
class Atlas2DImplementation
{
public:
	Atlas2DImplementation();

	spAtlas* GetSkeletonData(){ return m_data; };

protected:
	spAtlas* m_data;
};

Atlas2DImplementation::Atlas2DImplementation()
{

}
///----------------------------------------------------------
///
///----------------------------------------------------------

Atlas2D::Atlas2D()
{

}
///----------------------------------------------------------
///
///----------------------------------------------------------

Atlas2D::~Atlas2D()
{

}
///----------------------------------------------------------
///
///----------------------------------------------------------