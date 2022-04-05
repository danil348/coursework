#include "Map.h"
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

	statue.setMainTexture(TextureManager::LoadTexture("assets/player.png"));
	statue.setSrcDest_W_H(288, 320, 400, 400);

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
				chest[chestCount].setSrcDest_W_H(120, 120, 120, 120);
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


void Map::DrawMap()
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
								chest[i].chengeOpenState();
#ifdef DEBUG
								scorePlayer += 100;
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
					statue.setSrcDest_X_Y(src.x, src.y, dest.x - statue.dest.w / 2, dest.y - statue.dest.h / 2);
					TextureManager::Drow(statue.getMainTexture(), statue.src, statue.dest); 
					if (Intersection(8) == true) {
						cout << " asd ";
					}
					break;
				default:
					break;
				}
			}
		}
	}
	SDL_SetRenderDrawColor(textureManager.renderer, 255, 0, 0, 0);

	SDL_Rect rect = { WIDTH / 2, HEIGTH / 2, 10, 10 };
	SDL_RenderFillRect(textureManager.renderer, &rect);
	SDL_RenderDrawPoint(textureManager.renderer, WIDTH / 2, HEIGTH / 2);
	SDL_SetRenderDrawColor(textureManager.renderer, 12, 123, 123, 0);
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
