#pragma once
#include "gameobject.h"

class Player : public GameObject {
public:
	int speedX;
	int speedY;
	Player(int posX, int posY, char representation);
};