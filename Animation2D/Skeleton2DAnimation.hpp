//==========================================================
//Skeleton2DAnimation.hpp
//==========================================================

#pragma once
#ifndef _SKELETON2DANIMATION_HPP_
#define _SKELETON2DANIMATION_HPP_

#include <string>
class Skeleton2DData;
struct spSkeleton;
class Skeleton2DAnimationImplementation;

class Skeleton2DAnimation
{
public:
	Skeleton2DAnimation(const std::string& animationName,Skeleton2DData* skeletonData,bool isBaseAnimation);
	Skeleton2DAnimation(const std::string& animationName, Skeleton2DData* skeletonData, bool isBase, bool isLoop);
	Skeleton2DAnimation(const std::string& animationName, Skeleton2DData* skeletonData, bool isBase, bool isLoop, 
						float blendingchangingDuration, float changeScale, float expectBlending, float startBlending);
	~Skeleton2DAnimation();
	Skeleton2DAnimationImplementation* GetImplementation(){ return m_implementation; }
	std::string GetName();
	void BaseUpdate(float deltaSecond, spSkeleton* skeleton);
	void MixUpdate(float deltaSecond, spSkeleton* skeleton);
	void SetExpectBlending(float expectBlending){ m_expectBlending = expectBlending; }
	void SetChangeScale(float changeScale){ m_changeScale = changeScale; }
	void SetStartBlending(float startBlending){ m_startBlending = startBlending; }
	bool IsFinishBlending();
	bool GetIsBaseAnimation(){ return m_isBaseAnimation; }
	bool GetIsLooping(){ return m_isLooping; }
	bool GetIsComplete();
protected:
	Skeleton2DAnimationImplementation* m_implementation;
	float m_lastTime;
	bool m_isBaseAnimation;
	bool m_isLooping;
	float m_blendingchangingDuration;
	float m_expectBlending;
	float m_changeScale;
	float m_startBlending;
};

#endif