//==========================================================
//Skeleton2DAnimation.cpp
//==========================================================
#include "Skeleton2DAnimation.hpp"
#include "Skeleton2DData.hpp"
#include <spine/Animation.h>
#include <spine/Skeleton.h>

class Skeleton2DAnimationImplementation
{
public:
	Skeleton2DAnimationImplementation(const std::string& animationName,Skeleton2DData* skeletonData);
	spAnimation* GetAnimation(){ return m_animation; }
	std::string GetName(){ return m_animation->name; }
	float GetTotalTime(){ return m_animation->duration; }
	//void Update(float deltaSecond);
protected:
	spAnimation* m_animation;
};
///----------------------------------------------------------
///
///----------------------------------------------------------

Skeleton2DAnimationImplementation::Skeleton2DAnimationImplementation(const std::string& animationName, Skeleton2DData* skeletonData)
	:m_animation(nullptr)
{
	spSkeletonData* s = (spSkeletonData*)skeletonData->GetSkeleton2DData();
	m_animation = spSkeletonData_findAnimation(s, animationName.c_str());

}


//////////////////////////////////////////////////////////////////////////

///----------------------------------------------------------
///
///----------------------------------------------------------
Skeleton2DAnimation::Skeleton2DAnimation(const std::string& animationName, Skeleton2DData* skeletonData, bool isBase)
	:m_lastTime(0.0f)
	, m_isBaseAnimation(isBase)
	, m_blendingchangingDuration(0.5f)
	, m_changeScale(0.5f)
	, m_expectBlending(1.0f)
	, m_startBlending(0.0f)
	, m_isLooping(true)
{
	m_implementation = new Skeleton2DAnimationImplementation(animationName, skeletonData);
}
///----------------------------------------------------------
///
///----------------------------------------------------------
Skeleton2DAnimation::Skeleton2DAnimation(const std::string& animationName, Skeleton2DData* skeletonData, bool isBase,bool isLoop)
	:m_lastTime(0.0f)
	, m_isBaseAnimation(isBase)
	, m_blendingchangingDuration(0.5f)
	, m_changeScale(0.5f)
	, m_expectBlending(1.0f)
	, m_startBlending(0.0f)
	, m_isLooping(isLoop)
{
	m_implementation = new Skeleton2DAnimationImplementation(animationName, skeletonData);
}

Skeleton2DAnimation::Skeleton2DAnimation(const std::string& animationName, Skeleton2DData* skeletonData, bool isBase, bool isLoop, 
										float blendingchangingDuration = 0.5f, float changeScale= 0.5f, float expectBlending = 1.0f, float startBlending=0.0f)
	:m_lastTime(0.0f)
	, m_isBaseAnimation(isBase)
	, m_blendingchangingDuration(blendingchangingDuration)
	, m_changeScale(changeScale)
	, m_expectBlending(expectBlending)
	, m_startBlending(startBlending)
	, m_isLooping(isLoop)
{
	m_implementation = new Skeleton2DAnimationImplementation(animationName, skeletonData);
}

Skeleton2DAnimation::~Skeleton2DAnimation()
{

}
///----------------------------------------------------------
///
///----------------------------------------------------------

void Skeleton2DAnimation::BaseUpdate(float deltaSecond, spSkeleton* skeleton)
{
	spAnimation_apply(m_implementation->GetAnimation(), skeleton, deltaSecond, m_lastTime, m_isLooping, nullptr, nullptr);	
	m_lastTime += deltaSecond;
}
///----------------------------------------------------------
///
///----------------------------------------------------------

std::string Skeleton2DAnimation::GetName()
{
	return m_implementation->GetName();
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void Skeleton2DAnimation::MixUpdate(float deltaSecond, spSkeleton* skeleton)
{
	float alpha = m_lastTime / m_blendingchangingDuration;
	if (alpha<m_startBlending)
		alpha = m_startBlending;
	if (alpha>m_expectBlending)
		alpha = m_expectBlending;
	spAnimation_mix(m_implementation->GetAnimation(), skeleton, deltaSecond, m_lastTime, m_isLooping, nullptr, nullptr, alpha);	
	m_lastTime += deltaSecond;
}
///----------------------------------------------------------
///
///----------------------------------------------------------

bool Skeleton2DAnimation::IsFinishBlending()
{
	float alpha = m_lastTime / m_blendingchangingDuration;
	if (alpha >= m_expectBlending)
		return true;
	else
		return false;
	
}
///----------------------------------------------------------
///
///----------------------------------------------------------

bool Skeleton2DAnimation::GetIsComplete()
{
	float completePercent = m_lastTime / m_implementation->GetTotalTime();
	if (completePercent >= 1.0f)
		return true;
	else
		return false;
}
