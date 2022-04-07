#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "GameObgect.h"

using namespace std;

class Bullets
{
public:
	float offX = 0;
	float offY = 0;
	int Bx, By;
	bool isFly = false;

	void fly();
	void setAngl(int x, int y, int w, int h);
	void reset();
	bool intersection(GameObgect* defoltWall, int defoltWallCount, ClosingWall* closingWall, int closingWallCount, int tile_w, int tile_h, int offsetX, int offsetY);
private:
	float dist = 0.0f;
	int maxDist = 8000;
	int angle;
	int screanW;
	int screanH;
};

