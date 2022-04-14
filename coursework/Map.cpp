#include "Map.h"

SDL_Renderer* TextureManager::renderer = nullptr;

Map::Map()
{
	weaponSettings.bulletTexture = TextureManager::LoadTexture("assets/b1.png");
	weaponSettings.weaponTexture = TextureManager::LoadTexture("assets/w1.png");
	ground_1 = TextureManager::LoadTexture("assets/1.png");
	ground_2 = TextureManager::LoadTexture("assets/2.png");
	ground_3 = TextureManager::LoadTexture("assets/3.png");
	ground_4 = TextureManager::LoadTexture("assets/4.png");
	ground_5 = TextureManager::LoadTexture("assets/5.png");
	coin = TextureManager::LoadTexture("assets/9.png");
	hpBoard = TextureManager::LoadTexture("assets/hp.png");
	enemyTx = TextureManager::LoadTexture("assets/enemy.png");

	src.x = src.y = 0;
	src.w = tile_w;
	src.h = tile_h;

	dest.x = dest.y = 0;
	dest.w = tile_w;
	dest.h = tile_h;

	RoomCreater();
}


void Map::DrawMap(SDL_Window* window)
{
	SDL_GetMouseState(&key.mousePosX, &key.mousePosY);

	for (int row = 0; row < lvl1_h; row++) {
		for (int column = 0; column < lvl1_w; column++) {
			dest.x = column * tile_w + playerSettings.offsetX;
			dest.y = row * tile_h + playerSettings.offsetY;

			if (lvl1[row][column] == 0) {
				continue;
			}

			if (lvl1[row][column] >= 2 && lvl1[row][column] <= 9 && dest.x > -tile_w && dest.x < WIDTH + tile_w &&
				dest.y > -tile_h && dest.y < HEIGTH + tile_h && lvl1[row][column-1] != 8 && lvl1[row][column - 1] != 9) {
				switch (lvl1[row][column]) {
				case 2: TextureManager::Drow(ground_1, src, dest); break;
				case 3: TextureManager::Drow(ground_2, src, dest); break;
				case 4: TextureManager::Drow(ground_3, src, dest); break;
				case 5: TextureManager::Drow(ground_4, src, dest); break;
				case 6: TextureManager::Drow(ground_5, src, dest); break;
				case 7: ChestDrow(row, column); break;
				case 8: StatueDrow(row, column); break;
				case 9: WeaponDrow(row, column); break;
				default: break;
				}
			}
			else if (dest.x > -tile_w*7 && dest.x < WIDTH + tile_w*7 && dest.y > -tile_h*7 && dest.y < HEIGTH + tile_h*7) {
				switch (lvl1[row][column]) {
				case 1: DefoltWallDrow(row, column); break;
				case 10: case 11: case 12: case 13: ClosingWallDrow(row, column); break;
				case 14: TextureManager::Drow(ground_5, src, dest); break;
				default: break;
				}

				// переключение противников в активное состояние
				EnemyCreator(row, column);
			}
		}
	}
	// отрисовка противников
	EnemyDrow();
	
	// переключение пули в состояние полёта
	BulletCreator();
	// отрисовка пуль
	BulletDrow();
	
	// близкий бой
	CloseFightUpdate();

	// отрисовка моент и доски с характеристиками
	CoinCounterDrow();
	CharacteristicBoardDrow();

#ifdef DEBUG
	PlayerDrow();
#endif // DEBUG

#ifdef DEBUG
	if (key.keyQ == true) {
		RoomCreater();
	}
#endif // DEBUG
}

void Map::RoomCreater()
{
	playerSettings.offsetX = 440.0f;
	playerSettings.offsetY = 60.0f;

	for (int i = 0; i < lvl1_h; i++) {
		for (int j = 0; j < lvl1_w; j++) {
			lvl1[i][j] = 0;
		}
	}

	string lvlPath = "maps/" + to_string(lvl) + ".txt";
	ifstream file(lvlPath);
	string tmpString = "0";

	char str[3];
	if (file.is_open()) {
		for (int i = 0; i < lvl1_h; i++) {
			for (int j = 0; j < lvl1_w; j++) {
				file.getline(str, 3, ',');
				tmpString = str;
				lvl1[i][j] = atoi(tmpString.c_str());
			}
		}
		file.close();
		if (lvl < 2) {
			lvl++;
		}
	}

	for (int row = 0; row < lvl1_h; row++) {
		for (int column = 0; column < lvl1_w; column++) {
			switch (lvl1[row][column]) {
			case 7: chestCount++; break;
			case 8: statueCount++; break;
			case 10:case 11:case 12:case 13: closingWallCount++; break;
			case 1: defoltWallCount++; break;
			case 14: enemyCount++; break;
			case 9: weaponShopCount++; break;
			default: break;
			}

		}
	}
	chest = new Chest[chestCount];
	statue = new Statue[statueCount];
	closingWall = new ClosingWall[closingWallCount];
	bullets = new Bullets[bulletsCount];
	defoltWall = new GameObgect[defoltWallCount];
	enemy = new Enemy[enemyCount];
	weaponShop = new WeaponShop[weaponShopCount];
	chestCount = 0;
	statueCount = 0;
	closingWallCount = 0;
	defoltWallCount = 0;
	enemyCount = 0;
	weaponShopCount = 0;
	for (int row = 0; row < lvl1_h; row++) {
		for (int column = 0; column < lvl1_w; column++) {
			switch (lvl1[row][column]) {
			case 7:
				chest[chestCount].posX = column;
				chest[chestCount].posY = row;
				chest[chestCount].setSrcDest_W_H(tile_w, tile_h, tile_w, tile_h);
				chest[chestCount].setMainTexture(TextureManager::LoadTexture("assets/6.png"));
				chest[chestCount].setSecondTexture(TextureManager::LoadTexture("assets/7.png"));
				chestCount++;
				break;
			case 8:
				statue[statueCount].posX = column;
				statue[statueCount].posY = row;
				statue[statueCount].setSrcDest_W_H(288, 320, tile_w * 3, tile_h * 3);
				statue[statueCount].setType((rand() % 3));
				if (statue[statueCount].getType() == 1) {
					statue[statueCount].setMainTexture(TextureManager::LoadTexture("assets/st1.png"));
				}
				else {
					statue[statueCount].setMainTexture(TextureManager::LoadTexture("assets/st2.png"));
				}
				statueCount++;
				break;
			case 10: case 11: case 12: case 13:
				closingWall[closingWallCount].posX = column;
				closingWall[closingWallCount].posY = row;
				closingWall[closingWallCount].type = lvl1[row][column];
				closingWall[closingWallCount].setSrcDest_W_H(tile_w, tile_h, tile_w, tile_h);
				closingWall[closingWallCount].setMainTexture(TextureManager::LoadTexture("assets/2.png"));
				closingWall[closingWallCount].setSecondTexture(TextureManager::LoadTexture("assets/clwall.png"));
				closingWallCount++;
				break;
			case 1:
				defoltWall[defoltWallCount].posX = column;
				defoltWall[defoltWallCount].posY = row;
				defoltWall[defoltWallCount].setSrcDest_W_H(tile_w, tile_h, tile_w, tile_h);
				defoltWall[defoltWallCount].setMainTexture(TextureManager::LoadTexture("assets/0.png"));
				defoltWallCount++;
				break;
			case 14:
				enemy[enemyCount].posX = column;
				enemy[enemyCount].posY = row;
				enemy[enemyCount].setSrcDest_W_H(188, 188, tile_w, tile_h);
				enemy[enemyCount].setMainTexture(TextureManager::LoadTexture("assets/enemy.png"));
				enemyCount++;
				break;
			case 9:
				weaponShop[weaponShopCount].posX = column;
				weaponShop[weaponShopCount].posY = row;
				weaponShop[weaponShopCount].setSrcDest_W_H(320, 32, 320, 32);
				weaponShop[weaponShopCount].setType(rand() % weaponSettings.totalWeapons + 1);
				if (weaponShop[weaponShopCount].getType() == 1) {
					weaponShop[weaponShopCount].setWeaponTexture(TextureManager::LoadTexture("assets/w1.png"));
					weaponShop[weaponShopCount].setBulletTexture(TextureManager::LoadTexture("assets/b1.png"));
					weaponShop[weaponShopCount].setParameters(10, 1);
					weaponShop[weaponShopCount].cost = 10;
				}
				else if (weaponShop[weaponShopCount].getType() == 2) {
					weaponShop[weaponShopCount].setWeaponTexture(TextureManager::LoadTexture("assets/w2.png"));
					weaponShop[weaponShopCount].setBulletTexture(TextureManager::LoadTexture("assets/b2.png"));
					weaponShop[weaponShopCount].setParameters(20, 2);
					weaponShop[weaponShopCount].cost = 30;
				}
				else if (weaponShop[weaponShopCount].getType() == 3) {
					weaponShop[weaponShopCount].setWeaponTexture(TextureManager::LoadTexture("assets/w3.png"));
					weaponShop[weaponShopCount].setBulletTexture(TextureManager::LoadTexture("assets/b3.png"));
					weaponShop[weaponShopCount].setParameters(30, 3);
					weaponShop[weaponShopCount].cost = 50;
				}
				weaponShopCount++;
				break;
			default: break;
			}
		}
	}
}

void Map::UpdateMapX(float value)
{
	playerSettings.offsetX += value;
	if (Intersection(1) == true) {
		playerSettings.offsetX -= value;
	}else if (Intersection(10) == true) {
		playerSettings.offsetX -= value;
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
	playerSettings.offsetY += value;
	if (Intersection(1) == true) {
		playerSettings.offsetY -= value;
	}else if (Intersection(10) == true) {
		playerSettings.offsetY -= value;
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
	switch (type) {
	case 10: case 11: case 12: case 13:
		for (int j = 0; j < closingWallCount; j++) {
			if (WIDTH / 2 >= closingWall[j].posX * tile_w + playerSettings.offsetX && WIDTH / 2 <= closingWall[j].posX * tile_w + playerSettings.offsetX + tile_w &&
				HEIGTH / 2 >= closingWall[j].posY * tile_h + playerSettings.offsetY && HEIGTH / 2 <= closingWall[j].posY * tile_h + playerSettings.offsetY + tile_h &&
				closingWall[j].isClos == true) {
				return 1;
			}
		}
	case 1:
		for (int j = 0; j < defoltWallCount; j++) {
			if (WIDTH / 2 >= defoltWall[j].posX * tile_w + playerSettings.offsetX && WIDTH / 2 <= defoltWall[j].posX * tile_w + playerSettings.offsetX + tile_w &&
				HEIGTH / 2 >= defoltWall[j].posY * tile_h + playerSettings.offsetY && HEIGTH / 2 <= defoltWall[j].posY * tile_h + playerSettings.offsetY + tile_h) {
				return 1;
			}
		}
	default:
		return 0;
	}
	return 0;
}

bool Map::IntersectionWithGameObg(int x, int y, int w, int h)
{
	return (WIDTH / 2 >= x && WIDTH / 2 <= x + w && HEIGTH / 2 >= y - h && HEIGTH / 2 <= y +h * 2);
}

bool Map::IntersectionWithGameObg(ClosingWall wall)
{
	switch (wall.type) {
	case 10: return (WIDTH / 2 >= wall.dest.x - 10 && WIDTH / 2 < wall.dest.x + wall.dest.w + 10 && HEIGTH / 2 > wall.dest.y + wall.dest.h + 1 && HEIGTH / 2 < wall.dest.y + wall.dest.h + 10);
	case 11: return (HEIGTH / 2 > wall.dest.y - 10 && HEIGTH / 2 < wall.dest.y + wall.dest.h + 10 && WIDTH / 2 < wall.dest.x - 1 && WIDTH / 2 > wall.dest.x - 10);
	case 12: return (WIDTH / 2 > wall.dest.x - 10 && WIDTH / 2 < wall.dest.x + wall.dest.w + 10 && HEIGTH / 2 < wall.dest.y - 1 && HEIGTH / 2 > wall.dest.y - 10);
	case 13: return (HEIGTH / 2 > wall.dest.y - 10 && HEIGTH / 2 < wall.dest.y + wall.dest.h + 10 && WIDTH / 2 > wall.dest.x + wall.dest.w + 1 && WIDTH / 2 < wall.dest.x + wall.dest.w + 10);
	default: return 0;
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
	int tmpTime = clock();
	if (key.space == true) {
		key.space = false;
		key.timeOfLastspace = tmpTime;
	}
	if (key.keyQ == true) {
		key.keyQ = false;
		key.timeOfLastkeyQ = tmpTime;
	}

	if (tmpTime - key.timeOfLastspace > key.spaceDelay) {
		key.timeOfCurrentspace = tmpTime;
		key.space = arr[SDL_SCANCODE_SPACE];
	}
	if (tmpTime - key.timeOfLastkeyQ > key.keyQDelay) {
		key.timeOfCurrentkeyQ = tmpTime;
		key.keyQ = arr[SDL_SCANCODE_Q];
	}
}

void Map::changingKeyState(bool mouseDown)
{
	key.leftMouseKey = mouseDown;
}

void WeaponSettings::setParameters(WeaponShop& weaponShop)
{
	tmpWeaponTexture = weaponShop.getWeaponTexture();
	tmpBulletTexture = weaponShop.getBulletTexture();
	tmpType = weaponShop.getType();
	tmpBulletDamage = weaponShop.bulletDamage;
	tmpManaCost = weaponShop.manaCost;
	tmpCost = weaponShop.cost;

	weaponShop.cost = cost;
	weaponShop.manaCost = manaCost;
	weaponShop.bulletDamage = bulletDamage;
	weaponShop.setType(type);
	weaponShop.setWeaponTexture(weaponTexture);
	weaponShop.setBulletTexture(bulletTexture);
	
	cost = tmpCost;
	manaCost = tmpManaCost;
	bulletDamage = tmpBulletDamage;
	type = tmpType;
	weaponTexture = tmpWeaponTexture;
	bulletTexture = tmpBulletTexture;
}

void Map::ChestDrow(int row, int column)
{
	TextureManager::Drow(ground_5, src, dest);
	for (int i = 0; i < chestCount; i++) {
		if (chest[i].posX == column && chest[i].posY == row) {
			chest[i].setSrcDest_X_Y(src.x, src.y, dest.x, dest.y);
			if (IntersectionWithGameObg(chest[i].dest.x, chest[i].dest.y, chest[i].dest.w, chest[i].dest.h) == true && chest[i].isOpen() == false) {
				chest[i].getBonus(playerSettings.hp, playerSettings.armor, playerSettings.mana, playerSettings.score);
			}
			TextureManager::Drow(chest[i].getMainTexture(), chest[i].src, chest[i].dest);
			break;
		}
	}
}

void Map::StatueDrow(int row, int column)
{
	TextureManager::Drow(ground_5, src, dest);
	dopDest = { dest.x + tile_w, dest.y, tile_w, tile_h };
	TextureManager::Drow(ground_4, src, dopDest);
	for (int i = 0; i < statueCount; i++) {
		if (statue[i].posX == column && statue[i].posY == row) {
			statue[i].setSrcDest_X_Y(src.x, src.y, dest.x - tile_w, dest.y - tile_h * 2);
			TextureManager::Drow(statue[i].getMainTexture(), statue[i].src, statue[i].dest);
			if (IntersectionWithGameObg(statue[i].dest.x, statue[i].dest.y, statue[i].dest.w , statue[i].dest.h) == true && statue[i].isUsed() == false) {
				//textManager.Drow(textureManager.renderer, u8"всего 15 монет,\nа столько пользы", 300, 100, statue[i].dest.x + 70, statue[i].dest.y - 50, 232, 221, 186);
				if (key.space == true) {
					statue[i].wasUsed = true;
				}
			}
			if (statue[i].wasUsed == true) {
				statue[i].getBonus(playerSettings.hp, playerSettings.armor, playerSettings.mana, playerSettings.score);
			}
			break;
		}
	}
}

void Map::DefoltWallDrow(int row, int column)
{
	for (int i = 0; i < defoltWallCount; i++) {
		if (defoltWall[i].posX == column && defoltWall[i].posY == row) {
			defoltWall[i].setSrcDest_X_Y(src.x, src.y, dest.x, dest.y);
			TextureManager::Drow(defoltWall[0].getMainTexture(), src, dest);
			break;
		}
	}
}

void Map::ClosingWallDrow(int row, int column)
{
	for (int i = 0; i < closingWallCount; i++) {
		if (closingWall[i].posX == column && closingWall[i].posY == row) {
			closingWall[i].setSrcDest_X_Y(src.x, src.y, dest.x, dest.y);
			if (IntersectionWithGameObg(closingWall[i]) == true && closingWall[i].mayClose == true) {
				for (int j = 0; j < closingWallCount; j++) {
					if (abs(closingWall[i].posX - closingWall[j].posX) < 12 && abs(closingWall[i].posY - closingWall[j].posY) < 12) {
						closingWall[j].isClos = true;
						closingWall[j].mayClose = false;
						for (int k = 0; k < enemyCount; k++) {
							if (abs(closingWall[i].posX - enemy[k].posX) < 12 && abs(closingWall[i].posY - enemy[k].posY) < 12) {
								enemy[k].needSpawn = true;
							}
						}
					}
				}
			}
			enemyDie = true;
			for (int j = 0; j < closingWallCount; j++) {
				if (closingWall[j].isClos == true) {
					for (int k = 0; k < enemyCount; k++) {
						if (abs(closingWall[j].posX - enemy[k].posX) < 12 && abs(closingWall[j].posY - enemy[k].posY) < 12 && enemy[k].hasHp == true) {
							enemyDie = false;
						}
					}
				}
			}
			if (enemyDie == true) {
				for (int j = 0; j < closingWallCount; j++) {
					if (abs(closingWall[i].posX - closingWall[j].posX) < 11 && abs(closingWall[i].posY - closingWall[j].posY) < 11) {
						closingWall[j].isClos = false;
					}
				}
				enemyDie = false;
			}
			if (closingWall[i].isClos == false) {
				TextureManager::Drow(closingWall[i].getMainTexture(), closingWall[i].src, closingWall[i].dest);
			}
			else {
				TextureManager::Drow(closingWall[i].getSecondTexture(), closingWall[i].src, closingWall[i].dest);
			}
			break;
		}
	}
}

void Map::EnemyDrow()
{
	for (int i = 0; i < enemyCount; i++) {
		if (enemy[i].needSpawn == true && enemy[i].hasHp == true) {
			TextureManager::InvertDrow_x(enemy[i].getMainTexture(), enemy[i].src, enemy[i].dest, WIDTH / 2);
			dopDest = { enemy[i].dest.x - tile_w / 5, enemy[i].dest.y - 20, tile_w * enemy[i].hp / 100, 10 };
			SDL_SetRenderDrawColor(textureManager.renderer, 255, 0, 0, 0);
			SDL_RenderFillRect(textureManager.renderer, &dopDest);
		}
	}
}

void Map::EnemyCreator(int row, int column)
{
	for (int i = 0; i < enemyCount; i++) {
		if (enemy[i].needSpawn == true && enemy[i].posX == column && enemy[i].posY == row && enemy[i].hasHp == true) {
			enemy[i].islive = true;
			enemy[i].setSrcDest_X_Y(defoltWall, defoltWallCount, closingWall, closingWallCount, src.x, src.y, dest.x, dest.y);
			enemy[i].update(playerSettings.mana, playerSettings.score);
		}
	}
}

void Map::BulletDrow()
{
	for (int i = 0; i < bulletsCount; i++) {
		if (bullets[i].isFly == true) {
			if (bullets[i].intersection(defoltWall, defoltWallCount, closingWall, closingWallCount, enemy, enemyCount, tile_w, tile_h, playerSettings.offsetX, playerSettings.offsetY, weaponSettings.bulletDamage) == true) {
				bullets[i].reset();
			}
		}
		if (bullets[i].isFly == true) {
			bullets[i].fly();
			TextureManager::Drow(weaponSettings.bulletTexture, bullets[i].src, bullets[i].dest);
		}
	}
}

void Map::CharacteristicBoardDrow()
{// доска с характеристиками
	dopSrc = { 0,0, 292,148 };
	dopDest = { 5,2, 270,145 };
	SDL_SetRenderDrawColor(textureManager.renderer, 30, 30, 30, 0);
	SDL_RenderFillRect(textureManager.renderer, &dopDest);
	dopDest = { 0,0, 292, 148 };
	TextureManager::Drow(hpBoard, dopSrc, dopDest);

	dopDest = { 52,16, 212 * playerSettings.hp / 100, 28 };
	SDL_SetRenderDrawColor(textureManager.renderer, 237, 65, 63, 0);
	SDL_RenderFillRect(textureManager.renderer, &dopDest);
	textManager.Drow(textureManager.renderer, to_string(playerSettings.hp), 52, 26, 138, 20, 255, 255, 255);


	dopDest = { 52, 56, 212 * playerSettings.armor / 100,28 };
	SDL_SetRenderDrawColor(textureManager.renderer, 136, 142, 140, 0);
	SDL_RenderFillRect(textureManager.renderer, &dopDest);
	textManager.Drow(textureManager.renderer, to_string(playerSettings.armor), 52, 26, 138, 60, 255, (playerSettings.armor > 0) ? 255 : 33, (playerSettings.armor > 0) ? 255 : 33);

	dopDest = { 52, 96, 212 * playerSettings.mana / 100,28 };
	SDL_SetRenderDrawColor(textureManager.renderer, 15, 123, 178, 0);
	SDL_RenderFillRect(textureManager.renderer, &dopDest);
	textManager.Drow(textureManager.renderer, to_string(playerSettings.mana), 52, 26, 138, 100, 255, (playerSettings.mana > 0) ? 255 : 33, (playerSettings.mana > 0) ? 255 : 33);
}

void Map::BulletCreator()
{
	if (key.leftMouseKey == true) {
		weaponSettings.timeOfCurrentBullet = clock();
		for (int i = 0; i < bulletsCount; i++) {
			if (bullets[i].isFly == false && weaponSettings.timeOfCurrentBullet - weaponSettings.timeOfLastBullet > weaponSettings.bulletDelay &&
				playerSettings.mana >= weaponSettings.manaCost) {
				playerSettings.mana -= weaponSettings.manaCost;
				bullets[i].setAngl(key.mousePosX, key.mousePosY, WIDTH, HEIGTH, weaponSettings.bulletOffsetRadius);
				weaponSettings.timeOfLastBullet = clock();
				break;
			}
		}
	}
}

void Map::CoinCounterDrow()
{
	// монеты
	dopDest = { 10, 170, 40, 40 };
	dopSrc = { 0, 0, 56, 80 };
	TextureManager::Drow(coin, dopSrc, dopDest);
	textManager.Drow(textureManager.renderer, to_string(playerSettings.score), 50, 50, 80, 170, 232, 221, 186);
}

void Map::PlayerDrow()
{
	dopSrc = { 0,0, 160,16 };
	dopDest = { WIDTH / 2 - 160, HEIGTH / 2 - 16, 320, 32 };
	weaponSettings.weaponAngle = -int(atan2f(float(key.mousePosX - WIDTH / 2), float(key.mousePosY - HEIGTH / 2)) * 180 / M_PI - 90) % 360;
	if (weaponSettings.weaponAngle < 0) {
		weaponSettings.weaponAngle = 270 + weaponSettings.weaponAngle + 90;
	}
	TextureManager::Drow(weaponSettings.weaponTexture, dopSrc, dopDest, weaponSettings.weaponAngle);

	SDL_SetRenderDrawColor(textureManager.renderer, 255, 0, 0, 0);
	dopDest = { WIDTH / 2, HEIGTH / 2, 1, 1 };
	SDL_RenderFillRect(textureManager.renderer, &dopDest);
}

void Map::CloseFightUpdate()
{
	if (key.space == true && enemyDie == false) {
		for (int i = 0; i < enemyCount; i++) {
			if (enemy[i].islive == true && IntersectionWithGameObg(enemy[i].dest.x, enemy[i].dest.y, enemy[i].dest.w, enemy[i].dest.h) == true) {
				if (enemy[i].hp > 0) {
					enemy[i].hp -= playerSettings.damage;
				}
				break;
			}
		}
	}
}

void Map::WeaponDrow(int row, int column)
{
	TextureManager::Drow(ground_5, src, dest);
	dopDest = { dest.x + tile_w, dest.y, tile_w, tile_h };
	TextureManager::Drow(ground_4, src, dopDest);
	for (int i = 0; i < weaponShopCount; i++) {
		if (weaponShop[i].posX == column && weaponShop[i].posY == row) {
			weaponShop[i].setSrcDest_X_Y(src.x, src.y, dest.x - weaponShop[i].dest.w / 2, dest.y);
			TextureManager::Drow(weaponShop[i].getWeaponTexture(), weaponShop[i].src, weaponShop[i].dest);
			if (IntersectionWithGameObg(weaponShop[i].dest.x, weaponShop[i].dest.y, weaponShop[i].dest.w, weaponShop[i].dest.h) == true) {
				if (weaponShop[i].isBuy == false) {
					textManager.Drow(textureManager.renderer, u8"цена: " + to_string(weaponShop[i].cost), 120, 25, weaponShop[i].dest.x + weaponShop[i].dest.w / 2, weaponShop[i].dest.y - weaponShop[i].dest.h * 2, 232, 221, 186);
				}
				textManager.Drow(textureManager.renderer, u8"Dm: " + to_string(int(weaponShop[i].bulletDamage)) + u8" M: " + to_string(weaponShop[i].manaCost), 120, 25, weaponShop[i].dest.x + weaponShop[i].dest.w / 2, weaponShop[i].dest.y - weaponShop[i].dest.h, 232, 221, 186);
				if (key.space == true) {
					if (weaponShop[i].alrBuy == false && playerSettings.score >= weaponShop[i].cost) {
						playerSettings.score -= weaponShop[i].cost;
						weaponShop[i].alrBuy = true;
						weaponShop[i].isBuy = true;
					}
					if (weaponShop[i].isBuy == true) {
						weaponSettings.setParameters(weaponShop[i]);
					}
				}
			}
			break;
		}
	}
}