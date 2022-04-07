#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

using namespace std;

class Bullets
{
public:
	void fly();
	int Bx = 990, By = 540;
	bool isFly = false;
	void setAngl(int x, int y, int w, int h);
private:
	float dist = 0.0f;
	int angle;
	int screanW;
	int screanH;
};

