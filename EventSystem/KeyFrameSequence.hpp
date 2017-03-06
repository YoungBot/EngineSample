//==========================================================
//KeyFrameSequence.hpp
//==========================================================

#pragma once
#ifndef _KEYFRAMESEQUENCE_HPP_
#define _KEYFRAMESEQUENCE_HPP_

#include <vector>
#include "Engine/Math/MathUtils.hpp"
#include "Engine/Math/Math2D.hpp"
template<typename T>
class KeyFrame
{
public:
	T m_valueAtParametric;
	float m_parametric;

};

enum WrapBehavior
{
	WRAP_BEHAVIOR_LOOP,
	WRAP_BEHAVIOR_CLAMP,
	WRAP_BEHAVIOR_PINGPONG,
	NUM_BEHAVIORS
};
template <typename T>
class KeyFrameSequence
{
public:
	KeyFrameSequence() { m_warpBehavior = WRAP_BEHAVIOR_LOOP; }
	WrapBehavior m_warpBehavior;
	std::vector<KeyFrame<T>> m_keyFrames;
	void AddKeyFrame(KeyFrame<T> keyFrame);
	T GetValueAtParametric(float parametric);


private:

};

template <typename T>
inline void KeyFrameSequence<T>::AddKeyFrame(KeyFrame<T> keyFrame)
{
	//some logic
	m_keyFrames.push_back(keyFrame);
}

template <typename T>
inline T KeyFrameSequence<T>::GetValueAtParametric(float parametric)
{
	if (m_keyFrames.size() == 0)
	{
		//ASSERT();
	}
	if (m_keyFrames.size() == 1)
		return m_keyFrames[0].m_valueAtParametric;
	KeyFrame<T> previousKey;
	KeyFrame<T> nextKey;
	// set parametric by type
	switch (m_warpBehavior)
	{
	case WRAP_BEHAVIOR_LOOP:
		if (parametric<=0.0f)
		{
			while (parametric<=0.0f)
			{
				parametric += 1.0f;
			}
			break;
		}
		if (parametric>=1.0f)
		{
			while (parametric >= 1.0f)
			{
				parametric -= 1.0f;
			}
			break;
		}
		break;
	case WRAP_BEHAVIOR_CLAMP:
		if (parametric < 0.0f)
		{
			parametric = 0.0f;
		}
		if (parametric > 1.0f)
		{
			parametric = 1.0f;
		}
		break;
	case WRAP_BEHAVIOR_PINGPONG:
		if (parametric < 0.0f || parametric >1.0f)
		{
			int value = MathUtils::RoundUpToInt(parametric);
			parametric = value - parametric;
		}
		break;
	default:
		break;
	}
	// check if parametric greater than the last one
	KeyFrame<T> lastKeyframe = m_keyFrames[m_keyFrames.size() - 1];
	if (parametric >= lastKeyframe.m_parametric)
		return lastKeyframe.m_valueAtParametric;
	//get the previous and the next keyFrame
	for (unsigned int index = 0; index < m_keyFrames.size()-1; ++index)
	{
		if (m_keyFrames[index].m_parametric <= parametric && m_keyFrames[index +1].m_parametric > parametric)
		{
			previousKey = m_keyFrames[index];
			nextKey = m_keyFrames[index + 1];
		}
	}
	float fractionComplete = (parametric - previousKey.m_parametric) / (nextKey.m_parametric - previousKey.m_parametric);
	return Math2D::Interpolate(previousKey.m_valueAtParametric, nextKey.m_valueAtParametric, fractionComplete);
}

#endif