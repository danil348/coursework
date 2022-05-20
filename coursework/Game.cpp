#include "Game.h"

Map* _map;
Menu* menu;

void Game::init(const char* title, int xpos, int ypos, bool fullscrean)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		isRunning = false;
		printf("SDL Error: %S", SDL_GetError());
	}
	else if (IMG_Init(IMG_INIT_PNG) == 0) {
		printf("IMG Error: %S", SDL_GetError());
	}
	else {
		printf("Initialised!\n");
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 12, 12, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
		if (window) {
			printf("Window created!\n");
		}
		_map->textureManager.renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		if (_map->textureManager.renderer) {
			SDL_SetRenderDrawColor(_map->textureManager.renderer, 255, 255, 255, 255);
			printf("Renderer created!\n");
		}
		isRunning = true;
	}
	

	_map = new Map;
	dataStorage.getSetting(_map->settings);
	_map->UpdateSetiings();
	menu = new Menu;
	for (int i = 0; i < _map->settings.itemCount; i++) {
		if (_map->settings.screen[i][2] == 1) {
			if (_map->settings.screen[i][0] == 1) {
				SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
			}
			else {
				SDL_SetWindowSize(window, _map->settings.screen[i][0], _map->settings.screen[i][1]);
			}
		}
	}
	menu->fisrtItems[0].activeTexture = TextureManager::LoadTexture("assets/menu_newgameActive.png");
	menu->fisrtItems[0].texture = TextureManager::LoadTexture("assets/menu_newgame.png");
	menu->fisrtItems[1].activeTexture = TextureManager::LoadTexture("assets/menu_settingActive.png");
	menu->fisrtItems[1].texture = TextureManager::LoadTexture("assets/menu_setting.png");
	menu->fisrtItems[2].activeTexture = TextureManager::LoadTexture("assets/menu_exitActive.png");
	menu->fisrtItems[2].texture = TextureManager::LoadTexture("assets/menu_exit.png");

	menu->settingsItems[0].activeTexture = TextureManager::LoadTexture("assets/menu_soundActive.png");
	menu->settingsItems[0].texture = TextureManager::LoadTexture("assets/menu_sound.png");
	menu->settingsItems[1].activeTexture = TextureManager::LoadTexture("assets/menu_screenActive.png");
	menu->settingsItems[1].texture = TextureManager::LoadTexture("assets/menu_screen.png");

	menu->soundOff = TextureManager::LoadTexture("assets/menu_soundoff.png");
	menu->soundOn = TextureManager::LoadTexture("assets/menu_soundon.png");

	menu->fullscreen = TextureManager::LoadTexture("assets/menu_fullscreen.png");
	menu->screen1 = TextureManager::LoadTexture("assets/screen1.png");
	menu->screen2 = TextureManager::LoadTexture("assets/screen2.png");
	menu->screen3 = TextureManager::LoadTexture("assets/screen3.png");

	sound.addSoundEffect("switch.wav");

	event.key.keysym.scancode = SDL_SCANCODE_0;
	event.type = NULL;
}


void Game::handleEvents()
{
	SDL_PollEvent(&event);


	SDL_GetRendererOutputSize(_map->textureManager.renderer, &w, &h);
	_map->Update_W_H(w, h);
	if (keyArray[SDL_SCANCODE_ESCAPE]) {
		menu->timeOfLastKey = clock();
		if (menu->timeOfLastKey - menu->timeOfCurrentKey > menu->keyDelay) {
			menu->isRunning = !menu->isRunning;
			menu->timeOfCurrentKey = clock();
		}
	}
	else if (menu->isRunning == false) {
		if (keyArray[SDL_SCANCODE_W] && !(keyArray[SDL_SCANCODE_S]))
		{
			_map->UpdateMapY(_map->playerSettings.speed);
		}
		else if (!keyArray[SDL_SCANCODE_W] && keyArray[SDL_SCANCODE_S])
		{
			_map->UpdateMapY(-_map->playerSettings.speed);
		}

		if (keyArray[SDL_SCANCODE_D] && !keyArray[SDL_SCANCODE_A])
		{
			_map->UpdateMapX(-_map->playerSettings.speed);
		}
		else if (!keyArray[SDL_SCANCODE_D] && keyArray[SDL_SCANCODE_A])
		{
			_map->UpdateMapX(_map->playerSettings.speed);
		}

		_map->changingKeyState((GetKeyState(VK_LBUTTON) & 0x8000));
		_map->changingKeyState(keyArray);
	}
	else if (menu->isRunning == true) {
		menu->timeOfLastKey = clock();
		if (menu->timeOfLastKey - menu->timeOfCurrentKey > menu->keyDelay) {
			if (keyArray[SDL_SCANCODE_UP]) {
				sound.playSoundEffect(0);
				menu->activeMenu--;
				if (menu->typeMenu == 0) {
					if (menu->activeMenu < 0) {
						menu->activeMenu = menu->mainMenuCount - 1;
					}
				}
				else if (menu->typeMenu == 1) {
					if (menu->activeMenu < 0) {
						menu->activeMenu = menu->settingsMenuCount - 1;
					}
				}
			}
			else if (keyArray[SDL_SCANCODE_DOWN]) {
				sound.playSoundEffect(0);
				menu->activeMenu++;
				if (menu->typeMenu == 0) {
					if (menu->activeMenu >= menu->mainMenuCount) {
						menu->activeMenu = 0;
					}
				}
				else if (menu->typeMenu == 1) {
					if (menu->activeMenu >= menu->settingsMenuCount) {
						menu->activeMenu = 0;
					}
				}
			}
			if (keyArray[SDL_SCANCODE_RETURN]) {
				sound.playSoundEffect(0);

				if (menu->typeMenu == 1) {
					menu->typeMenu = 0;
					menu->activeMenu = 1;

					for (int i = 0; i < _map->settings.itemCount; i++) {
						if (_map->settings.screen[i][2] == 1) {
							if (_map->settings.screen[i][0] == 1 && _map->settings.screen[i][1] == 1) {
								SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
							}
							else {
								SDL_SetWindowFullscreen(window, 0);

								SDL_SetWindowSize(window, _map->settings.screen[i][0], _map->settings.screen[i][1]);
								SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
							}
						}
					}
				
				}else  if (menu->typeMenu == 0) {
					if (menu->activeMenu == 2) {
						isRunning = false;
					}
					else if (menu->activeMenu == 1) {
						menu->typeMenu = 1;
						menu->activeMenu = 0;
					}
					else if (menu->activeMenu == 0) {
						dataStorage.refreshSetting(_map->settings);
						dataStorage.getSetting(_map->settings);
						_map->Update_W_H(w, h);
						_map->RoomCreater(true);
						menu->isRunning = false;
						_map->playerIsdeadh = false;
						needPlayEnd = true;
					}
				}

			}

			if (keyArray[SDL_SCANCODE_LEFT] == true && menu->typeMenu == 1 && menu->activeMenu == 0) {
				_map->settings.sound = !_map->settings.sound;
			}
			if (keyArray[SDL_SCANCODE_RIGHT] == true && menu->typeMenu == 1 && menu->activeMenu == 0) {
				_map->settings.sound = !_map->settings.sound;
			}

			if (keyArray[SDL_SCANCODE_LEFT] == true && menu->typeMenu == 1 && menu->activeMenu == 1) {
				_map->settings.screen[_map->settings.activeItem][2] = 0;
				_map->settings.activeItem--;
				if (_map->settings.activeItem < 0) {
					_map->settings.activeItem = _map->settings.itemCount - 1;
				}
				_map->settings.screen[_map->settings.activeItem][2] = 1;

			}
			if (keyArray[SDL_SCANCODE_RIGHT] == true && menu->typeMenu == 1 && menu->activeMenu == 1) {
				_map->settings.screen[_map->settings.activeItem][2] = 0;
				_map->settings.activeItem++;
				if (_map->settings.activeItem >= _map->settings.itemCount) {
					_map->settings.activeItem = 0;
				}
				_map->settings.screen[_map->settings.activeItem][2] = 1;
			}

			menu->timeOfCurrentKey = clock();
		}
	}
}

void Game::update()
{
	if (timeOfLastend == 0 && needPlayEnd == true && _map->playerIsdeadh == true) {
		timeOfLastend = clock();
	}
	
	if (_map->playerIsdeadh == true) {
		menu->isRunning = true;
		if (needPlayEnd == true) {
			endplay = true;
			timeOfCurrentend = clock();
			playEnd();
			if (timeOfCurrentend - timeOfLastend  > endDelay) {
				needPlayEnd = false;
				endplay = false;
			}
		}
	}
}

void Game::menuRender()
{
	if (menu->isRunning == true && endplay == false) {
		SDL_SetRenderDrawColor(_map->textureManager.renderer, 27, 28, 50, 0);
		SDL_RenderClear(_map->textureManager.renderer);
		if (menu->typeMenu == 0) {
			for (int i = 0; i < menu->mainMenuCount; i++) {
				menu->_src = { 0,0,300,90 };
				menu->_dest = { w / 2 - menu->_src.w / 2,200 * i,300,90 };
				if (i == menu->activeMenu) {
					TextureManager::Drow(menu->fisrtItems[i].activeTexture, menu->_src, menu->_dest);
				}
				else {
					TextureManager::Drow(menu->fisrtItems[i].texture, menu->_src, menu->_dest);
				}
			}
		}
		else if (menu->typeMenu == 1) {
			for (int i = 0; i < menu->settingsMenuCount; i++) {
				menu->_src = { 0,0,300,90 };
				menu->_dest = { w / 2 - menu->_src.w / 2  - 100, 200 * i,300,90 };
				
				if (i == menu->activeMenu) {
					TextureManager::Drow(menu->settingsItems[i].activeTexture, menu->_src, menu->_dest);
				}
				else {
					TextureManager::Drow(menu->settingsItems[i].texture, menu->_src, menu->_dest);
				}

				if (i == 0) {
					menu->_src = { 0,0,150,90 };
					menu->_dest = { w / 2 - menu->_src.w / 2 + 100, 200 * i,150,90 };
					if (_map->settings.sound == false) {
						TextureManager::Drow(menu->soundOff, menu->_src, menu->_dest);
					}
					else {
						TextureManager::Drow(menu->soundOn, menu->_src, menu->_dest);
					}
				}
				else if (i == 1) {
					menu->_src = { 0,0,300,90 };
					menu->_dest = { w / 2 - menu->_src.w / 2 + 250, 200 * i + 10,300,90 };
					if (_map->settings.screen[3][2] == 1) {
						TextureManager::Drow(menu->fullscreen, menu->_src, menu->_dest);
					}
					else {
						if (_map->settings.screen[0][2] == 1) {
							TextureManager::Drow(menu->screen1, menu->_src, menu->_dest);
						}
						else if (_map->settings.screen[1][2] == 1) {
							TextureManager::Drow(menu->screen2, menu->_src, menu->_dest);
						}
						else if (_map->settings.screen[2][2] == 1) {
							TextureManager::Drow(menu->screen3, menu->_src, menu->_dest);
						}
					}
				}
				
			}
		}
		SDL_RenderPresent(_map->textureManager.renderer);
	}
}

void Game::gameRender()
{
	if (menu->isRunning == false && _map->playerIsdeadh == false) {
		SDL_SetRenderDrawColor(_map->textureManager.renderer, 27, 28, 50, 0);
		SDL_RenderClear(_map->textureManager.renderer);
		_map->DrawMap(window);
		SDL_RenderPresent(_map->textureManager.renderer);
	}
}

void Game::clean()
{
	dataStorage.saveSetting(_map->settings);
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(_map->textureManager.renderer);
	TTF_Quit();
	SDL_Quit();

	printf("game cleaned\n");
}

bool Game::running()
{
	return isRunning;
}

void Game::playEnd()
{
	SDL_SetRenderDrawColor(_map->textureManager.renderer, 27, 28, 50, 0);
	SDL_RenderClear(_map->textureManager.renderer);			
	_map->textManager.Drow(_map->textureManager.renderer, u8"Game Over", 17 * 14*2, 28*2, w/2- 17 * 14, h/2 - 28, 232, 221, 186);
	SDL_SetRenderDrawColor(_map->textureManager.renderer, 232, 221, 186, 0);
	SDL_RenderDrawLine(_map->textureManager.renderer, 0, h / 2 - 28 - 50, w, h / 2 - 28 - 50);
	SDL_RenderDrawLine(_map->textureManager.renderer, 0, h / 2 - 28 + 100, w, h / 2 - 28 + 100);
	
	SDL_RenderPresent(_map->textureManager.renderer);
}
