#include "Map.h"

SDL_Renderer* TextureManager::renderer = nullptr;

Map::Map()
{
	weaponSettings.bulletTexture = TextureManager::LoadTexture("assets/b1.png");
	weaponSettings.weaponTexture = TextureManager::LoadTexture("assets/w1.png");

	playerSettings.playerTexture = TextureManager::LoadTexture("assets/b2.png");

	ground_1 = TextureManager::LoadTexture("assets/1.png");
	ground_2 = TextureManager::LoadTexture("assets/2.png");
	ground_3 = TextureManager::LoadTexture("assets/3.png");
	ground_4 = TextureManager::LoadTexture("assets/4.png");
	ground_5 = TextureManager::LoadTexture("assets/5.png");
	coin = TextureManager::LoadTexture("assets/9.png");
	hpBoard = TextureManager::LoadTexture("assets/hp.png");
	enemyTx = TextureManager::LoadTexture("assets/enemy.png");
	chestClose = TextureManager::LoadTexture("assets/6.png");
	chestOpen = TextureManager::LoadTexture("assets/7.png");
	statue_1 = TextureManager::LoadTexture("assets/st1.png");
	statue_2 = TextureManager::LoadTexture("assets/st2.png");
	clwall = TextureManager::LoadTexture("assets/clwall.png");
	dtWall = TextureManager::LoadTexture("assets/0.png");

	weapon_1 = TextureManager::LoadTexture("assets/w1.png");
	bullet_1 = TextureManager::LoadTexture("assets/b1.png");

	weapon_2 = TextureManager::LoadTexture("assets/w2.png");
	bullet_2 = TextureManager::LoadTexture("assets/b2.png");

	weapon_3 = TextureManager::LoadTexture("assets/w3.png");
	bullet_3 = TextureManager::LoadTexture("assets/b3.png");

	for (int i = 0; i < 8; i++) {
		path = "assets/portal2/" + to_string(i) + ".png";
		portal[i] = TextureManager::LoadTexture(path.c_str());
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
				//case 14: TextureManager::Drow(ground_5, src, dest); break;
				case 15: PortalBetweenMapsDrow(row, column); break;
				case 17: SpikesDrow(row, column); break;
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

	PlayerDrow();
}

void Map::RoomCreater(bool isFirstRoom)
{
	if (isFirstRoom == true) {
		lvl = 1;
	}
	playerSettings.offsetX = WIDTH / 2.0;
	playerSettings.offsetY = HEIGTH / 2.0;
	playerSettings.dest.x = WIDTH / 2 - playerSettings.dest.w / 2;
	playerSettings.dest.y = HEIGTH / 2 - playerSettings.dest.h / 2;

	for (_row = 0; _row < lvl1_h; _row++) {
		for (_column = 0; _column < lvl1_w; _column++) {
			lvl1[_row][_column] = 0;
		}
	}

	lvlPath = "maps/" + to_string(lvl) + ".txt";
	tmpString = "0";
	ifstream file(lvlPath);

	if (file.is_open()) {
		for (_row = 0; _row < lvl1_h; _row++) {
			for (_column = 0; _column < lvl1_w; _column++) {
				file.getline(str, 3, ',');
				tmpString = str;
				lvl1[_row][_column] = atoi(tmpString.c_str());
			}
		}
		file.close();
		if (lvl < 2) {
			lvl++;
		}
	}

	for (_row = 0; _row < lvl1_h; _row++) {
		for (_column = 0; _column < lvl1_w; _column++) {
			switch (lvl1[_row][_column]) {
			case 7: chestCount++; break;
			case 8: statueCount++; break;
			case 10:case 11:case 12:case 13: closingWallCount++; break;
			case 1: defoltWallCount++; break;
			case 14: enemyCount++; break;
			case 9: weaponShopCount++; break;
			case 17: spikesCount++; break;
			default: break;
			}

		}
	}

	delete[] chest;
	delete[] statue;
	delete[] closingWall;
	delete[] bullets;
	delete[] defoltWall;
	delete[] enemy;
	delete[] weaponShop;
	delete[] spikes;

	chest = new Chest[chestCount];
	statue = new Statue[statueCount];
	closingWall = new ClosingWall[closingWallCount];
	bullets = new Bullets[bulletsCount];
	defoltWall = new GameObgect[defoltWallCount];
	enemy = new Enemy[enemyCount];
	weaponShop = new WeaponShop[weaponShopCount];
	spikes = new Spikes[spikesCount];
	chestCount = 0;
	statueCount = 0;
	closingWallCount = 0;
	defoltWallCount = 0;
	enemyCount = 0;
	weaponShopCount = 0;
	spikesCount = 0;

	for (_row = 0; _row < lvl1_h; _row++) {
		for (_column = 0; _column < lvl1_w; _column++) {
			switch (lvl1[_row][_column]) {
			case 7:
				chest[chestCount].posX = _column;
				chest[chestCount].posY = _row;
				chest[chestCount].setSrcDest_W_H(tile_w, tile_h, tile_w, tile_h);
				chest[chestCount].setMainTexture(chestClose);
				chest[chestCount].setSecondTexture(chestOpen);
				chestCount++;
				break;
			case 8:
				statue[statueCount].posX = _column;
				statue[statueCount].posY = _row;
				statue[statueCount].setSrcDest_W_H(288, 320, tile_w * 3, tile_h * 3);
				statue[statueCount].setType((rand() % 3));
				if (statue[statueCount].getType() == 1) {
					statue[statueCount].setMainTexture(statue_1);
				}
				else {
					statue[statueCount].setMainTexture(statue_2);
				}
				statueCount++;
				break;
			case 10: case 11: case 12: case 13:
				closingWall[closingWallCount].posX = _column;
				closingWall[closingWallCount].posY = _row;
				closingWall[closingWallCount].type = lvl1[_row][_column];
				closingWall[closingWallCount].setSrcDest_W_H(tile_w, tile_h, tile_w, tile_h);
				closingWall[closingWallCount].setMainTexture(ground_2);
				closingWall[closingWallCount].setSecondTexture(clwall);
				closingWallCount++;
				break;
			case 1:
				defoltWall[defoltWallCount].posX = _column;
				defoltWall[defoltWallCount].posY = _row;
				defoltWall[defoltWallCount].setSrcDest_W_H(tile_w, tile_h, tile_w, tile_h);
				defoltWall[defoltWallCount].setMainTexture(dtWall);
				defoltWallCount++;
				break;
			case 15:
				portalBetweenMaps.posX = _column;
				portalBetweenMaps.posY = _row;
				portalBetweenMaps.setSrcDest_W_H(768, 720, tile_w*4, tile_h*4);
				for (int i = 0; i < 8; i++) {
					portalBetweenMaps.tx[i] = portal[i];
				}
				break;
			case 16:
				playerSettings.offsetX -= _column * tile_w + tile_w / 2;
				playerSettings.offsetY -= _row * tile_h + tile_h / 2;
				break;
			case 14:
				enemy[enemyCount].posX = _column;
				enemy[enemyCount].posY = _row;
				enemy[enemyCount].setScreen_W_H(WIDTH, HEIGTH);
				enemy[enemyCount].setSrcDest_W_H(188, 188, tile_w, tile_h);
				enemy[enemyCount].setMainTexture(enemyTx);
				enemyCount++;
				break;
			case 9:
				weaponShop[weaponShopCount].posX = _column;
				weaponShop[weaponShopCount].posY = _row;
				weaponShop[weaponShopCount].setSrcDest_W_H(320, 32, 320, 32);
				weaponShop[weaponShopCount].setType(rand() % weaponSettings.totalWeapons + 1);
				if (weaponShop[weaponShopCount].getType() == 1) {
					weaponShop[weaponShopCount].setWeaponTexture(weapon_1);
					weaponShop[weaponShopCount].setBulletTexture(bullet_1);
					weaponShop[weaponShopCount].setParameters(10, 1);
					weaponShop[weaponShopCount].cost = 10;
				}
				else if (weaponShop[weaponShopCount].getType() == 2) {
					weaponShop[weaponShopCount].setWeaponTexture(weapon_2);
					weaponShop[weaponShopCount].setBulletTexture(bullet_2);
					weaponShop[weaponShopCount].setParameters(20, 2);
					weaponShop[weaponShopCount].cost = 30;
				}
				else if (weaponShop[weaponShopCount].getType() == 3) {
					weaponShop[weaponShopCount].setWeaponTexture(weapon_3);
					weaponShop[weaponShopCount].setBulletTexture(bullet_3);
					weaponShop[weaponShopCount].setParameters(30, 3);
					weaponShop[weaponShopCount].cost = 50;
				}
				weaponShopCount++;
				break;
			case 17:
				spikes[spikesCount].posX = _column;
				spikes[spikesCount].posY = _row;
				spikes[spikesCount].setSrcDest_W_H(tile_w, tile_h, tile_w, tile_h);
				spikes[spikesCount].setMainTexture(chestClose);
				spikes[spikesCount].setSecondTexture(chestOpen);
				spikesCount++;
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
		for (int i = 0; i < enemyCount; i++) {
			if (enemy[i].islive == true) {
				for (int j = 0; j < enemy[i].bulletsCount; j++) {
					if (enemy[i].bl[j].isFly == true) {
						enemy[i].bl[j].offX += value;
					}
				}
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
		for (int i = 0; i < enemyCount; i++) {
			if (enemy[i].islive == true) {
				for (int j = 0; j < enemy[i].bulletsCount; j++) {
					if (enemy[i].bl[j].isFly == true) {
						enemy[i].bl[j].offY += value;
					}
				}
			}
		}
	}
}

bool Map::Intersection(int type)
{
	switch (type) {
	case 10: case 11: case 12: case 13:
		for (int j = 0; j < closingWallCount; j++) {
			if (WIDTH / 2 + playerSettings.dest.w / 2 >= closingWall[j].posX * tile_w + playerSettings.offsetX && WIDTH / 2 - playerSettings.dest.w / 2 <= closingWall[j].posX * tile_w + playerSettings.offsetX + tile_w &&
				HEIGTH / 2 + playerSettings.dest.h/2 >= closingWall[j].posY * tile_h + playerSettings.offsetY && HEIGTH / 2 - playerSettings.dest.h/2 <= closingWall[j].posY * tile_h + playerSettings.offsetY + tile_h &&
				closingWall[j].isClos == true) {
				return 1;
			}
		}
	case 1:
		for (int j = 0; j < defoltWallCount; j++) {
			if (WIDTH / 2 + playerSettings.dest.w / 2 >= defoltWall[j].posX * tile_w + playerSettings.offsetX && WIDTH / 2 - playerSettings.dest.w / 2 <= defoltWall[j].posX * tile_w + playerSettings.offsetX + tile_w &&
				HEIGTH / 2 + playerSettings.dest.h / 2 >= defoltWall[j].posY * tile_h + playerSettings.offsetY && HEIGTH / 2 - playerSettings.dest.h / 2 <= defoltWall[j].posY * tile_h + playerSettings.offsetY + tile_h) {
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
	return (WIDTH / 2 - playerSettings.dest.w / 2 > x - playerSettings.dest.w &&
		WIDTH / 2 - playerSettings.dest.w / 2 < x + playerSettings.dest.w &&
		HEIGTH / 2 - playerSettings.dest.h / 2 > y - playerSettings.dest.h &&
		HEIGTH / 2 - playerSettings.dest.h / 2 < y + playerSettings.dest.h);
}

bool Map::IntersectionWithGameObg(ClosingWall wall)
{
	switch (wall.type) {
	case 10: return (WIDTH / 2 >= wall.dest.x - 10 && WIDTH / 2 < wall.dest.x + wall.dest.w + 10 && HEIGTH / 2 - playerSettings.dest.h/2 > wall.dest.y + wall.dest.h + 1 && HEIGTH / 2 - playerSettings.dest.h/2 < wall.dest.y + wall.dest.h + 10);
	case 11: return (HEIGTH / 2 > wall.dest.y - 10 && HEIGTH / 2 < wall.dest.y + wall.dest.h + 10 && WIDTH / 2 + playerSettings.dest.w / 2 < wall.dest.x - 1 && WIDTH / 2 + playerSettings.dest.w / 2 > wall.dest.x - 10);
	case 12: return (WIDTH / 2 > wall.dest.x - 10 && WIDTH / 2 < wall.dest.x + wall.dest.w + 10 && HEIGTH / 2 + playerSettings.dest.h / 2 < wall.dest.y - 1 && HEIGTH / 2 + playerSettings.dest.h / 2 > wall.dest.y - 10);
	case 13: return (HEIGTH / 2  > wall.dest.y - 10 && HEIGTH / 2 < wall.dest.y + wall.dest.h + 10 && WIDTH / 2 - playerSettings.dest.w/2 > wall.dest.x + wall.dest.w + 1 && WIDTH / 2 - playerSettings.dest.w/2 < wall.dest.x + wall.dest.w + 10);
	default: return 0;
	}
	return 0;
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

void Map::UpdateSetiings()
{
	settings.score = settings.score;
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
	//TextureManager::Drow(ground_5, src, dest);
	for (int i = 0; i < chestCount; i++) {
		if (chest[i].posX == column && chest[i].posY == row) {
			chest[i].setSrcDest_X_Y(src.x, src.y, dest.x, dest.y);
			if (IntersectionWithGameObg(chest[i].dest.x, chest[i].dest.y, chest[i].dest.w, chest[i].dest.h) == true && chest[i].isOpen() == false) {
				chest[i].getBonus(settings.hp, settings.armor, settings.mana, settings.score);
			}
			TextureManager::Drow(chest[i].getMainTexture(), chest[i].src, chest[i].dest);
			break;
		}
	}
}

void Map::StatueDrow(int row, int column)
{
	//TextureManager::Drow(ground_5, src, dest);
	//dopDest = { dest.x + tile_w, dest.y, tile_w, tile_h };
	//TextureManager::Drow(ground_4, src, dopDest);
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
				statue[i].getBonus(settings.hp, settings.armor, settings.mana, settings.score);
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
				//TextureManager::Drow(closingWall[i].getMainTexture(), closingWall[i].src, closingWall[i].dest);
			}
			else {
				TextureManager::Drow(closingWall[i].getSecondTexture(), closingWall[i].src, closingWall[i].dest);
			}
			break;
		}
	}
}

void Map::PortalBetweenMapsDrow(int row, int column)
{
	if (portalBetweenMaps.posX == column && portalBetweenMaps.posY == row) {
		portalBetweenMaps.setSrcDest_X_Y(src.x, src.y, dest.x, dest.y);
		TextureManager::Drow(portalBetweenMaps.tx[portalBetweenMaps.animFrame], portalBetweenMaps.src, portalBetweenMaps.dest);
		portalBetweenMaps.animFrameUpdate();
		if (IntersectionWithGameObg(portalBetweenMaps.dest.x, portalBetweenMaps.dest.y, portalBetweenMaps.dest.w, portalBetweenMaps.dest.h) == true) {
			textManager.Drow(textureManager.renderer, u8"Q для перехода", 17*14, 28, portalBetweenMaps.dest.x - (17 * 14 - portalBetweenMaps.dest.w) / 2, portalBetweenMaps.dest.y, 232, 221, 186);
			if (key.keyQ == true) {
				RoomCreater(false);
			}
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
		if (enemy[i].islive == true) {
			for (int j = 0; j < enemy[i].bulletsCount; j++) {

				if (enemy[i].bl[j].isFly == true) {
					if (enemy[i].bl[j].intersection(defoltWall, defoltWallCount, closingWall, closingWallCount, tile_w, tile_h, playerSettings.offsetX, playerSettings.offsetY, weaponSettings.bulletDamage, playerSettings.dest) == true) {
						if (enemy[i].bl[j].intersectionType == 2) {
							if (settings.armor > 0) {
								settings.armor -= enemy[i].damage;
								if (settings.armor < 0) {
									settings.armor = 0;
								}
							}
							else if (settings.hp > 0) {
								settings.hp -= enemy[i].damage;
								if (settings.hp < 0) {
									settings.hp = 0;
									/*
									* 
									* 
									* 
									* 
									* 
									* 
									// тут игрока убивают
									* 
									* 
									* 
									* 
									* 
									* 
									*/
								}
							}
							
						}
						enemy[i].bl[j].reset();
					}
				}
				if (enemy[i].bl[j].isFly == true) {
					enemy[i].bl[j].fly(enemy[i].dest.x, enemy[i].dest.y);
					TextureManager::Drow(weaponSettings.bulletTexture, enemy[i].bl[j].src, enemy[i].bl[j].dest);
				}
			}
		}
	}
}

void Map::EnemyCreator(int row, int column)
{
	for (int i = 0; i < enemyCount; i++) {
		if (enemy[i].needSpawn == true && enemy[i].posX == column && enemy[i].posY == row && enemy[i].hasHp == true) {
			enemy[i].islive = true;
			enemy[i].setSrcDest_X_Y(defoltWall, defoltWallCount, closingWall, closingWallCount, src.x, src.y, dest.x, dest.y);
			enemy[i].update(settings.mana, settings.score);
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

	dopDest = { 52,16, 212 * settings.hp / 100, 28 };
	SDL_SetRenderDrawColor(textureManager.renderer, 237, 65, 63, 0);
	SDL_RenderFillRect(textureManager.renderer, &dopDest);
	textManager.Drow(textureManager.renderer, to_string(settings.hp), 52, 26, 138, 20, 255, 255, 255);


	dopDest = { 52, 56, 212 * settings.armor / 100,28 };
	SDL_SetRenderDrawColor(textureManager.renderer, 136, 142, 140, 0);
	SDL_RenderFillRect(textureManager.renderer, &dopDest);
	textManager.Drow(textureManager.renderer, to_string(settings.armor), 52, 26, 138, 60, 255, (settings.armor > 0) ? 255 : 33, (settings.armor > 0) ? 255 : 33);

	dopDest = { 52, 96, 212 * settings.mana / 100,28 };
	SDL_SetRenderDrawColor(textureManager.renderer, 15, 123, 178, 0);
	SDL_RenderFillRect(textureManager.renderer, &dopDest);
	textManager.Drow(textureManager.renderer, to_string(settings.mana), 52, 26, 138, 100, 255, (settings.mana > 0) ? 255 : 33, (settings.mana > 0) ? 255 : 33);
}

void Map::BulletCreator()
{
	if (key.leftMouseKey == true) {
		weaponSettings.timeOfCurrentBullet = clock();
		for (int i = 0; i < bulletsCount; i++) {
			if (bullets[i].isFly == false && weaponSettings.timeOfCurrentBullet - weaponSettings.timeOfLastBullet > weaponSettings.bulletDelay &&
				settings.mana >= weaponSettings.manaCost) {
				settings.mana -= weaponSettings.manaCost;
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
	textManager.Drow(textureManager.renderer, to_string(settings.score), 50, 50, 80, 170, 232, 221, 186);
}

void Map::PlayerDrow()
{
	dopSrc = { 0,0, 160,16 };
	dopDest = { WIDTH / 2 - 160, HEIGTH / 2 - 16, 320, 32 };
	weaponSettings.weaponAngle = -int(atan2f(float(key.mousePosX - WIDTH / 2), float(key.mousePosY - HEIGTH / 2)) * 180 / M_PI - 90) % 360;
	if (weaponSettings.weaponAngle < 0) {
		weaponSettings.weaponAngle = 270 + weaponSettings.weaponAngle + 90;
	}
	TextureManager::Drow(playerSettings.playerTexture, playerSettings.src, playerSettings.dest);
	TextureManager::Drow(weaponSettings.weaponTexture, dopSrc, dopDest, weaponSettings.weaponAngle);
}

void Map::SpikesDrow(int row, int column)
{
	spikeCurrentTime = clock();
	if (spikeCurrentTime - spikeLastTime >= spikesDelay) {
		spikeLastTime = spikeCurrentTime;
		for (int i = 0; i < spikesCount; i++) {
			spikes[i].changeState();
		}
	}
	for (int i = 0; i < spikesCount; i++) {
		if (spikes[i].posX == column && spikes[i].posY == row) {
			spikes[i].setSrcDest_X_Y(src.x, src.y, dest.x, dest.y);
			TextureManager::Drow(spikes[i].getMainTexture(), spikes[i].src, spikes[i].dest);
		}
		if (IntersectionWithGameObg(spikes[i].dest.x, spikes[i].dest.y, spikes[i].dest.w, spikes[i].dest.h) == true && spikes[i].IsRaised() == true && spikes[i].used == false) {
			spikes[i].used = true;
			settings.hp -= 10;
			if (settings.hp < 0) {
				settings.hp = 0;
			}
		}
	}
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

void Map::Update_W_H(int w, int h) 
{
	if (tmpWIDTH == NULL && tmpHEIGTH == NULL) {
		tmpWIDTH = w;
		tmpHEIGTH = h;
		WIDTH = w;
		HEIGTH = h;
		playerSettings.offsetX -= (tmpWIDTH - w) / 4;
		playerSettings.offsetY -= (tmpHEIGTH - h) / 4;
		playerSettings.dest.x = WIDTH / 2 - playerSettings.dest.w / 2;
		playerSettings.dest.y = HEIGTH / 2 - playerSettings.dest.h / 2;
	}
	if (tmpWIDTH != w || tmpHEIGTH != h) {
		playerSettings.offsetX -= (tmpWIDTH - w) / 4;
		playerSettings.offsetY -= (tmpHEIGTH - h)/4;
		playerSettings.dest.x = WIDTH / 2 - playerSettings.dest.w / 2;
		playerSettings.dest.y = HEIGTH / 2 - playerSettings.dest.h / 2;
		tmpWIDTH = WIDTH;
		tmpHEIGTH = HEIGTH;
		WIDTH = w;
		HEIGTH = h;
		for (int i = 0; i < enemyCount; i++) {
			if (enemy[i].hasHp == true) {
				enemy[i].setScreen_W_H(w, h);
				enemy[i].update(settings.mana, settings.score);
			}
		}
	}
}

void Map::WeaponDrow(int row, int column)
{
	//TextureManager::Drow(ground_5, src, dest);
	//dopDest = { dest.x + tile_w, dest.y, tile_w, tile_h };
	//TextureManager::Drow(ground_4, src, dopDest);
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
					if (weaponShop[i].alrBuy == false && settings.score >= weaponShop[i].cost) {
						settings.score -= weaponShop[i].cost;
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