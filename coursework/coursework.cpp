﻿#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "Game.h"
#include <time.h>

Game* game = nullptr;

int main(int argc, char** argv)
{
	setlocale(LC_ALL, "RU");

	const int FPS = 60;
	const int frameDelay = 1000 / FPS;
	Uint32 frameStart;
	int frameTime;

    game = new Game();
    game->init("dota 2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, true);


	clock_t start, end;

	while (game->running())
	{
		frameStart = clock();
		game->habdleEvents();
		game->update();
		frameTime = clock() - frameStart;
		if (frameDelay > frameTime) {

			game->render();
		}
	}

	game->clean();

    return 0;
}