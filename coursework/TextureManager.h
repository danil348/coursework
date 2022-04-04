#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

using namespace std;

class TextureManager
{
public:
	static SDL_Texture* LoadTexture(const char* texture);
	static void Drow(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest);
	static SDL_Renderer* renderer;
private:
};

