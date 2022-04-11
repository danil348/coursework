#pragma once

struct Room1
{
	static const int w = 8;
	static const int h = 8;
	int room[h][w] = {
		{1,1,1,0,0,1,1,1},
		{1,5,3,4,2,2,2,1},
		{1,6,4,5,3,3,5,1},
		{0,3,2,3,5,5,4,0},
		{0,3,4,3,4,4,2,0},
		{1,2,5,2,3,4,3,1},
		{1,4,4,6,4,5,4,1},
		{1,1,1,0,0,1,1,1},
	};
};

struct Room2
{
	static const int w = 10;
	static const int h = 8;
	int room[h][w] = {
		{1,1,1,1,0,0,1,1,1,1},
		{1,5,2,4,3,4,2,2,2,1},
		{1,6,4,5,4,5,3,3,5,1},
		{0,3,2,3,5,5,6,3,4,0},
		{0,3,4,3,4,5,3,4,2,0},
		{1,2,5,2,4,6,3,4,3,1},
		{1,4,4,6,3,4,4,5,4,1},
		{1,1,1,1,0,0,1,1,1,1},
	};
};


struct SpawnRoom
{
	bool hasLowerRoom = false;
	bool hasUpperRoom = false;
	bool hasLeftRoom = false;
	bool hasRightRoom = false;

	static const int w = 8;
	static const int h = 6;
	int room[h][w] = {
		{1,1,1,0,0,1,1,1},
		{1,5,3,4,2,4,2,1},
		{0,6,4,6,3,5,3,0},
		{0,3,2,5,3,3,5,0},
		{1,3,4,3,2,6,8,1},
		{1,1,1,0,0,1,1,1}
	};
};

struct Rooms
{
	const int roomCount = 2;
	static const int mapW = 5;
	static const int mapH = 5;
	int rooms[mapH][mapW] = {
		{0,0,0,0,0},
		{0,0,0,0,0},
		{0,0,0,0,0},
		{0,0,0,0,0},
		{0,0,0,0,0}
	};
	SpawnRoom spawnRoom; // 1
	Room2 room2; // 2
};