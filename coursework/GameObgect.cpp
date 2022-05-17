#include "GameObgect.h"

void GameObgect::setMainTexture(SDL_Texture* value)
{
	maintx = value;
}

void GameObgect::setSecondTexture(SDL_Texture* value)
{
	second = value;
}

SDL_Texture* GameObgect::getMainTexture()
{
	return maintx;
}

SDL_Texture* GameObgect::getSecondTexture()
{
	return second;
}

void GameObgect::setSrcDest_W_H(int src_w, int src_h, int dest_w, int dest_h)
{
	src.w = src_w;
	src.h = src_h;
	dest.w = dest_w;
	dest.h = dest_h;
}

void GameObgect::setSrcDest_X_Y(int src_x, int src_y, int dest_x, int dest_y)
{
	src.x = src_x;
	src.y = src_y;
	dest.x = dest_x;
	dest.y = dest_y;
}

void GameObgect::setSrc(int w, int h, int x, int y)
{
	src.w = w;
	src.h = h;
	src.x = x;
	src.y = y;
}

void GameObgect::setDest(int w, int h, int x, int y)
{
	dest.w = w;
	dest.h = h;
	dest.x = x;
	dest.y = y;
}

void GameObgect::chengeMainTexture()
{
	maintx = second;
	playerIsClose = true;
}

Chest::Chest()
{
	int flag = rand() % 2;
	if (flag == 0) {
		hpBust = rand() % 2;
	}

	flag = rand() % 2;
	if (flag == 0) {
		armorBust += rand() % 15;
	}

	flag = rand() % 2;
	if (flag == 0) {
		manaBust += rand() % 15;
	}

	coinsBust = rand() % 2 + 1;
}

void Chest::setSrcDest_X_Y(int src_x, int src_y, int dest_x, int dest_y)
{
	if (open == true) {
		dest.x = dest_x - dest.w / 6;
	}
	else {
		dest.x = dest_x;
	}
	src.x = src_x;
	src.y = src_y;
	dest.y = dest_y;
}

bool Chest::isOpen()
{
	return open;
}

void Chest::getBonus(int& hp, int& armor, int& mana, int& coins)
{
	if (stateIsChanged == false) {
		chengeMainTexture();
		dest.w = dest.w + int(dest.w / 2.1);
		stateIsChanged = true;
	}

	if ((hpBust != 0 || armorBust != 0 || manaBust != 0 || coinsBust != 0) && open == false) {
		if (hpBust != 0) {
			if (hp < 100) {
				hp++;
			}
			hpBust--;
		}
		if (armorBust != 0) {
			if (armor < 100) {
				armor++;
			}
			armorBust--;
		}
		if (manaBust != 0) {
			if (mana < 100) {
				mana++;
			}
			manaBust--;
		}
		if (coinsBust != 0) {
			coins++;
			coinsBust--;
		}
	}
	else {
		open = true;
	}
}

Statue::Statue()
{
	int flag = rand() % 2;

	flag = rand() % 2;
	if (flag == 0) {
		hpBust = rand() % 11 + 1;
	}

	flag = rand() % 2;
	if (flag == 0) {
		armorBust += rand() % 21 + 10;
	}

	flag = rand() % 2;
	if (flag == 0) {
		manaBust += rand() % 21 + 10;
	}
}

void Statue::setSrcDest_X_Y(int src_x, int src_y, int dest_x, int dest_y)
{
	dest.x = dest_x;
	src.x = src_x;
	src.y = src_y;
	dest.y = dest_y;
}

bool Statue::isUsed()
{
	return used;
}

void Statue::getBonus(int& hp, int& armor, int& mana, int& coins)
{
	if (coins >= 15 && used == false) {
		used = true;
	}
	if (used == true) {
		if (hpBust != 0 || armorBust != 0 || manaBust != 0 || coinsBust != 0) {
			if (hpBust != 0) {
				if (hp < 100) {
					hp++;
				}
				hpBust--;
			}
			if (armorBust != 0) {
				if (armor < 100) {
					armor++;
				}
				armorBust--;
			}
			if (manaBust != 0) {
				if (mana < 100) {
					mana++;
				}
				manaBust--;
			}
			if (coinsBust != 0) {
				if (coins > 0) {
					coins--;
					coinsBust--;
				}
			}
		}
		else {
			wasUsed = false;
		}
	}
}

int Statue::getType()
{
	return type;
}

void Statue::setType(int type)
{
	this->type = type;
}

Enemy::Enemy()
{
	manaPlayerBonus = rand() % 11 + 1;
	scorePlayerBonus = rand() % 2 + 1;
}

void Enemy::update(int& manaPlayer, int& scorePlayer)
{
	timeOfCurrentBullet = clock();
	for (int i = 0; i < bulletsCount; i++) {
		if (bl[i].isFly == false && timeOfCurrentBullet - timeOfLastBullet > bulletDelay) {
			bl[i].setAngl(dest.x, dest.y, ScreenW, ScreenH, 20, dest.x, dest.y);
			timeOfLastBullet = clock();
			break;
		}
	}
	if (hp <= 0) {
		hasHp = false;
		islive = false;
		scorePlayer += scorePlayerBonus;
	}
}

void Enemy::setSrcDest_X_Y(GameObgect* defoltWall, int defoltWallCount, ClosingWall* closingWall, int closingWallCount, int src_x, int src_y, int dest_x, int dest_y)
{
	intersection(defoltWall, defoltWallCount, closingWall, closingWallCount, dest_x, dest_y);
	dest.x = dest_x + pathX;
	dest.y = dest_y + pathY;
	src.x = src_x;
	src.y = src_y;
}

void Enemy::setScreen_W_H(int w, int h)
{
	ScreenW = w;
	ScreenH = h;
}

void Enemy::reset()
{
}

void Enemy::intersection(GameObgect* defoltWall, int defoltWallCount, ClosingWall* closingWall, int closingWallCount, int dest_x, int dest_y)
{
	if (pathLengthX == 0) {
		pathLengthX = rand() % 1000;
		if (rand() % 2 == 0) {
			pathLengthX *= -1;
		}
	}
	if (pathLengthY == 0) {
		pathLengthY = rand() % 1000;
		if (rand() % 2 == 0) {
			pathLengthY *= -1;
		}
	}

	if (pathLengthX > 0) {
		pathX++;
		pathLengthX--;
		if (intersection(defoltWall, defoltWallCount, dest_x, dest_y) == true || intersection(closingWall, closingWallCount, dest_x, dest_y) == true) {
			pathLengthX *= -1;
			pathX--;
		}
	}
	else {
		pathX--;
		pathLengthX++;
		if (intersection(defoltWall, defoltWallCount, dest_x, dest_y) == true || intersection(closingWall, closingWallCount, dest_x, dest_y) == true) {
			pathLengthX *= -1;
			pathX++;
		}
	}
	if (pathLengthY > 0) {
		pathY++;
		pathLengthY--;
		if (intersection(defoltWall, defoltWallCount, dest_x, dest_y) == true || intersection(closingWall, closingWallCount, dest_x, dest_y) == true) {
			pathLengthY *= -1;
			pathY--;
		}
	}
	else {
		pathY--;
		pathLengthY++;
		if (intersection(defoltWall, defoltWallCount, dest_x, dest_y) == true || intersection(closingWall, closingWallCount, dest_x, dest_y) == true) {
			pathLengthY *= -1;
			pathY++;
		}
	}
}

bool Enemy::intersection(GameObgect* defoltWall, int Count, int dest_x, int dest_y)
{
	for (int j = 0; j < Count; j++) {
		if (dest_x + pathX > defoltWall[j].dest.x - dest.w &&
			dest_x + pathX < defoltWall[j].dest.x + defoltWall[j].dest.w &&
			dest_y + pathY > defoltWall[j].dest.y - dest.h &&
			dest_y + pathY < defoltWall[j].dest.y + defoltWall[j].dest.h) {
			return 1;
		}
	}
	return 0;
}

bool Enemy::intersection(ClosingWall* closingWall, int Count, int dest_x, int dest_y)
{
	for (int j = 0; j < Count; j++) {
		if (dest_x + pathX > closingWall[j].dest.x - dest.w &&
			dest_x + pathX < closingWall[j].dest.x + closingWall[j].dest.w &&
			dest_y + pathY > closingWall[j].dest.y - dest.h &&
			dest_y + pathY < closingWall[j].dest.y + closingWall[j].dest.h) {
			return 1;
		}
	}
	return 0;
}

void WeaponShop::setWeaponTexture(SDL_Texture* value)
{
	weaponTexture = value;
}

void WeaponShop::setBulletTexture(SDL_Texture* value)
{
	bulletTexture = value;
}

void WeaponShop::setType(int type)
{
	this->type = type;
}

void WeaponShop::setParameters(float bulletDamage, int manaCost)
{
	this->bulletDamage = bulletDamage;
	this->manaCost = manaCost;
}

int WeaponShop::getType()
{
	return type;
}

SDL_Texture* WeaponShop::getWeaponTexture()
{
	return weaponTexture;
}

SDL_Texture* WeaponShop::getBulletTexture()
{
	return bulletTexture;
}

void PortalBetweenMaps::animFrameUpdate()
{
	dopFrame++;
	if (dopFrame % animFrameDelay == 0) {
		animFrame++;
		if (animFrame == animFrameCount) {
			animFrame = 0;
			dopFrame = 0;
		}
	}
}



Bullets::Bullets()
{
	src.x = 0;
	src.y = 0;
	src.w = 60;
	src.h = 60;
	dest.w = 20;
	dest.h = 20;
}

void Bullets::fly()
{
	Bx = screanW / 2 + (dist + offsetRadius) * cosVal + offX;
	By = screanH / 2 + (dist + offsetRadius) * -sinVal + offY;
	dest.x = Bx;
	dest.y = By;
	dist += 6.2f;
}

void Bullets::fly(int enX, int enY)
{
	if (flag == false) {
		tmpBx = enX;
		tmpBy = enY;
		flag = true;
		Bx = enX - (dist + offsetRadius) * cosVal;
		By = enY - (dist + offsetRadius) * -sinVal;
	}
	else {
		Bx = tmpBx - (dist + offsetRadius) * cosVal + offX;
		By = tmpBy - (dist + offsetRadius) * -sinVal + offY;
	}
	dest.x = Bx;
	dest.y = By;
	dist += 1.2f;
}

void Bullets::setAngl(int x, int y, int w, int h, float offsetR)
{
	flag = false;
	offsetRadius = offsetR;
	x = x - w / 2;
	y = (h / 2 - y);
	screanW = w;
	screanH = h;
	Bx = w / 2;
	By = h / 2;
	angle = -int(atan2f(float(x), float(y)) * 180 / M_PI - 90) % 360;
	if (angle < 0) {
		angle = 270 + angle + 90;
	}
	cosVal = cos(angle * M_PI / 180);
	sinVal = sin(angle * M_PI / 180);
	isFly = true;
}

void Bullets::setAngl(int x, int y, int w, int h, float offsetR, int enx, int eny)
{
	flag = false;
	offsetRadius = offsetR;
	x = x - w / 2;
	y = (h / 2 - y);
	screanW = w;
	screanH = h;
	Bx = enx;
	By = eny;
	angle = -int(atan2f(float(x), float(y)) * 180 / M_PI - 90) % 360;
	if (angle < 0) {
		angle = 270 + angle + 90;
	}
	cosVal = cos(angle * M_PI / 180);
	sinVal = sin(angle * M_PI / 180);
	isFly = true;
}

bool Bullets::intersection(GameObgect* defoltWall, int defoltWallCount, ClosingWall* closingWall, int closingWallCount, Enemy* enemy, int enemyCount, int tile_w, int tile_h, int offsetX, int offsetY, float damage)
{
	if (dist > maxDist) {
		return 1;
	}
	for (int j = 0; j < defoltWallCount; j++) {
		if (Bx >= defoltWall[j].dest.x && Bx <= defoltWall[j].dest.x + defoltWall[j].dest.w &&
			By >= defoltWall[j].dest.y && By <= defoltWall[j].dest.y + defoltWall[j].dest.h) {
			return 1;
		}
	}
	for (int j = 0; j < closingWallCount; j++) {
		if (Bx >= closingWall[j].dest.x && Bx <= closingWall[j].dest.x + closingWall[j].dest.w &&
			By >= closingWall[j].dest.y && By <= closingWall[j].dest.y + closingWall[j].dest.h &&
			closingWall[j].isClos == true) {
			return 1;
		}
	}
	for (int j = 0; j < enemyCount; j++) {
		if (Bx >= enemy[j].dest.x && Bx <= enemy[j].dest.x + enemy[j].dest.w &&
			By >= enemy[j].dest.y && By <= enemy[j].dest.y + enemy[j].dest.h &&
			enemy[j].islive == true) {
			enemy[j].hp -= damage;
			return 1;
		}
	}
	return 0;
}

bool Bullets::intersection(GameObgect* defoltWall, int defoltWallCount, ClosingWall* closingWall, int closingWallCount, int tile_w, int tile_h, int offsetX, int offsetY, float damage, SDL_Rect player)
{
	if (dist > maxDist) {
		return 1;
	}
	for (int j = 0; j < defoltWallCount; j++) {
		if (Bx >= defoltWall[j].dest.x && Bx <= defoltWall[j].dest.x + defoltWall[j].dest.w &&
			By >= defoltWall[j].dest.y && By <= defoltWall[j].dest.y + defoltWall[j].dest.h) {
			return 1;
		}
	}
	for (int j = 0; j < closingWallCount; j++) {
		if (Bx >= closingWall[j].dest.x && Bx <= closingWall[j].dest.x + closingWall[j].dest.w &&
			By >= closingWall[j].dest.y && By <= closingWall[j].dest.y + closingWall[j].dest.h &&
			closingWall[j].isClos == true) {
			return 1;
		}
	}
	if (Bx >= player.x && Bx <= player.x + player.w &&
		By >= player.y && By <= player.y + player.h) {
		intersectionType = 2;
		return 1;
	}
	return 0;
}

void Bullets::reset()
{
	angle = 0;
	dist = 0.0f;
	offX = 0;
	offY = 0;
	Bx = screanW / 2;
	By = screanH / 2;
	isFly = false;
	intersectionType = 0;
}

void Spikes::switchTexture()
{
	tmpTexture = maintx;
	maintx = second;
	second = tmpTexture;
}

void Spikes::changeState()
{
	isRaised = !isRaised;
	used = false;
	switchTexture();
}

bool Spikes::IsRaised()
{
	return isRaised;
}
