#include "Game.h"

Map* map;

void Game::init(const char* title, int xpos, int ypos, int width, int heigth, bool fullscrean)
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
		window = SDL_CreateWindow(title, xpos, ypos, width, heigth, flag);
		if (window) {
			printf("Window created!\n");
		}

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

	/*player = TextureManager::LoadTexture("assets/player.png");
	src.x = src.y = 0;
	src.w = 1001;
	src.h = 1001;

	dest.x = WIDTH / 2 - 50;
	dest.y = HEIGTH/2 - 50;
	dest.w = 100;
	dest.h = 100;*/
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
			map->UpdateMapY(speed);
			needUpdate = true;
		}
		else if (!keyboard_state_array[SDL_SCANCODE_UP] && keyboard_state_array[SDL_SCANCODE_DOWN])
		{
			map->UpdateMapY(-speed);
			needUpdate = true;
		}

		if (keyboard_state_array[SDL_SCANCODE_RIGHT] && !keyboard_state_array[SDL_SCANCODE_LEFT])
		{
			map->UpdateMapX(-speed);
			needUpdate = true;
		}
		else if (!keyboard_state_array[SDL_SCANCODE_RIGHT] && keyboard_state_array[SDL_SCANCODE_LEFT])
		{
			map->UpdateMapX(speed);
			needUpdate = true;
		}
	}

	
}

void Game::update()
{

}

void Game::render()
{
	if (NeedUpdate() == true) {
		SDL_SetRenderDrawColor(map->textureManager.renderer, 27, 28, 50, 0);
		SDL_RenderClear(map->textureManager.renderer);
		map->DrawMap();
		//TextureManager::Drow(player, src, dest);
		SDL_RenderPresent(map->textureManager.renderer);
		needUpdate = false;
	}
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(map->textureManager.renderer);
	SDL_Quit();

	printf("game cleaned\n");
}

bool Game::running()
{
	return isRunning;
}

bool Game::NeedUpdate()
{
	return needUpdate;
}
