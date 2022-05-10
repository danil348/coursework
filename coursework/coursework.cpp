#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "Game.h"
#include <time.h>

Game* game = nullptr;

int main(int argc, char** argv)
{
	setlocale(LC_ALL, "RU");
	srand(time(0));

	const int FPS = 180;
	const int frameDelay = 1000 / FPS;
	int frameStart;
	int frameTime;

    game = new Game();
    game->init("dota 2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, true);

	while (game->running())
	{
		frameStart = clock();

		game->handleEvents();
		game->menuRender();
		game->gameRender();
		
		frameTime = clock() - frameStart;
		while (frameTime < frameDelay)
		{
			frameTime = clock() - frameStart;
		}
	}

	game->clean();

    return 0;
}