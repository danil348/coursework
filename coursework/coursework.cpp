#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "Game.h"

Game* game = nullptr;

int main(int argc, char** argv)
{
	setlocale(LC_ALL, "RU");

	const int FPS = 300;
	const int frameDelay = 1000 / FPS;
	Uint32 frameStart;
	int frameTime;

    game = new Game();
    game->init("dota 2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, true);

	while (game->running())
	{
		frameStart = SDL_GetTicks();
		game->habdleEvents();
		game->update();
		game->render();
		frameTime = SDL_GetTicks() - frameStart;
		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}
	}

	game->clean();

    return 0;
}