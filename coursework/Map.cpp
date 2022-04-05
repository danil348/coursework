#include <string>
#include "Map.h"
using namespace std;

SDL_Renderer* TextureManager::renderer = nullptr;
Map::Map()
{

	wall_1 = TextureManager::LoadTexture("assets/0.png");
	ground_1 = TextureManager::LoadTexture("assets/1.png");
	ground_2 = TextureManager::LoadTexture("assets/2.png");
	ground_3 = TextureManager::LoadTexture("assets/3.png");
	ground_4 = TextureManager::LoadTexture("assets/4.png");
	ground_5 = TextureManager::LoadTexture("assets/5.png");
	chest_1 = TextureManager::LoadTexture("assets/6.png");
	chest_2 = TextureManager::LoadTexture("assets/7.png");
	coin = TextureManager::LoadTexture("assets/9.png");
	hpBoard = TextureManager::LoadTexture("assets/hp.png");

	statue.setMainTexture(TextureManager::LoadTexture("assets/player.png"));
	statue.setSrcDest_W_H(288, 320, tile_w*3, tile_h*3);

	//сундуки
	int x, y;
	for (int row = 0; row < lvl1_h; row++) {
		for (int column = 0; column < lvl1_w; column++) {
			if (lvl1[row][column] == 7) {
				chestCount++;
			}
		}
	}
	chest = new Chest[chestCount];
	chestCount = 0;
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
		}
	}

	src.x = src.y = 0;
	src.w = tile_w;
	src.h = tile_h;

	dest.x = dest.y = 0;
	dest.w = tile_w;
	dest.h = tile_h;
}


void Map::DrawMap(SDL_Window* window)
{
	int type = 0;
	int tmpOffset = 0;
	for (int row = 0; row < lvl1_h; row++) {
		for (int column = 0; column < lvl1_w; column++) {
			type = lvl1[row][column];
			dest.x = column * tile_w + offsetX;
			dest.y = row * tile_h + offsetY;
			if (dest.x > -tile_w && dest.x < WIDTH + tile_w && dest.y > -tile_h && dest.y < HEIGTH + tile_h && type!=0) {
				switch (type) {
				case 0: break;
				case 1: TextureManager::Drow(wall_1, src, dest); break;
				case 2: TextureManager::Drow(ground_1, src, dest); break;
				case 3: TextureManager::Drow(ground_2, src, dest); break;
				case 4: TextureManager::Drow(ground_3, src, dest); break;
				case 5: TextureManager::Drow(ground_4, src, dest); break;
				case 6: TextureManager::Drow(ground_5, src, dest); break;
				case 9:
					TextureManager::Drow(ground_5, src, dest);
					TextureManager::Drow(chest_2, src, dest); break;
				default:
					break;
				}
			}
		}
	}
	for (int row = 0; row < lvl1_h; row++) {
		for (int column = 0; column < lvl1_w; column++) {
			type = lvl1[row][column];
			dest.x = column * tile_w + offsetX;
			dest.y = row * tile_h + offsetY;
			if (dest.x > -tile_w && dest.x < WIDTH + tile_w && dest.y > -tile_h && dest.y < HEIGTH + tile_h && type != 0) {
				switch (type)
				{
				case 7: TextureManager::Drow(ground_5, src, dest);
					for (int i = 0; i < chestCount; i++) {
						if (chest[i].posX == column && chest[i].posY == row) {
							chest[i].setSrcDest_X_Y(src.x, src.y, dest.x, dest.y);
							if (IntersectionWithGameObg(chest[i]) == true && chest[i].isOpen() == false) {
								chest[i].chengeOpenState(true);
#ifdef DEBUG
								if (manaPlayer < 100) {
									manaPlayer += 10;
								}
								scorePlayer += 1;
								cout << "\n\nу игрока " << scorePlayer << " очков\n\n";
#endif // DEBUG
							}
							if (chest[i].isOpen() == false) {
								TextureManager::Drow(chest[i].getMainTexture(), chest[i].src, chest[i].dest);
							}
							else {
								TextureManager::Drow(chest[i].getSecondTexture(), chest[i].src, chest[i].dest);
							}
						}
					}
					break;
				case 8:
					TextureManager::Drow(ground_5, src, dest);
					statue.setSrcDest_X_Y(src.x, src.y, dest.x - tile_w, dest.y - tile_h * 2);
					TextureManager::Drow(statue.getMainTexture(), statue.src, statue.dest);
#ifdef DEBUG
					if (Intersection(8) == true) {
						cout << "игрок зашёл на статую\n";
					}
#endif // DEBUG
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
	//--------------------------
	//
	// тут обработка брони, здоровья, маны
	//
	//--------------------------
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

	SDL_SetRenderDrawColor(textureManager.renderer, 12, 123, 123, 0);


#ifdef DEBUG
	SDL_SetRenderDrawColor(textureManager.renderer, 255, 0, 0, 0);
	rect = { WIDTH / 2, HEIGTH / 2, 10, 10 };
	SDL_RenderFillRect(textureManager.renderer, &rect);
	SDL_SetRenderDrawColor(textureManager.renderer, 12, 123, 123, 0);
#endif // DEBUG
}


void Map::UpdateMapX(float value)
{
	offsetX += value;
	if (Intersection(1) == true) {
		offsetX -= value;
	}
}

void Map::UpdateMapY(float value)
{
	offsetY += value;
	if (Intersection(1) == true) {
		offsetY -= value;
	}
}

bool Map::Intersection(int type)
{
	int x;
	int y;
	for (int row = 0; row < lvl1_h; row++) {
		for (int column = 0; column < lvl1_w; column++) {
			if (lvl1[row][column] == type) {
				x = column * tile_w + offsetX;
				y = row * tile_h + offsetY;
				if (WIDTH / 2 >= x && WIDTH / 2 <= x + tile_w && HEIGTH / 2 >= y && HEIGTH / 2 <= y + tile_h) {
					
#ifdef DEBUG
					switch (type)
					{
					case 1: cout << "игрок касается стены " << offsetX << '\n'; break;
					case 7: cout << "игрок на сундуке " << offsetX << '\n'; break;
					default: break;
					}
#endif // DEBUG

					return 1;
				}
			}
		}
	}
	return 0;
}

bool Map::IntersectionWithGameObg(GameObgect gameObgect)
{
	if (WIDTH / 2 >= gameObgect.dest.x && WIDTH / 2 <= gameObgect.dest.x + gameObgect.dest.w && HEIGTH / 2 >= gameObgect.dest.y && HEIGTH / 2 <= gameObgect.dest.y + gameObgect.dest.h) {

#ifdef DEBUG
		cout << "игрок на сундуке " << offsetX << '\n';
#endif // DEBUG

		return 1;
	}
	return 0;
}

bool Map::IntersectionWithGameObg(Chest chest)
{
	if (WIDTH / 2 >= chest.dest.x && WIDTH / 2 <= chest.dest.x + chest.dest.w && HEIGTH / 2 >= chest.dest.y && HEIGTH / 2 <= chest.dest.y + chest.dest.h) {

#ifdef DEBUG
		cout << "игрок на сундуке " << offsetX << '\n';
#endif // DEBUG

		return 1;
	}
	return 0;
}

void Map::SetSize(int w, int h)
{
	WIDTH = w;
	HEIGTH = h;
}
