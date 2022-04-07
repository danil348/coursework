#include "Map.h"

SDL_Renderer* TextureManager::renderer = nullptr;

Map::Map()
{
	ground_1 = TextureManager::LoadTexture("assets/1.png");
	ground_2 = TextureManager::LoadTexture("assets/2.png");
	ground_3 = TextureManager::LoadTexture("assets/3.png");
	ground_4 = TextureManager::LoadTexture("assets/4.png");
	ground_5 = TextureManager::LoadTexture("assets/5.png");
	coin = TextureManager::LoadTexture("assets/9.png");
	hpBoard = TextureManager::LoadTexture("assets/hp.png");

	//сундуки
	int x, y;
	for (int row = 0; row < lvl1_h; row++) {
		for (int column = 0; column < lvl1_w; column++) {
			if (lvl1[row][column] == 7) {
				chestCount++;
			}
			else if (lvl1[row][column] == 8) {
				statueCount++;
			}
			else if (lvl1[row][column] == 10 || lvl1[row][column] == 11 || lvl1[row][column] == 12 || lvl1[row][column] == 13) {
				closingWallCount++;
			}
			else if (lvl1[row][column] == 1) {
				defoltWallCount++;
			}
			
		}
	}
	chest = new Chest[chestCount];
	statue = new Statue[statueCount];
	closingWall = new ClosingWall[closingWallCount];
	bullets = new Bullets[bulletsCount];
	defoltWall = new GameObgect[defoltWallCount];
	chestCount = 0;
	statueCount = 0;
	closingWallCount = 0;
	defoltWallCount = 0;
	for (int row = 0; row < lvl1_h; row++) {
		for (int column = 0; column < lvl1_w; column++) {
			if (lvl1[row][column] == 7) {
				chest[chestCount].posX = column;
				chest[chestCount].posY = row;
				chest[chestCount].setSrcDest_W_H(tile_w, tile_h, tile_w, tile_h);
				chest[chestCount].setMainTexture(TextureManager::LoadTexture("assets/6.png"));
				chest[chestCount].setSecondTexture(TextureManager::LoadTexture("assets/7.png"));
				chestCount++;
			}
			else if (lvl1[row][column] == 8) {
				statue[statueCount].posX = column;
				statue[statueCount].posY = row;
				statue[statueCount].setSrcDest_W_H(288, 320, tile_w * 3, tile_h * 3);
				statue[statueCount].setMainTexture(TextureManager::LoadTexture("assets/player.png"));
				statueCount++;
			}
			else if (lvl1[row][column] == 10 || lvl1[row][column] == 11 || lvl1[row][column] == 12 || lvl1[row][column] == 13) {
				closingWall[closingWallCount].posX = column;
				closingWall[closingWallCount].posY = row;
				closingWall[closingWallCount].type = lvl1[row][column];
				closingWall[closingWallCount].setSrcDest_W_H(tile_w, tile_h, tile_w, tile_h);
				closingWall[closingWallCount].setMainTexture(TextureManager::LoadTexture("assets/2.png"));
				closingWall[closingWallCount].setSecondTexture(TextureManager::LoadTexture("assets/0.png"));
				closingWallCount++;
			}
			else if (lvl1[row][column] == 1) {
				defoltWall[defoltWallCount].posX = column;
				defoltWall[defoltWallCount].posY = row;
				defoltWall[defoltWallCount].setSrcDest_W_H(tile_w, tile_h, tile_w, tile_h);
				defoltWall[defoltWallCount].setMainTexture(TextureManager::LoadTexture("assets/0.png"));
				defoltWallCount++;
			}
		}
	}

	src.x = src.y = 0;
	src.w = tile_w;
	src.h = tile_h;

	dest.x = dest.y = 0;
	dest.w = tile_w;
	dest.h = tile_h;
	cout << "Game objects created!\n";
}


void Map::DrawMap(SDL_Window* window)
{
	SDL_GetMouseState(&mousePosX, &mousePosY);
	for (int row = 0; row < lvl1_h; row++) {
		for (int column = 0; column < lvl1_w; column++) {
			dest.x = column * tile_w + offsetX;
			dest.y = row * tile_h + offsetY;
			if (dest.x > -tile_w && dest.x < WIDTH + tile_w && dest.y > -tile_h && dest.y < HEIGTH + tile_h && lvl1[row][column] !=0) {
				switch (lvl1[row][column]) {
				case 0: break;
				case 1: TextureManager::Drow(defoltWall[0].getMainTexture(), src, dest); break;
				case 2: TextureManager::Drow(ground_1, src, dest); break;
				case 3: TextureManager::Drow(ground_2, src, dest); break;
				case 4: TextureManager::Drow(ground_3, src, dest); break;
				case 5: TextureManager::Drow(ground_4, src, dest); break;
				case 6: TextureManager::Drow(ground_5, src, dest); break;
				case 7: TextureManager::Drow(ground_5, src, dest);
					for (int i = 0; i < chestCount; i++) {
						if (chest[i].posX == column && chest[i].posY == row) {
							chest[i].setSrcDest_X_Y(src.x, src.y, dest.x, dest.y);
							if (IntersectionWithGameObg(chest[i]) == true && chest[i].isOpen() == false) {
								chest[i].getBonus(hpPlayer, armorPlayer, manaPlayer, scorePlayer);
							}
							TextureManager::Drow(chest[i].getMainTexture(), chest[i].src, chest[i].dest);
							break;
						}
					}
					break;
				case 8:
					TextureManager::Drow(ground_5, src, dest);
					for (int i = 0; i < statueCount; i++) {
						if (statue[i].posX == column && statue[i].posY == row) {
							statue[i].setSrcDest_X_Y(src.x, src.y, dest.x - tile_w, dest.y - tile_h * 2);
							TextureManager::Drow(statue[i].getMainTexture(), statue[i].src, statue[i].dest);
							if (IntersectionWithGameObg(statue[i]) == true && statue[i].isUsed() == false) {
								if (key.space == true) {
									statue[i].wasUsed = true;
								}
							}
							if (statue[i].wasUsed == true) {
								statue[i].getBonus(hpPlayer, armorPlayer, manaPlayer, scorePlayer);
							}
							break;
						}
					}
					break;
				case 10: case 11: case 12: case 13:
					for (int i = 0; i < closingWallCount; i++) {
						if (closingWall[i].posX == column && closingWall[i].posY == row) {
							closingWall[i].setSrcDest_X_Y(src.x, src.y, dest.x, dest.y);
							if (IntersectionWithGameObg(closingWall[i]) == true && closingWall[i].mayClose == true) {
								for (int j = 0; j < closingWallCount; j++) {
									if (abs(closingWall[i].posX - closingWall[j].posX) < 15 && abs(closingWall[i].posY - closingWall[j].posY) < 15) {
										closingWall[j].isClos = true;
										closingWall[j].mayClose = false;
									}
								}
							}
#ifdef DEBUG
							if (key.space == true) {
								for (int j = 0; j < closingWallCount; j++) {
									if (abs(closingWall[i].posX - closingWall[j].posX) < 15 && abs(closingWall[i].posY - closingWall[j].posY) < 15) {
										closingWall[j].isClos = false;
									}
								}
							}
#endif // DEBUG
							if (closingWall[i].isClos == false) {
								TextureManager::Drow(closingWall[i].getMainTexture(), closingWall[i].src, closingWall[i].dest);
							}
							else {
								TextureManager::Drow(closingWall[i].getSecondTexture(), closingWall[i].src, closingWall[i].dest);
							}
							break;
						}
					}
					break;
				default:
					break;
				}
			}
		}
	}

	// монеты
	_rect = { 10, 170, 40, 40 };
	_srect = { 0, 0, 56, 80 };
	TextureManager::Drow(coin, _srect, _rect);
	textManager.Drow(textureManager.renderer, to_string(scorePlayer), 50, 50, 80, 170, 232, 221, 186);

	// доска с характеристиками
	_srect = { 0,0, 292,148 };
	_rect = { 5,2, 270,145 };
	SDL_SetRenderDrawColor(textureManager.renderer, 30, 30, 30, 0);
	SDL_RenderFillRect(textureManager.renderer, &_rect);
	_rect = { 0,0, 292, 148 };
	TextureManager::Drow(hpBoard, _srect, _rect);

	_rect = { 52,16, 212*hpPlayer/100, 28 };
	SDL_SetRenderDrawColor(textureManager.renderer, 237, 65, 63, 0);
	SDL_RenderFillRect(textureManager.renderer, &_rect);
	textManager.Drow(textureManager.renderer, to_string(hpPlayer), 52, 26, 138, 20, 255, 255, 255);


	_rect = { 52, 56, 212 * armorPlayer / 100,28 };
	SDL_SetRenderDrawColor(textureManager.renderer, 136, 142, 140, 0);
	SDL_RenderFillRect(textureManager.renderer, &_rect);
	textManager.Drow(textureManager.renderer, to_string(armorPlayer), 52, 26, 138, 60, 255, 255, 255);

	_rect = { 52, 96, 212 * manaPlayer / 100,28 };
	SDL_SetRenderDrawColor(textureManager.renderer, 15, 123, 178, 0);
	SDL_RenderFillRect(textureManager.renderer, &_rect);
	textManager.Drow(textureManager.renderer, to_string(manaPlayer), 52, 26, 138, 100, 255, 255, 255);

	SDL_SetRenderDrawColor(textureManager.renderer, 255, 0, 0, 0);
	rect = { WIDTH / 2, HEIGTH / 2, 10, 10 };
	SDL_RenderFillRect(textureManager.renderer, &rect);

	SDL_SetRenderDrawColor(textureManager.renderer, 255, 255, 255, 0);
	if (key.leftMouseKey == true) {
		for (int i = 0; i < bulletsCount; i++) {
			if (bullets[i].isFly == false) {
				bullets[i].setAngl(mousePosX, mousePosY, WIDTH, HEIGTH);
				break;
			}
		}
	}
	for (int i = 0; i < bulletsCount; i++) {
		if (bullets[i].intersection(defoltWall, defoltWallCount, closingWall, closingWallCount, tile_w, tile_h, offsetX, offsetY) == true) {
			bullets[i].reset();
		}
		if (bullets[i].isFly == true) {
			bullets[i].fly();
			SDL_RenderDrawPoint(textureManager.renderer, bullets[i].Bx, bullets[i].By);
		}
	}
}


void Map::UpdateMapX(float value)
{
	offsetX += value;
	if (Intersection(1) == true) {
		offsetX -= value;
	}else if (Intersection(10) == true) {
		offsetX -= value;
	} 
	else {
		for (int i = 0; i < bulletsCount; i++) {
			if (bullets[i].isFly == true) {
				bullets[i].offX += value;
			}
		}
	}
}

void Map::UpdateMapY(float value)
{
	offsetY += value;
	if (Intersection(1) == true) {
		offsetY -= value;
	}else if (Intersection(10) == true) {
		offsetY -= value;
	}
	else {
		for (int i = 0; i < bulletsCount; i++) {
			if (bullets[i].isFly == true) {
				bullets[i].offY += value;
			}
		}
	}
}

bool Map::Intersection(int type)
{
	if (type == 10 || type == 11 || type == 12 || type == 13) {
		for (int j = 0; j < closingWallCount; j++) {
			if (WIDTH / 2 >= closingWall[j].posX * tile_w + offsetX && WIDTH / 2 <= closingWall[j].posX * tile_w + offsetX + tile_w &&
				HEIGTH / 2 >= closingWall[j].posY * tile_h + offsetY && HEIGTH / 2 <= closingWall[j].posY * tile_h + offsetY + tile_h &&
				closingWall[j].isClos == true) {
				return 1;
			}
		}
	}
	else if (type == 1) {
		for (int j = 0; j < defoltWallCount; j++) {
			if (WIDTH / 2 >= defoltWall[j].posX * tile_w + offsetX && WIDTH / 2 <= defoltWall[j].posX * tile_w + offsetX + tile_w &&
				HEIGTH / 2 >= defoltWall[j].posY * tile_h + offsetY && HEIGTH / 2 <= defoltWall[j].posY * tile_h + offsetY + tile_h) {
				return 1;
			}
		}
	}
	return 0;
}

bool Map::IntersectionWithGameObg(GameObgect gameObgect)
{
	if (WIDTH / 2 >= gameObgect.dest.x && WIDTH / 2 <= gameObgect.dest.x + gameObgect.dest.w && HEIGTH / 2 >= gameObgect.dest.y && HEIGTH / 2 <= gameObgect.dest.y + gameObgect.dest.h) {
		return 1;
	}
	return 0;
}

bool Map::IntersectionWithGameObg(Chest chest)
{
	if (WIDTH / 2 >= chest.dest.x && WIDTH / 2 <= chest.dest.x + chest.dest.w && HEIGTH / 2 >= chest.dest.y && HEIGTH / 2 <= chest.dest.y + chest.dest.h) {
		return 1;
	}
	return 0;
}

bool Map::IntersectionWithGameObg(ClosingWall wall)
{
	if (wall.type == 10) {
		if (WIDTH / 2 >= wall.dest.x && WIDTH / 2 < wall.dest.x + wall.dest.w && HEIGTH / 2 > wall.dest.y + wall.dest.h + 1 && HEIGTH / 2 < wall.dest.y + wall.dest.h + 10) {
			return 1;
		}
	}
	else if (wall.type == 11) {
		if (HEIGTH / 2 > wall.dest.y && HEIGTH / 2 < wall.dest.y + wall.dest.h && WIDTH / 2 < wall.dest.x - 1 && WIDTH / 2 > wall.dest.x - 10) {
			return 1;
		}
	}
	else if (wall.type == 12) {
		if (WIDTH / 2 > wall.dest.x && WIDTH / 2 < wall.dest.x + wall.dest.w && HEIGTH / 2 < wall.dest.y - 1 && HEIGTH / 2 > wall.dest.y - 10) {
			return 1;
		}
	}
	else if (wall.type == 13) {
		if (HEIGTH / 2 > wall.dest.y && HEIGTH / 2 < wall.dest.y + wall.dest.h && WIDTH / 2 > wall.dest.x + wall.dest.w + 1 && WIDTH / 2 < wall.dest.x + wall.dest.w + 10) {
			return 1;
		}
	}
	return 0;
}

void Map::SetSize(int w, int h)
{
	WIDTH = w;
	HEIGTH = h;
}

void Map::changingKeyState(const Uint8* arr)
{
	key.space = arr[SDL_SCANCODE_SPACE];
}

void Map::changingKeyState(bool mouseDown)
{
	key.leftMouseKey = mouseDown;
}
