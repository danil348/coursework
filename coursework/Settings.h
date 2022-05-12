#pragma once

struct Settings
{
	bool sound = true;
	int row = 4;
	int col = 3;
	int activeItem = 0;
	int itemCount = 4;
	int screen[4][3] = {
		{1920, 1080, 1},
		{1680, 1050, 0},
		{1280, 1024, 0},
		{1, 1, 0},
	};


	float bulletOffsetRadius = 140.0f;
	int bulletDelay = 100;
	float bulletDamage = 10.0f;
	int type = 0;
	int manaCost = 1;
	int cost = 0;
	int weaponAngle = 0;
	int totalWeapons = 3;


	float speed = 3.7f;
	float damage = 25.0f;
	float shotDamage = 10.0f;
	int score = 114;
	int hp = 100;
	int armor = 100;
	int mana = 100;
	float offsetX = 1120.0f;
	float offsetY = 0.0f;
};