#include "Weapon.h"

Bullets::Bullets()
{
	src.x = 0;
	src.y = 0;
	src.w = 60;
	src.h = 60;
	dest.w = 20;
	dest.h = 20;
}

void Bullets::fly()
{
	Bx = screanW /2 + dist * cosVal + offX;
	By = screanH /2 + dist * -sinVal + offY;
	dest.x = Bx;
	dest.y = By;
	dist += 6.2f;
}

void Bullets::setAngl(int x, int y, int w, int h)
{
	x = x - w / 2;
	y = (h / 2 - y);
	screanW = w;
	screanH = h;
	Bx = w / 2;
	By = h / 2;
	angle = -int(atan2f(float(x), float(y)) * 180 / M_PI - 90) % 360;
	if (angle < 0) {
		angle = 270 + angle + 90;
	}
	cosVal = cos(angle * M_PI / 180);
	sinVal = sin(angle * M_PI / 180);
	isFly = true;
}

bool Bullets::intersection(GameObgect* defoltWall, int defoltWallCount, ClosingWall* closingWall, int closingWallCount, Enemy* enemy, int enemyCount, int tile_w, int tile_h, int offsetX, int offsetY)
{
	if (dist > maxDist) {
		return 1;
	}
	for (int j = 0; j < defoltWallCount; j++) {
		if (Bx >= defoltWall[j].posX * tile_w + offsetX && Bx <= defoltWall[j].posX * tile_w + offsetX + tile_w &&
			By >= defoltWall[j].posY * tile_h + offsetY && By <= defoltWall[j].posY * tile_h + offsetY + tile_h) {
			return 1;
		}
	}
	for (int j = 0; j < closingWallCount; j++) {
		if (Bx >= closingWall[j].posX * tile_w + offsetX && Bx <= closingWall[j].posX * tile_w + offsetX + tile_w &&
			By >= closingWall[j].posY * tile_h + offsetY && By <= closingWall[j].posY * tile_h + offsetY + tile_h &&
			closingWall[j].isClos == true) {
			return 1;
		}
	}
	for (int j = 0; j < enemyCount; j++) {
		if (Bx >= enemy[j].posX * tile_w + offsetX && Bx <= enemy[j].posX * tile_w + offsetX + tile_w &&
			By >= enemy[j].posY * tile_h + offsetY && By <= enemy[j].posY * tile_h + offsetY + tile_h &&
			enemy[j].islive == true) {
			enemy[j].hp -= 10;
			return 1;
		}
	}
	return 0;
}

void Bullets::reset()
{
	angle = 0;
	dist = 0.0f;
	offX = 0;
	offY = 0;
	Bx = screanW / 2;
	By = screanH / 2;
	isFly = false;
}
