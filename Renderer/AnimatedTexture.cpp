//==========================================================
//AnimatedTexture.cpp
//==========================================================
#include "AnimatedTexture.hpp"

AnimatedTextureMap AnimatedTexture::s_globalAnimatureTextures ;
AnimatedTexture::AnimatedTexture(const std::string& path ,unsigned int numberOfSprites ,int cellWidth ,int cellHeight)
	:Texture(path)
{
	m_cellHeight = cellHeight;
	m_cellWidth  = cellWidth;
	m_totalNumberOfSprites = numberOfSprites;
}
///------------------------------------------------------
///
///------------------------------------------------------
AnimatedTexture::~AnimatedTexture()
{

}
///------------------------------------------------------
///
///------------------------------------------------------
AnimatedTexture* AnimatedTexture::CreateOrGetAnimatedTexture(const std::string& path ,unsigned int numberOfSprites ,int cellWidth ,int cellHeight)
{
	AnimatedTextureMap::iterator AnimatedTextureIter = s_globalAnimatureTextures.find( path );
	if ( AnimatedTextureIter != s_globalAnimatureTextures.end() )
		return AnimatedTextureIter->second ;

	AnimatedTexture*	newAnimatedTexture			= new AnimatedTexture( path,numberOfSprites,cellWidth,cellHeight );
	s_globalAnimatureTextures[ path ]	= newAnimatedTexture ;
	return newAnimatedTexture ;
}
///------------------------------------------------------
///
///------------------------------------------------------
void AnimatedTexture::CalcTextuleCoordinatesAtPresentComplete(double percentComplete, Vector2& minCoordinates_out, Vector2& maxCoordinates_out)
{
	int tileNumber = (int)(percentComplete*m_totalNumberOfSprites);
	int tileColumn = tileNumber % m_cellWidth;
	int tileRow    = tileNumber / m_cellWidth;
	float XsizeOfTile = 1.0f/m_cellWidth;
	float YsizeOFTile = 1.0f/m_cellHeight;
	minCoordinates_out = Vector2((tileColumn)*XsizeOfTile
								,(tileRow+1)*YsizeOFTile);
	maxCoordinates_out = Vector2((tileColumn+1)*XsizeOfTile
									,tileRow*YsizeOFTile);
	
}