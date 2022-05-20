#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <Windows.h>
#include "DataStorage.h"
#include "Map.h"
#include "Menu.h"
#include "Sound.h"

using namespace std;
class Game
{
public:
	void init(const char* title, int xpos, int ypos, bool fullscrean);

	void handleEvents();
	void update();
	void menuRender();
	void gameRender();
	void clean();
	bool running();

	void playEnd();

	SDL_Event event;
	DataStorage dataStorage;
	Sound sound;
	int w, h;
private:
	const int endDelay = 2000;
	int timeOfLastend = 0;
	int timeOfCurrentend = 0;
	bool endplay = false;
	bool needPlayEnd = false;
	bool isRunning = false;
	const Uint8* keyArray = SDL_GetKeyboardState(NULL);
	SDL_Window* window;
};

