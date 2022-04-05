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

bool Chest::isOpen()
{
	return open;
}

void Chest::chengeOpenState()
{
	open = !open;
}
