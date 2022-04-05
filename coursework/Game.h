#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "Map.h"
#include "variables.cpp"

using namespace std;
class Game
{
public:
	void init(const char* title, int xpos, int ypos, bool fullscrean);

	void habdleEvents();
	void update();
	void render();
	void clean();
	bool running();
	bool NeedUpdate();
	SDL_Event event;
private:
	int count = 0;
	bool isRunning = false;
	bool needUpdate = true;
	float speed = 1.7f;
	const Uint8* keyboard_state_array = SDL_GetKeyboardState(NULL);
	SDL_Window* window;
};

