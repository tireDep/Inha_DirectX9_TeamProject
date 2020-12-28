#include "stdafx.h"


CSoundManager::CSoundManager()
{
	sfxPlaying = false;
}

CSoundManager::~CSoundManager()
{
	Stop();
	fmodSystem->close();
	sound = true;
}

// cant use
void CSoundManager::Destroy()
{
	delete fmodSystem;
}

//CSoundManager * CSoundManager::GetInstance()
//{
//	static CSoundManager instance;
//	return &instance;
//}

void CSoundManager::init()
{
	System_Create(&fmodSystem);
	fmodSystem->init(4, FMOD_INIT_NORMAL, NULL);

	AddMain("sounds/bgm/bgm.mp3", "bgm");

	AddSFX("sounds/appear.wav", "BombPut");
	AddSFX("sounds/die.wav", "Die");
	AddSFX("sounds/draw.wav", "Draw");
	AddSFX("sounds/explode.wav", "Boom");
	AddSFX("sounds/get.wav", "ItemGet");
	AddSFX("sounds/lay.wav", "Lay");
	AddSFX("sounds/lose.wav", "Lose");
	AddSFX("sounds/start.wav", "Start");
	AddSFX("sounds/win.wav", "Win");
	//winter
	AddBGM("sounds/winter/first.wav", "w_first");
	AddBGM("sounds/winter/middle.wav", "w_middle");
	AddBGM("sounds/winter/winter-fall.wav", "w_last");
	//fall
	AddBGM("sounds/fall/first.wav", "f_first");
	AddBGM("sounds/fall/middle.wav", "f_middle");
	AddBGM("sounds/fall/fall-sum.wav", "f_last");
	//Orb
	AddSFX("sounds/Orb/Orb.wav", "Orb");
	//button
	AddSFX("sounds/button/button.wav", "button");

}

void CSoundManager::AddBGM(string path, string bgmName)
{
	fmodSystem->createStream(path.c_str(), FMOD_LOOP_NORMAL, NULL, &bgmHash[bgmName]);
}

void CSoundManager::AddMain(string path, string bgmName)
{
	fmodSystem->createStream(path.c_str(), FMOD_LOOP_NORMAL, NULL, &mainHash[bgmName]);
}


void CSoundManager::AddSFX(string path, string soundName)
{
	fmodSystem->createSound(path.c_str(), FMOD_DEFAULT, NULL, &soundHash[soundName]);
}

void CSoundManager::PlayBGM(string bgmName)
{
	if(bgmHash[bgmName] != NULL)
	fmodSystem->playSound(FMOD_CHANNEL_REUSE, bgmHash[bgmName], false, &bgmChannel);
}

void CSoundManager::PlayMain(string bgmName)
{
	if (mainHash[bgmName] != NULL)
		fmodSystem->playSound(FMOD_CHANNEL_REUSE, mainHash[bgmName], false, &mainChannel);
}

void CSoundManager::PlaySFX(string soundName)
{
	if (soundHash[soundName] != NULL)
		fmodSystem->playSound(FMOD_CHANNEL_FREE, soundHash[soundName], false, &sfxChannel);
}

bool CSoundManager::isPlaying()
{
	bool playing = false;
	bgmChannel->isPlaying(&playing);

	return playing;
}

bool CSoundManager::MainPlaying()
{
	bool Main = false;
	mainChannel->isPlaying(&Main);

	return Main;
}

void CSoundManager::Stop()
{
	sfxChannel->stop();
	bgmChannel->stop();
}

void CSoundManager::Stopmain()
{
	mainChannel->stop();
}
