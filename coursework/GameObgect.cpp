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
	if (hp <= 0) {
		hasHp = false;
		islive = false;
		scorePlayer += scorePlayerBonus;
	}
}

void Enemy::setSrcDest_X_Y(GameObgect* defoltWall, int defoltWallCount, ClosingWall* closingWall, int closingWallCount, int src_x, int src_y, int dest_x, int dest_y)
{
	intersection(defoltWall, defoltWallCount, closingWall, closingWallCount);
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

void Enemy::intersection(GameObgect* defoltWall, int defoltWallCount, ClosingWall* closingWall, int closingWallCount)
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
		for (int j = 0; j < defoltWallCount; j++) {
			if (dest.x + dest.w >= defoltWall[j].dest.x && dest.x + dest.w <= defoltWall[j].dest.x + defoltWall[j].dest.w &&
				dest.x - 10 + dest.w < defoltWall[j].dest.x && dest.y >= defoltWall[j].dest.y &&
				dest.y <= defoltWall[j].dest.y + defoltWall[j].dest.h) {
				pathLengthX *= -1;
				pathX--;
				break;
			}
		}
		for (int j = 0; j < closingWallCount; j++) {
			if (dest.x + dest.w >= closingWall[j].dest.x && dest.x + dest.w <= closingWall[j].dest.x + closingWall[j].dest.w &&
				dest.x - 10 + dest.w < closingWall[j].dest.x && dest.y >= closingWall[j].dest.y &&
				dest.y <= closingWall[j].dest.y + closingWall[j].dest.h) {
				pathLengthX *= -1;
				pathX--;
				break;
			}
		}
	}
	else {
		pathX--;
		pathLengthX++;
		for (int j = 0; j < defoltWallCount; j++) {
			if (dest.x >= defoltWall[j].dest.x && dest.x < defoltWall[j].dest.x + defoltWall[j].dest.w &&
				dest.x + 10 < defoltWall[j].dest.x + defoltWall[j].dest.w && dest.y >= defoltWall[j].dest.y &&
				dest.y <= defoltWall[j].dest.y + defoltWall[j].dest.h) {
				pathLengthX *= -1;
				pathX++;
				break;
			}
		}
		for (int j = 0; j < closingWallCount; j++) {
			if (dest.x >= closingWall[j].dest.x && dest.x < closingWall[j].dest.x + closingWall[j].dest.w &&
				dest.x + 10 < closingWall[j].dest.x + closingWall[j].dest.w && dest.y >= closingWall[j].dest.y &&
				dest.y <= closingWall[j].dest.y + closingWall[j].dest.h) {
				pathLengthX *= -1;
				pathX++;
				break;
			}
		}
	}

	if (pathLengthY > 0) {
		pathY++;
		pathLengthY--;
		for (int j = 0; j < defoltWallCount; j++) {
			if (dest.x >= defoltWall[j].dest.x && dest.x <= defoltWall[j].dest.x + defoltWall[j].dest.w &&
				dest.y + dest.h - 10 < defoltWall[j].dest.y && dest.y + dest.h >= defoltWall[j].dest.y &&
				dest.y <= defoltWall[j].dest.y + defoltWall[j].dest.h) {
				pathLengthY *= -1;
				pathY--;
				break;
			}
		}
		for (int j = 0; j < closingWallCount; j++) {
			if (dest.x >= closingWall[j].dest.x && dest.x <= closingWall[j].dest.x + closingWall[j].dest.w &&
				dest.y + dest.h - 10 < closingWall[j].dest.y && dest.y + dest.h >= closingWall[j].dest.y &&
				dest.y <= closingWall[j].dest.y + closingWall[j].dest.h) {
				pathLengthY *= -1;
				pathY--;
				break;
			}
		}
	}
	else {
		pathY--;
		pathLengthY++;
		for (int j = 0; j < defoltWallCount; j++) {
			if (dest.x >= defoltWall[j].dest.x && dest.x <= defoltWall[j].dest.x + defoltWall[j].dest.w &&
				dest.y + 10 > defoltWall[j].dest.y + defoltWall[j].dest.h && dest.y >= defoltWall[j].dest.y &&
				dest.y <= defoltWall[j].dest.y + defoltWall[j].dest.h) {
				pathLengthY *= -1;
				pathY--;
				break;
			}
		}
		for (int j = 0; j < closingWallCount; j++) {
			if (dest.x >= closingWall[j].dest.x && dest.x <= closingWall[j].dest.x + closingWall[j].dest.w &&
				dest.y + 10 > closingWall[j].dest.y + closingWall[j].dest.h && dest.y >= closingWall[j].dest.y &&
				dest.y <= closingWall[j].dest.y + closingWall[j].dest.h) {
				pathLengthY *= -1;
				pathY--;
				break;
			}
		}
	}
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
