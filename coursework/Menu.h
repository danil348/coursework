#pragma once
#include <SDL.h>

struct Item
{
	SDL_Texture* texture;
	SDL_Texture* activeTexture;
};


class Menu
{
public:
	bool isRunning = true;

	const int keyDelay = 150;
	int timeOfLastKey = 0;
	int timeOfCurrentKey = 0;

	int activeMenu = 0;
	int typeMenu = 0;
	
	int mainMenuCount = 3;
	int settingsMenuCount = 2;
	Item* fisrtItems = new Item[mainMenuCount];
	Item* settingsItems = new Item[settingsMenuCount];
	SDL_Texture* soundOff;
	SDL_Texture* soundOn;

	SDL_Texture* fullscreen;
	SDL_Texture* screen1;
	SDL_Texture* screen2;
	SDL_Texture* screen3;

	SDL_Rect _src;
	SDL_Rect _dest;
private:
};

