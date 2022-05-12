#pragma once
#include "TextureManager.h"
#include "GameObgect.h"
#include "TextManager.h"
#include <string>
#include "Settings.h"
#include <fstream>

#define DEBUG

using namespace std;

struct Key
{
	bool leftMouseKey = false;
	int mousePosX = 0;
	int mousePosY = 0;

	bool keyQ = false;
	const int keyQDelay = 600;
	int timeOfLastkeyQ = 0;
	int timeOfCurrentkeyQ = 0;

	bool space = false;
	const int spaceDelay = 600;
	int timeOfLastspace = 0;
	int timeOfCurrentspace = 0;
};

struct PlayerSettings
{
	float speed = 3.7f;
	float damage = 25.0f;
	float shotDamage = 10.0f;
	int score = 114;
	int hp = 100;
	int armor = 100;
	int mana = 100;
	float offsetX = 1120.0f;
	float offsetY = 0.0f;
	SDL_Texture* playerTexture;
	SDL_Rect src = { 0,0,60,60 };
	SDL_Rect dest = { 0,0,120,120 };
};

struct WeaponSettings
{
	void setParameters(WeaponShop& weaponShop);
	SDL_Texture* weaponTexture;
	SDL_Texture* bulletTexture;
	int bulletDelay = 100;
	float bulletDamage = 10.0f;
	int type = 0;
	int manaCost = 1;
	int cost = 0;
	int weaponAngle = 0;

	SDL_Texture* tmpWeaponTexture;
	SDL_Texture* tmpBulletTexture;
	int tmpType;
	int tmpBulletDelay;
	float tmpBulletDamage;
	int tmpManaCost;
	int tmpCost;

	int timeOfLastBullet = 0;
	int timeOfCurrentBullet = 0;
	float bulletOffsetRadius = 140.0f;
	int totalWeapons = 3;
};

class Map
{
public:
	Map();

	void DrawMap(SDL_Window * Window);

	void UpdateMapX(float value);
	void UpdateMapY(float value);
	void Update_W_H(int w, int h);
	void changingKeyState(const Uint8* arr);
	void changingKeyState(bool mouseDown);
	void UpdateSetiings();

	bool Intersection(int type);
	bool IntersectionWithGameObg(ClosingWall wall);
	bool IntersectionWithGameObg(int x, int y, int w, int h);

	void RoomCreater(bool isFirstRoom);

	void ChestDrow(int row, int column);
	void StatueDrow(int row, int column);
	void WeaponDrow(int row, int column);
	void DefoltWallDrow(int row, int column);
	void ClosingWallDrow(int row, int column);
	void PortalBetweenMapsDrow(int row, int column);
	void EnemyDrow();
	void BulletDrow();
	void CharacteristicBoardDrow();
	void CoinCounterDrow();
	void PlayerDrow();

	void EnemyCreator(int row, int column);
	void BulletCreator();

	void CloseFightUpdate();

	PlayerSettings playerSettings;
	TextureManager textureManager;
	WeaponSettings weaponSettings;
	Settings settings;
private:

	string lvlPath;
	string tmpString;
	string path;
	char str[3];
	int _row;
	int _column;

	TextManager textManager;
	Key key;

	int tmpWIDTH = NULL;
	int tmpHEIGTH = NULL;
	int WIDTH;
	int HEIGTH;

	SDL_Rect src, dest;
	SDL_Rect dopDest, dopSrc;
	
	SDL_Texture* ground_1;
	SDL_Texture* ground_2;
	SDL_Texture* ground_3;
	SDL_Texture* ground_4;
	SDL_Texture* ground_5;
	SDL_Texture* coin;
	SDL_Texture* hpBoard;
	SDL_Texture* enemyTx;
	SDL_Texture* chestClose;
	SDL_Texture* chestOpen;
	SDL_Texture* statue_1;
	SDL_Texture* statue_2;
	SDL_Texture* clwall;
	SDL_Texture* dtWall;

	SDL_Texture* portal[8];

	SDL_Texture* weapon_1;
	SDL_Texture* bullet_1;

	SDL_Texture* weapon_2;
	SDL_Texture* bullet_2;

	SDL_Texture* weapon_3;
	SDL_Texture* bullet_3;

	SDL_Texture* portal_1;

	int chestCount = 0;
	Chest* chest;

	int statueCount = 0;
	Statue*statue;

	int closingWallCount = 0;
	ClosingWall* closingWall;
	bool enemyDie = false;

	int bulletsCount = 100;
	Bullets* bullets;

	int defoltWallCount = 0;
	GameObgect* defoltWall;

	int weaponShopCount = 0;
	WeaponShop* weaponShop;

	bool needSpawn = false;
	int enemyCount = 0;
	Enemy* enemy;

	PortalBetweenMaps portalBetweenMaps;

	int tile_w = 120;
	int tile_h = 120;
	int lvl = 1;
	static const int lvl1_w = 70;
	static const int lvl1_h = 70;

	int lvl1[lvl1_h][lvl1_w] = { 0 };
};