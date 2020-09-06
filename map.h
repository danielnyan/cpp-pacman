#pragma once
#include "player.h"

class Map {
private:
	int columns;
	int rows;
	char** map;
	Player* pacman;
	GameObject** obstacles;
public:
	Map(int x, int y);
	void display();
	void refresh();
	void setSpeed(int xDelta, int yDelta);
	void move();
	// void populate(std::string data);
	~Map();
};