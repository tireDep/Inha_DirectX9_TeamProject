#include "stdafx.h"
 
#include "SoundManager.h"

CSoundManager::CSoundManager()
{
}

CSoundManager::~CSoundManager()
{
	Stop();
	fmodSystem->close();
}

// cant use
void CSoundManager::Destroy()
{
	delete fmodSystem;
}

void CSoundManager::init()
{
	System_Create(&fmodSystem);
	fmodSystem->init(4, FMOD_INIT_NORMAL, NULL);
	
	AddSFX("sounds/appear.wav", "BombPut");
	AddSFX("sounds/die.wav", "Die");
	AddSFX("sounds/draw.wav", "Draw");
	AddSFX("sounds/explode.wav", "Boom");
	AddSFX("sounds/get.wav", "ItemGet");
	AddSFX("sounds/lay.wav", "Lay");
	AddSFX("sounds/lose.wav", "Lose");
	AddSFX("sounds/start.wav", "Start");
	AddSFX("sounds/win.wav", "Win");
}

void CSoundManager::AddBGM(string path)
{
	//fmodSystem->createSound(path.c_str(), FMOD_LOOP_NORMAL, NULL, &bgm);
	fmodSystem->createStream(path.c_str(), FMOD_LOOP_NORMAL, NULL, &bgm);
}

void CSoundManager::AddSFX(string path, string soundName)
{
	fmodSystem->createSound(path.c_str(), FMOD_DEFAULT, NULL, &soundHash[soundName]);
}

void CSoundManager::PlayBGM()
{
	fmodSystem->playSound(FMOD_CHANNEL_REUSE, bgm, false, &bgmChannel);
}

void CSoundManager::PlaySFX(string soundName)
{
	if (soundHash[soundName] != NULL)
		fmodSystem->playSound(FMOD_CHANNEL_FREE, soundHash[soundName], false, &sfxChannel);
}

void CSoundManager::Stop()
{
	sfxChannel->stop();
	bgmChannel->stop();
}