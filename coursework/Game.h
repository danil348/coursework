#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <Windows.h>
#include "DataStorage.h"
#include "Map.h"
#include "Menu.h" 

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
	SDL_Event event;
	DataStorage dataStorage;
	int w, h;
private:
	bool isRunning = false;
	const Uint8* keyboard_state_array = SDL_GetKeyboardState(NULL);
	SDL_Window* window;
};

