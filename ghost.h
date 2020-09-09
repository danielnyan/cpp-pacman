#pragma once
#include "gameobject.h"
#include <list>

class Ghost : public GameObject {
public:
	Ghost(int posX, int posY, char representation);
	void move(int** navmesh, int rows, int columns);
};