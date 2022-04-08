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

void Enemy::update()
{
	if (hp <= 0) {
		hasHp = false;
		islive = false;
	}
}

void Enemy::setSrcDest_X_Y(GameObgect* defoltWall, int defoltWallCount, int src_x, int src_y, int dest_x, int dest_y)
{
	dest.x = dest_x;
	dest.y = dest_y;

	if (intersection(defoltWall, defoltWallCount) == true) {
		coeffX *= -1;
		coeffY *= -1;
	}
	offX += coeffX;
	offY += coeffY;
	src.x = src_x;
	src.y = src_y;
	dest.x = dest_x + offX;
	dest.y = dest_y + offY;
}

void Enemy::reset()
{
}

bool Enemy::intersection(GameObgect* defoltWall, int defoltWallCount)
{
	for (int j = 0; j < defoltWallCount; j++) {
		if (dest.x + coeffX + offX >= defoltWall[j].dest.x && dest.x + coeffX + offX <= defoltWall[j].dest.x + defoltWall[j].dest.w &&
			dest.y + coeffY + offY >= defoltWall[j].dest.y && dest.y + coeffY + offY <= defoltWall[j].dest.y + defoltWall[j].dest.h) {
			return 1;
		}
		if (dest.x + coeffX + offX + dest.w >= defoltWall[j].dest.x && dest.x + coeffX + offX + dest.w <= defoltWall[j].dest.x + defoltWall[j].dest.w &&
			dest.y + coeffY + offY + dest.h >= defoltWall[j].dest.y && dest.y + coeffY + offY + dest.h <= defoltWall[j].dest.y + defoltWall[j].dest.h) {
			return 1;
		}
	}
	return 0;
}
