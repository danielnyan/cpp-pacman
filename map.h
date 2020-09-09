#pragma once
#include "player.h"
#include "ghost.h"
#include <list>

class Map {
private:
	int columns;
	int rows;
	char** map;
	int** navmesh;
	int timer;
	Player* pacman;
	Ghost* ghost;
	std::list <GameObject> obstacles;
public:
	Map(int x, int y);
	void display();
	void refresh();
	void placeObstacle(int x, int y);
	void setSpeed(int xDelta, int yDelta);
	void move();
	// void populate(std::string data);
	~Map();
};