#pragma once
#include <SDL.h>

struct Item
{
	SDL_Texture* texture;
	SDL_Texture* activeTexture;
};


struct GameSettings
{
	bool sound = true;
	int row = 4;
	int col = 3;
	int activeItem = 0;
	int itemCount = 4;
	int screen[4][3] = {
		{1920, 1080, 1},
		{1680, 1050, 0},
		{1280, 1024, 0},
		{1, 1, 0},
	};
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


	GameSettings gameSettings;
	SDL_Rect _src;
	SDL_Rect _dest;
private:
};

