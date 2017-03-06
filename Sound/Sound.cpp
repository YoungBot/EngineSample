//==========================================================
//Sound.cpp
//==========================================================

#include "Sound.hpp"
#include "ck/sound.h"



struct SoundImpl
{
	CkSound*   m_sound;
};

Sound::Sound(const std::string& soundPath)
	:m_soundImpl(NULL)
	,m_isValid(false)
	,m_doesNeedReset(false)
{
	//CkSound::newStreamSound(soundPath.c_str(),kCkPathType_FileSystem);
	m_soundImpl = new SoundImpl();
	m_soundImpl->m_sound = nullptr;// = CkSound::newStreamSound(soundPath.c_str(), kCkPathType_FileSystem);
	if(m_soundImpl->m_sound)
		m_isValid = true;
	soundPath;
}
Sound::~Sound()
{

}

bool Sound::Play(int loopCount,float volumeLevel)
{
	if(m_soundImpl && m_soundImpl->m_sound)
	{
		m_doesNeedReset = true;
		m_soundImpl->m_sound->setLoopCount(loopCount);
		m_soundImpl->m_sound->setVolume(volumeLevel);
		m_soundImpl->m_sound->play();
		return true;
	}
	return false;
}

bool Sound::IsValid()const 
{
	return m_isValid;
}

bool Sound::IsPlaying()
{
	if(m_soundImpl && m_soundImpl->m_sound)
		return m_soundImpl->m_sound->isPlaying();
	return false;
}

bool Sound::IsReady()
{
	if(m_soundImpl && m_soundImpl->m_sound)
		return m_soundImpl->m_sound->isReady();
	return false;
}

bool Sound::NeedsReset()
{
	return m_doesNeedReset;
}

void Sound::Reset()
{
	m_soundImpl->m_sound->stop();
	m_soundImpl->m_sound->setPlayPosition(NULL);
	m_doesNeedReset = false;
}