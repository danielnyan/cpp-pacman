#pragma once
#include "gameobject.h"
#include <list>

class Player : public GameObject {
public:
	int speedX;
	int speedY;
	Player(int posX, int posY, char representation);
	void move(std::list<GameObject> obstacles, int rows, int columns);
};