#include "player.h"
#include <list>
Player::Player(int posX, int posY, char representation) :
	GameObject(posX, posY, representation) {
	speedX = 0;
	speedY = 0;
}

void Player::move(std::list<GameObject> obstacles, int rows, int columns) {
	int futurePosX = posX + speedX;
	int futurePosY = posY + speedY;

	std::list<GameObject>::iterator it;
	for (it = obstacles.begin(); it != obstacles.end(); ++it) {
		if (it->posX == futurePosX && it->posY == futurePosY) {
			speedX = 0;
			speedY = 0;
			return;
		}
	}

	posX = futurePosX;
	posY = futurePosY;
	if (posX >= rows) {
		posX -= rows;
	}
	else if (posX < 0) {
		posX += rows;
	}
	if (posY >= columns) {
		posY -= columns;
	}
	else if (posY < 0) {
		posY += columns;
	}
}