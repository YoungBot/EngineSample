//==========================================================
//SoundSystem.cpp
//==========================================================
#include "SoundSystem.hpp"
#include "ck/ck.h"

SoundSystem* s_theSoundSystem = NULL;

SoundSystem::SoundSystem()
{
	if(!s_theSoundSystem)
		s_theSoundSystem = this;
}

SoundSystem::~SoundSystem()
{

}

void SoundSystem::Startup()
{
	m_nextSoundID = 1;
	m_workingDirectory = _getcwd(NULL,0);
	m_workingDirectory += "/";
	//static CkConfig  ckConfig;
	//CkInit(&ckConfig);
}

void SoundSystem::Update()
{
	//CkUpdate();
	
	for(SoundMap::iterator soundMapIter = m_soundMap.begin() ; soundMapIter != m_soundMap.end() ; ++soundMapIter)
	{	
		Sounds& soundInstance = soundMapIter -> second;
		for( Sounds::iterator soundIter = soundInstance.begin(); soundIter!=soundInstance.end(); ++soundIter)
		{
			Sound* sound = (*soundIter);
			if(sound && sound->NeedsReset() && !sound->IsPlaying())
				sound->Reset();
		}
	}
	
}

void SoundSystem::ShutDown()
{
	//CkShutdown();
	delete this;
}

SoundID SoundSystem::LoadStreamingSound(const std::string& soundPath,unsigned int maxNumberOfCopies)
{
	SoundID soundID = m_nextSoundID++;
	std::string fullPath = m_workingDirectory;
	fullPath += soundPath;
	
	size_t characterIndex = 0;
	while(characterIndex != std::string::npos)
	{
		characterIndex = fullPath.find_first_of('\\',characterIndex);
		if(characterIndex != std::string::npos)
			fullPath.replace(characterIndex,1,"/");
	}


	Sounds sounds;
	for (unsigned int i = 0; i<maxNumberOfCopies;i++)
	{
		Sound* newSound = new Sound(fullPath);
		if(newSound -> IsValid())
		{
			sounds.push_back(newSound);
		}
		else
		{
			soundID = -1;
			delete newSound;
			break;
		}
	}
	if(soundID != -1)
	{
		m_soundMap[soundID] = sounds;
	}

	return soundID;
}

Sound* SoundSystem::PlayStreamingSound(SoundID soundID, int loopCount, float volumeLevel)
{
	Sound*		soundPicked = NULL;

	SoundMap ::iterator soundIDIter = m_soundMap.find(soundID);
	if(soundIDIter!= m_soundMap.end())
	{
		//bool playedSound = false;
		Sounds& sounds = soundIDIter->second;
		for (Sounds::iterator soundIter = sounds.begin();soundIter != sounds.end();++soundIter)
		{
			Sound* sound = (*soundIter);
			if(sound->IsPlaying() &&sound->IsReady())
				continue;
			sound->Play(loopCount,volumeLevel);
		//	playedSound = true;
			soundPicked = sound;
			break;
		}
	/*
		if(soundPicked)
		{

		}
	*/
	}
	return soundPicked ; 
}
