//================================================================================================================================
// Texture.hpp
//================================================================================================================================


#pragma once
#ifndef __included_Texture__
#define __included_Texture__

#include "Engine/Math/Vector2.hpp"
#include <string>
#include <map>
#include "Engine/Math/IntVector2.hpp"

class Texture ;
typedef std::map< std::string, Texture* >	TextureMap ;

//================================================================================================================================
//
//================================================================================================================================
class Texture
{
public:
	virtual ~Texture();
//protected:
	///-----------------------------------------------------------------------------------
	///
	///-----------------------------------------------------------------------------------
	Texture( const std::string& pathName );
	Texture(const std::string& name, unsigned char* pixelData, Vector2 textureSize, int numOfComponents);
	///-----------------------------------------------------------------------------------
	///
	///-----------------------------------------------------------------------------------
	const std::string&		GetName() const															{ return m_pathName ; }
	unsigned int			GetPlatformHandle() const												{ return m_platformHandle ; }

	///-----------------------------------------------------------------------------------
	///
	///-----------------------------------------------------------------------------------
//protected:
	static Texture*	CreateOrGetTexture( const std::string& texturePath );
	static Texture* CreateMissingTexture(const std::string& name, unsigned char* pixelData, Vector2 textureSize, int numOfComponents);
protected:
	std::string				m_pathName ;
	Vector2					m_size ;
	unsigned int			m_platformHandle ;

	static TextureMap		s_globalTextures ;
	
};

#endif // __included_Texture__


