#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

class GameObgect
{
public:
	void setMainTexture(SDL_Texture* value);
	void setSecondTexture(SDL_Texture* value);
	void chengeMainTexture();

	SDL_Texture* getMainTexture();
	SDL_Texture* getSecondTexture();

	void setSrcDest_W_H(int src_w, int src_h, int dest_w, int dest_h);
	virtual void setSrcDest_X_Y(int src_x, int src_y, int dest_x, int dest_y);
	void setSrc(int w, int h, int x, int y);
	void setDest(int w, int h, int x, int y);

	SDL_Rect src, dest;
	int posX, posY;

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
	Statue();
	void setSrcDest_X_Y(int src_x, int src_y, int dest_x, int dest_y) override;
	bool isUsed();
	void getBonus(int& hp, int& armor, int& mana, int& coins);
	bool wasUsed = false;
private:
	int hpBust = 0;
	int armorBust = 0;
	int manaBust = 0;
	int coinsBust = 15;
	bool used = false;
};


class ClosingWall: public GameObgect
{
public:
	int type;
	bool isClos = false;
	bool mayClose = true;
private:
};
