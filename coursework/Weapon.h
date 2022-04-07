#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "GameObgect.h"

using namespace std;

class Bullets
{
public:
	Bullets();
	float offX = 0;
	float offY = 0;
	bool isFly = false;
	SDL_Rect src, dest;

	void fly();
	void setAngl(int x, int y, int w, int h);
	void reset();
	bool intersection(GameObgect* defoltWall, int defoltWallCount, ClosingWall* closingWall, int closingWallCount, Enemy* enemy, int enemyCount, int tile_w, int tile_h, int offsetX, int offsetY);
private:
	float dist = 0.0f;
	int maxDist = 8000;
	int angle;
	int screanW;
	int screanH;
	float cosVal;
	float sinVal;
	int Bx, By;
};

