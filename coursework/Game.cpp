#include "Game.h"

Map* map;
Menu* menu;

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
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1300, 900, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
		if (window) {
			printf("Window created!\n");
		}
		//SDL_SetWindowFullscreen(window, 1);
		map->textureManager.renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		if (map->textureManager.renderer) {
			SDL_SetRenderDrawColor(map->textureManager.renderer, 255, 255, 255, 255);
			printf("Renderer created!\n");
		}
		isRunning = true;
	}
	
	int w, h;
	SDL_GetRendererOutputSize(map->textureManager.renderer, &w, &h);

	map = new Map;
	menu = new Menu;
	map->Update_W_H(w, h);
	map->RoomCreater();
	event.key.keysym.scancode = SDL_SCANCODE_0;
	event.type = NULL;

}


void Game::handleEvents()
{
	SDL_PollEvent(&event);


	int w, h;
	SDL_GetRendererOutputSize(map->textureManager.renderer, &w, &h);
	map->Update_W_H(w, h);
	if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE ||
		event.key.keysym.scancode == SDL_SCANCODE_RETURN ||
		event.type == SDL_QUIT) {
		menu->timeOfLastKey = clock();
		if (menu->timeOfLastKey - menu->timeOfCurrentKey > menu->keyDelay) {
			menu->isRunning = !menu->isRunning;
			menu->timeOfCurrentKey = clock();
		}
	}
	else if (menu->isRunning == false) {


		if (keyboard_state_array[SDL_SCANCODE_W] && !(keyboard_state_array[SDL_SCANCODE_S]))
		{
			map->UpdateMapY(map->playerSettings.speed);
		}
		else if (!keyboard_state_array[SDL_SCANCODE_W] && keyboard_state_array[SDL_SCANCODE_S])
		{
			map->UpdateMapY(-map->playerSettings.speed);
		}

		if (keyboard_state_array[SDL_SCANCODE_D] && !keyboard_state_array[SDL_SCANCODE_A])
		{
			map->UpdateMapX(-map->playerSettings.speed);
		}
		else if (!keyboard_state_array[SDL_SCANCODE_D] && keyboard_state_array[SDL_SCANCODE_A])
		{
			map->UpdateMapX(map->playerSettings.speed);
		}

		map->changingKeyState((GetKeyState(VK_LBUTTON) & 0x8000));
		map->changingKeyState(keyboard_state_array);
	}

	if (menu->isRunning == true) {
		if (keyboard_state_array[SDL_SCANCODE_P] == true) {
			SDL_SetWindowSize(window, 1300, 800);
		}
	}
}

void Game::update()
{

}

void Game::menuRender()
{
	if (menu->isRunning == true) {
		SDL_SetRenderDrawColor(map->textureManager.renderer, 27, 28, 50, 0);
		SDL_RenderClear(map->textureManager.renderer);
		SDL_RenderPresent(map->textureManager.renderer);
	}
}

void Game::gameRender()
{
	if (menu->isRunning == false) {
		SDL_SetRenderDrawColor(map->textureManager.renderer, 27, 28, 50, 0);
		SDL_RenderClear(map->textureManager.renderer);
		map->DrawMap(window);
		SDL_RenderPresent(map->textureManager.renderer);
	}
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