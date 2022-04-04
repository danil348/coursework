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
