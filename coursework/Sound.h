#pragma once
#include <SDL_mixer.h>
#include <SDL.h>
#include <iostream>
#include <vector>
#include <SDL_main.h>

using namespace std;

class Sound
{
public:
	Sound();
	~Sound();
	bool isActive = true;
	void addSoundEffect(const char* path);
	void playSoundEffect(const int which) const;
private:
	int audioRate = 22050;
	int audioChannels = 2;
	int audioBuffers = 4096;
	Uint16 audioFormat = AUDIO_S16SYS;
	vector<Mix_Chunk*> soundEffects;
};

