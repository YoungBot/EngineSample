//==========================================================
//Atlas2D.hpp
//==========================================================
#pragma once
#ifndef _ATLAS2D_HPP_
#define _ATLAS2D_HPP_

class Atlas2DImplementation;

class Atlas2D
{
public:
	Atlas2D();
	~Atlas2D();
	Atlas2DImplementation* GetImplementation(){ return m_implementation; }

protected:
	Atlas2DImplementation* m_implementation;

};

#endif

