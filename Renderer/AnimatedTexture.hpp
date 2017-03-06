//==========================================================
//AnimatedTexture.hpp
//==========================================================

#pragma once

#ifndef _ANIMATEDTEXTURE_HPP_ 
#define _ANIMATEDTEXTURE_HPP_

#include "Engine/Renderer/Texture.hpp"

class AnimatedTexture ;
typedef std::map< std::string, AnimatedTexture* >	AnimatedTextureMap ;

class  AnimatedTexture :public Texture
{
public:
	AnimatedTexture(const std::string& path
					,unsigned int numberOfSprites
					,int cellWidth
					,int cellHeight);
	~AnimatedTexture();
///------------------------------------------------------
///
///------------------------------------------------------
	static AnimatedTexture* CreateOrGetAnimatedTexture(	const std::string& path
														,unsigned int numberOfSprites
														,int cellWidth
														,int cellHeight);

	void CalcTextuleCoordinatesAtPresentComplete(	double percentComplete,
													Vector2& minCoordinates_out,
													Vector2& maxCoordinates_out);
protected:
	
private:
	int m_cellWidth;
	int m_cellHeight;
	unsigned int m_totalNumberOfSprites;
	static AnimatedTextureMap s_globalAnimatureTextures ;

};

#endif