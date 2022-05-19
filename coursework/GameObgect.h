#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

using namespace std;

class GameObgect
{
public:
	SDL_Rect src, dest;
	int posX, posY;
	//asd
	void setMainTexture(SDL_Texture* value);
	void setSecondTexture(SDL_Texture* value);
	void chengeMainTexture();

	SDL_Texture* getMainTexture();
	SDL_Texture* getSecondTexture();

	void setSrcDest_W_H(int src_w, int src_h, int dest_w, int dest_h);
	virtual void setSrcDest_X_Y(int src_x, int src_y, int dest_x, int dest_y);
	void setSrc(int w, int h, int x, int y);
	void setDest(int w, int h, int x, int y);

	SDL_Texture* maintx;
	SDL_Texture* second;
private:
	bool playerIsClose = false;
};

class Chest: public GameObgect
{
public:
	Chest();
	void setSrcDest_X_Y(int src_x, int src_y, int dest_x, int dest_y) override;
	bool isOpen();
	void getBonus(int& hp, int& armor, int& mana, int& coins);
private:
	int hpBust = 0;
	int armorBust = 0;
	int manaBust = 0;
	int coinsBust = 0;
	bool open = false;
	bool stateIsChanged = false;
};

class Statue: public GameObgect
{ 
public:
	bool wasUsed = false;

	Statue();
	void setSrcDest_X_Y(int src_x, int src_y, int dest_x, int dest_y) override;
	bool isUsed();
	void getBonus(int& hp, int& armor, int& mana, int& coins);
	void setType(int type);
	int getType();
private:
	int hpBust = 0;
	int armorBust = 0;
	int manaBust = 0;
	int coinsBust = 15;
	bool used = false;
	int type;
};

class WeaponShop: public GameObgect
{
public:
	void setWeaponTexture(SDL_Texture* value);
	void setBulletTexture(SDL_Texture* value);
	void setType(int type);
	void setParameters(float bulletDamage, int manaCost);

	int getType();
	SDL_Texture* getWeaponTexture();
	SDL_Texture* getBulletTexture();

	float bulletDamage = 10.0f;
	int manaCost = 1;
	int cost = 10;
	bool alrBuy = false;
	bool isBuy = false;
private:
	SDL_Texture* weaponTexture;
	SDL_Texture* bulletTexture;
	int bulletDelay = 100;
	float bulletOffsetRadius = 140.0f;
	int type = 0;
};


class ClosingWall: public GameObgect
{
public:
	int type;
	bool isClos = false;
	bool mayClose = true;
private:
};

class Bullets;
class Enemy;


class Bullets
{
public:
	Bullets();
	float offX = 0;
	float offY = 0;
	bool isFly = false;
	int intersectionType = 0;
	SDL_Rect src, dest;

	void fly();
	void fly(int enX, int enY);
	void setAngl(int x, int y, int w, int h, float offsetR);
	void setAngl(int x, int y, int w, int h, float offsetR, int enx, int eny);
	void reset();
	bool intersection(GameObgect* defoltWall, int defoltWallCount, ClosingWall* closingWall, int closingWallCount, Enemy* enemy, int enemyCount, int tile_w, int tile_h, int offsetX, int offsetY, float damage);
	bool intersection(GameObgect* defoltWall, int defoltWallCount, ClosingWall* closingWall, int closingWallCount, int tile_w, int tile_h, int offsetX, int offsetY, float damage, SDL_Rect player);
private:
	float dist = 0.0f;
	int maxDist = 8000;
	float offsetRadius;
	int angle;
	int screanW;
	int screanH;
	float cosVal;
	float sinVal;
	int Bx, By;
	int tmpBx, tmpBy;
	float speed = 1;
	bool flag = false;
};

class Enemy: public GameObgect
{
public:
	Enemy();
	bool needSpawn = false;
	bool islive = false;
	bool hasHp = true;
	bool isSpawn = false;
	int hp = 100;
	int damage = 1;
	void update(int& manaPlayer, int& scorePlayer);
	void setSrcDest_X_Y(GameObgect* defoltWall, int defoltWallCount, ClosingWall* closingWall, int closingWallCount, int src_x, int src_y, int dest_x, int dest_y);
	void setScreen_W_H(int w, int h);
	void reset();
	void intersection(GameObgect* defoltWall, int defoltWallCount, ClosingWall* closingWall, int closingWallCount, int dest_x, int dest_y);

	int bulletsCount = 120;
	Bullets* bl = new Bullets[bulletsCount];
	int bulletDelay = 1000;
	int timeOfCurrentBullet = 0;
	int timeOfLastBullet = 0;
private:
	bool intersection(GameObgect* defoltWall, int Count, int dest_x, int dest_y);
	bool intersection(ClosingWall* closingWall, int Count, int dest_x, int dest_y);

	int manaPlayerBonus;
	int scorePlayerBonus;

	int ScreenW;
	int ScreenH;
	int pathLengthX = 0;
	int pathLengthY = 0;
	int pathX = 0;
	int pathY = 0;
};

class PortalBetweenMaps: public GameObgect
{
public:
	SDL_Texture* tx[8];
	int animFrame = 0;
	void animFrameUpdate();
private:
	int dopFrame = 0;
	const int animFrameCount = 8;
	int animFrameDelay = 16;
};

class Spikes : public GameObgect
{
public:
	void changeState();
	bool IsRaised();
	bool used = false;
private:
	void switchTexture();

	bool isRaised = false;
	SDL_Texture* tmpTexture;
};