//==========================================================
//RBGA.hpp
//==========================================================
#pragma once

#ifndef _RGBA_HPP_
#define _RGBA_HPP_

class RGBA
{
public:
	RGBA();
	explicit RGBA(float,float,float,float);
	explicit RGBA(float,float,float);
	explicit RGBA(unsigned char,unsigned char,unsigned char,unsigned char);
	explicit RGBA(int,int,int,int);
	~RGBA();
	bool operator != (const RGBA& rgbaToNotEqual) const;
///------------------------------------------------------
///
///------------------------------------------------------
	inline const float GetRed();
	inline const float GetGreen();
	inline const float GetBlue();
	inline const float GetAlpha();

///------------------------------------------------------
///
///------------------------------------------------------	
	unsigned char R;	
	unsigned char G;
	unsigned char B;
	unsigned char A;

	static const RGBA BLACK;
	static const RGBA WHITE;
};
const float RGBA::GetRed()
{
	return R/255.0f;
}
const float RGBA::GetGreen()
{
	return G/255.0f;
}
const float RGBA::GetBlue()
{
	return B/255.0f;
}
const float RGBA::GetAlpha()
{
	return A/255.0f;
}

inline	RGBA::RGBA()
{
}


#endif