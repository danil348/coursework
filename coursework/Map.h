#pragma once
#include "TextureManager.h"
#include "variables.cpp"
#include "GameObgect.h"
#include "TextManager.h"

class Map
{
public:
	Map();

	void DrawMap(SDL_Window * Window);
	void UpdateMapX(float value);
	void UpdateMapY(float value);
	bool Intersection(int type);
	bool IntersectionWithGameObg(GameObgect gameObgect);
	bool IntersectionWithGameObg(Chest chest);
	void SetSize(int w, int h);
	TextureManager textureManager;
private:
	int WIDTH;
	int HEIGTH;
	TextManager textManager;
	SDL_Rect src, dest;
	SDL_Rect _rect;

#ifdef DEBUG
	SDL_Rect rect;
#endif // DEBUG
	
	SDL_Rect _srect;
	SDL_Texture* ground_1;
	SDL_Texture* ground_2;
	SDL_Texture* ground_3;
	SDL_Texture* ground_4;
	SDL_Texture* ground_5;
	SDL_Texture* wall_1;
	SDL_Texture* chest_1;
	SDL_Texture* chest_2;
	SDL_Texture* coin;
	SDL_Texture* hpBoard;
	
	int scorePlayer = 9;

	int hpPlayer = 30;
	int armorPlayer = 100;
	int manaPlayer = 80;

	int chestCount = 0;
	Chest* chest;

	GameObgect statue;

	float offsetX = 0.0f;
	float offsetY = 0.0f;

	int tile_w = 120;
	int tile_h = 120;

	static const int lvl1_w = 30;
	static const int lvl1_h = 30;
	int lvl1[lvl1_h][lvl1_w] = {
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,1,7,4,7,3,7,1,1,1,2,4,5,6,7,1,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,1,3,2,1,4,6,3,3,2,3,3,5,1,1,1,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,3,5,2,3,2,5,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,1,1,4,2,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,1,3,4,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,1,1,1,1,1,2,5,1,1,1,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0},
		{0,0,1,8,6,5,3,2,3,6,3,1,0,0,1,7,4,2,5,4,1,0,0,0,0,0,0,0,0,0},
		{0,0,1,3,4,3,5,4,5,2,4,1,0,0,1,4,2,4,3,2,1,0,0,0,0,0,0,0,0,0},
		{0,0,1,2,3,2,5,2,6,3,4,1,0,0,1,5,2,3,3,2,1,0,0,0,0,0,0,0,0,0},
		{0,0,1,2,2,4,5,5,3,2,3,1,0,0,1,3,3,2,4,2,1,0,0,0,0,0,0,0,0,0},
		{0,0,1,4,2,4,6,2,3,2,3,1,0,0,1,6,5,1,1,2,1,1,1,1,0,0,0,0,0,0},
		{0,0,1,2,3,4,6,2,3,4,3,1,0,0,1,6,3,3,3,5,3,4,7,1,0,0,0,0,0,0},
		{0,0,1,5,2,4,6,5,6,2,3,1,0,0,1,3,3,4,2,5,6,4,4,1,0,0,0,0,0,0},
		{0,0,1,1,1,1,1,1,2,3,1,1,0,1,1,4,3,3,5,1,1,1,1,1,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,1,5,4,1,0,0,1,2,4,4,2,1,1,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,1,6,4,1,0,0,1,2,3,1,1,1,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,1,4,4,1,0,0,1,2,6,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,1,2,4,1,1,1,1,2,4,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,1,3,4,3,4,2,2,3,2,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,1,2,5,4,2,5,4,2,2,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,1,1,1,1,1,1,1,3,6,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,1,5,2,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,1,4,3,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	};
};

