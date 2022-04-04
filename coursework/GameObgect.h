#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

class GameObgect
{
public:
	void setMainTexture(SDL_Texture* value);
	void setSecondTexture(SDL_Texture* value);
	SDL_Texture* getMainTexture();
	SDL_Texture* getSecondTexture();
	void setSrc(int w, int h, int x, int y);
	void setDest(int w, int h, int x, int y);
	SDL_Rect src, dest;
	void chengeMainTexture();
private:
	bool playerIsClose = false;
	SDL_Texture* maintx;
	SDL_Texture* second;
};

