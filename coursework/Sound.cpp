#include "Sound.h"

Sound::Sound()
{
	SDL_Init(SDL_INIT_AUDIO);

	Mix_OpenAudio(audioRate, audioFormat, audioChannels, audioBuffers);
}

Sound::~Sound()
{
	SDL_Quit();
}

void Sound::addSoundEffect(const char* path)
{
	Mix_Chunk* tmpChunk = Mix_LoadWAV(path);

	if (tmpChunk != nullptr) {
		soundEffects.push_back(tmpChunk);
	}
	else {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't init audio: %s", Mix_GetError());
	}
}


void Sound::playSoundEffect(const int which) const
{
	if (isActive == true) {
		Mix_PlayChannel(-1, soundEffects[which], 0);
	}
}
