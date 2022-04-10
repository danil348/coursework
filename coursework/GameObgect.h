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

	void setMainTexture(SDL_Texture* value);
	void setSecondTexture(SDL_Texture* value);
	void chengeMainTexture();

	SDL_Texture* getMainTexture();
	SDL_Texture* getSecondTexture();

	void setSrcDest_W_H(int src_w, int src_h, int dest_w, int dest_h);
	virtual void setSrcDest_X_Y(int src_x, int src_y, int dest_x, int dest_y);
	void setSrc(int w, int h, int x, int y);
	void setDest(int w, int h, int x, int y);

private:
	bool playerIsClose = false;
	SDL_Texture* maintx;
	SDL_Texture* second;
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


class Enemy: public GameObgect
{
public:
	Enemy();
	bool needSpawn = false;
	bool islive = false;
	bool hasHp = true;
	bool isSpawn = false;
	int hp = 100;
	void update(int& manaPlayer, int& scorePlayer);
	void setSrcDest_X_Y(GameObgect* defoltWall, int defoltWallCount, ClosingWall* closingWall, int closingWallCount, int src_x, int src_y, int dest_x, int dest_y);
	void reset();
	bool intersection(GameObgect* defoltWall, int defoltWallCount, ClosingWall* closingWall, int closingWallCount);
private:
	float offX = 0;
	float offY = 0;
	float coeffX;
	float coeffY;
	int manaPlayerBonus;
	int scorePlayerBonus;
};
