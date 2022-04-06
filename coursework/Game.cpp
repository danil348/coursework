#include "Game.h"

Map* map;

void Game::init(const char* title, int xpos, int ypos, bool fullscrean)
{

	int flag = 0;
	if (fullscrean) {
		flag = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		isRunning = false;
		printf("SDL Error: %S", SDL_GetError());
	}
	else if (IMG_Init(IMG_INIT_PNG) == 0) {
		printf("IMG Error: %S", SDL_GetError());
	}
	else {
		printf("Initialised!\n");
		window = SDL_CreateWindow(title, xpos, ypos, SDL_WINDOW_FULLSCREEN_DESKTOP, SDL_WINDOW_FULLSCREEN_DESKTOP, flag);
		if (window) {
			printf("Window created!\n");
		}
		SDL_SetWindowFullscreen(window, 1);
		map->textureManager.renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		if (map->textureManager.renderer) {
			SDL_SetRenderDrawColor(map->textureManager.renderer, 255, 255, 255, 255);
			printf("Renderer created!\n");
		}

		isRunning = true;
	}
	map = new Map();
	event.key.keysym.scancode = SDL_SCANCODE_0;
	event.type = NULL;

	int w, h;
	SDL_GetRendererOutputSize(map->textureManager.renderer, &w, &h);
	map->SetSize(w, h);
}


void Game::habdleEvents()
{
	SDL_PollEvent(&event);

	if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE ||
		event.key.keysym.scancode == SDL_SCANCODE_RETURN ||
		event.type == SDL_QUIT) {
		isRunning = false;
	}
	else {
		if (keyboard_state_array[SDL_SCANCODE_UP] && !(keyboard_state_array[SDL_SCANCODE_DOWN]))
		{
			map->UpdateMapY(map->playerSpeed);
		}
		else if (!keyboard_state_array[SDL_SCANCODE_UP] && keyboard_state_array[SDL_SCANCODE_DOWN])
		{
			map->UpdateMapY(-map->playerSpeed);
		}

		if (keyboard_state_array[SDL_SCANCODE_RIGHT] && !keyboard_state_array[SDL_SCANCODE_LEFT])
		{
			map->UpdateMapX(-map->playerSpeed);
		}
		else if (!keyboard_state_array[SDL_SCANCODE_RIGHT] && keyboard_state_array[SDL_SCANCODE_LEFT])
		{
			map->UpdateMapX(map->playerSpeed);
		}
	}

	map->changingKeyState(keyboard_state_array);
}

void Game::update()
{

}

void Game::render()
{
	SDL_SetRenderDrawColor(map->textureManager.renderer, 27, 28, 50, 0);
	SDL_RenderClear(map->textureManager.renderer);
	map->DrawMap(window);
	SDL_RenderPresent(map->textureManager.renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(map->textureManager.renderer);
	TTF_Quit();
	SDL_Quit();

	printf("game cleaned\n");
}

bool Game::running()
{
	return isRunning;
}