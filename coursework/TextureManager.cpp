#include "TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(const char* texture)
{
	SDL_Surface* tempSurface = IMG_Load(texture);
	if (tempSurface == NULL) {
		cout << "TextureManager error";
	}
	SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, tempSurface);
	SDL_FreeSurface(tempSurface);
	return tex;
}

void TextureManager::Drow(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest)
{
	SDL_RenderCopy(renderer, tex, &src, &dest);
}

void TextureManager::Drow(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest, float angle)
{
	SDL_RenderCopyEx(renderer, tex, &src, &dest, angle, NULL, SDL_FLIP_NONE);
}
