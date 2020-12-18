#pragma once

#define	g_pSoundManager	CSoundManager::GetInstance()

#include "fmod.hpp"


#define SOUND_MAX 1.0f
#define SOUND_MIN 0.0f
#define SOUND_DEFAULT 0.5f
#define SOUND_WEIGHT 0.1f

using namespace FMOD;

class CSoundManager
{
private:
	SingleTone(CSoundManager);
private:
	System * fmodSystem;

	Channel* bgmChannel;
	Channel* sfxChannel;

	Sound* bgm;
	map<string, Sound*> soundHash;
	map<string, Sound*> bgmHash;

public:
	//CSoundManager();
	//virtual ~CSoundManager() { }

	void init();
	void AddSFX(string path, string musicName);
	void AddBGM(string path, string bgmName);

	void PlaySFX(string soundName);
	void PlayBGM(string bgmName);

	void Stop();

	void Destroy();
};
