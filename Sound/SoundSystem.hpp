//==========================================================
//SoundSystem.hpp
//==========================================================
#pragma once

#ifndef _SOUNDSYSTEM_HPP_
#define _SOUNDSYSTEM_HPP_

#include <string>
#include <map>
#include <vector>
#include "Sound.hpp"
#include <direct.h>

typedef std::map<SoundID,Sounds> SoundMap;

class SoundSystem
{
public:
	SoundSystem();
	~SoundSystem();

	void Startup();
	void Update();
	void ShutDown();
	SoundID LoadStreamingSound(const std::string& soundPath,unsigned int maxNumberOfCopies);
	Sound* PlayStreamingSound(SoundID soundID, int loopCount, float volumeLevel);
	int m_nextSoundID;
private:
	std::string m_workingDirectory;
	SoundMap m_soundMap;
};

extern SoundSystem* s_theSoundSystem;


#endif