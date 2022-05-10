#pragma once
class Menu
{
public:
	bool isRunning = false;

	const int keyDelay = 200;
	int timeOfLastKey = 0;
	int timeOfCurrentKey = 0;

	int tmpTime = 0;
private:
};

