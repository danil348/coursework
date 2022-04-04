#include "TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(const char* texture)
{
	SDL_Surface* tempSurface = IMG_Load(texture);
	if (tempSurface == NULL) {
		cout << "error";
	}
	SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer , tempSurface);
	SDL_FreeSurface(tempSurface);

	return tex;
}

void TextureManager::Drow(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest)
{
	SDL_RenderCopy(Game::renderer, tex, &src, &dest);
}
