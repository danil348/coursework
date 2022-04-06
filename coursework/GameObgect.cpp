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

void Chest::chengeOpenState(bool flag)
{
	dest.w = dest.w + int(dest.w / 2.1);
	open = flag;
}

void Chest::getBonus(int& hp, int& armor, int& mana, int& coins)
{
	int flag = rand() % 10;
	if (flag == 0) {
		hp += rand() % 2 + 1;
		hp = hp % 101;
	}

	flag = rand() % 2;
	if (flag == 0) {
		armor += rand() % 10 + 1;
		armor = armor % 101;
	}
	
	flag = rand() % 2;
	if (flag == 0) {
		mana += rand() % 10 + 1;
		mana = mana % 101;
	}
	coins += rand() % 2 + 1;
}

void Statue::setSrcDest_X_Y(int src_x, int src_y, int dest_x, int dest_y)
{
	dest.x = dest_x;
	src.x = src_x;
	src.y = src_y;
	dest.y = dest_y;
}

void Statue::chengeUsedState(bool flag)
{
	used = flag;
}

bool Statue::isUsed()
{
	return used;
}

void Statue::getBonus(int& hp, int& armor, int& mana, int& coins)
{
	if (coins >= 15) {
		used = true;
		coins -= 15; 
		int flag = rand() % 2;
		if (flag == 0) {
			hp += rand() % 10 + 1;
			hp = hp % 101;
		}

		flag = rand() % 2;
		if (flag == 0) {
			armor += rand() % 30 + 1;
			armor = armor % 101;
		}

		flag = rand() % 2;
		if (flag == 0) {
			mana += rand() % 30 + 1;
			mana = mana % 101;
		}
	}
}
