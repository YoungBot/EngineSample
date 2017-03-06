//==========================================================
//Skeleton2D.hpp
//==========================================================

#pragma once
#ifndef _SKELETON2D_HPP_
#define _SKELETON2D_HPP_
#include "Engine/Math/Matrix4x4.hpp"
#include "Engine/Math/AABB2D.hpp"
#include "Engine/Math/Vector2.hpp"
#include "Engine/Animation2D/Skeleton2DLoader.hpp"
#include <string>
#include <vector>
class Skeleton2DImplementation;
class Skeleton2DAnimation;
class Skeleton2DData;
class OpenGLRenderer;
struct SkeletonRenderer;
class Skeleton2D
{
public:
	Skeleton2D(Skeleton2DData* skeletonData);
	~Skeleton2D();
	Skeleton2DImplementation* GetImplementation(){ return m_implementation; }
	void Update(float deltaSecond);
	void UpdateAnimations(float deltaSecond);
	void DebugDrawSkeletonBone(OpenGLRenderer* renderer);
	void DebugDrawRectSlot(OpenGLRenderer* renderer);
	void ResetAnimations();
	void DrawSlot(const Matrix4x4& transformMatrix);
	void PlayAnimation(const std::string& animationName, bool isBaseAnimation, bool isLooping = true, float blendingchangingDuration = 0.5f, float changeScale = 0.5f, float expectBlending = 1.0f, float startBlending = 0.0f);
	void SetScaleSize(float scale);
	void SetPosition(const Vector2& newPosition);
	void SetBonePositionByName(const Vector2& newPosition, const std::string& boneName);
	void DeleteCompletedAnimation();
	void FlipSkeletonX(bool isFlip);
	void FlipSkeletonY(bool isFlip);
	const Vector2& GetPosition();
	void SetBoneRotation(const std::string& targetBoneName, float rotationDegree);
	void UpdateBoneRotation();
	Vector2 GetBonePositionByName(const std::string& boneName);
	Vector2 GetSlotPositionByName(const std::string& slotName);
	AABB2D GetSkeletonBox();
protected:
	void ProcessUpdatedAnimations();
	Skeleton2DImplementation* m_implementation;
	std::vector<Skeleton2DAnimation*> m_activeAnimations;
	Skeleton2DData* m_skeletonData;
};

#endif

