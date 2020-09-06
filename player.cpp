#include "player.h"
Player::Player(int posX, int posY, char representation) :
	GameObject(posX, posY, representation) {
	speedX = 0;
	speedY = 0;
}