//==========================================================
//Sound.hpp
//==========================================================
#pragma once

#ifndef _SOUND_HPP_
#define _SOUND_HPP_
#include <vector>
#include <string>
#include <map>



typedef int SoundID;


struct SoundImpl;

class Sound
{
public:
	Sound(const std::string& soundPath);
	~Sound();
	bool IsValid()const;
	bool Play(int loopCount,float volumeLevel);
	bool IsPlaying();
	bool IsReady();
	bool NeedsReset();
	void Reset();
	
private:
	bool m_isValid;
	SoundImpl*   m_soundImpl;
	bool m_doesNeedReset;
};
typedef std::vector<Sound*> Sounds;

#endif