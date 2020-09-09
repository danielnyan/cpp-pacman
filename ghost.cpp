#include "ghost.h"

Ghost::Ghost(int posX, int posY, char representation) :
	GameObject(posX, posY, representation) {

}

void Ghost::move(int** navmesh, int rows, int columns) {
	int currentLevel = navmesh[posX][posY];
	if (currentLevel == 0) {
		return;
	}

	int adjX, adjY;

	// up
	adjX = (posX - 1) % rows;
	adjY = posY % columns;
	if (adjX < 0) {
		adjX += rows;
	}
	if (adjY < 0) {
		adjY += columns;
	}
	if (navmesh[adjX][adjY] < currentLevel && navmesh[adjX][adjY] != -1) {
		posX = adjX;
		posY = adjY;
		return;
	}

	// down
	adjX = (posX + 1) % rows;
	adjY = posY % columns;
	if (adjX < 0) {
		adjX += rows;
	}
	if (adjY < 0) {
		adjY += columns;
	}
	if (navmesh[adjX][adjY] < currentLevel && navmesh[adjX][adjY] != -1) {
		posX = adjX;
		posY = adjY;
		return;
	}

	// left
	adjX = posX % rows;
	adjY = (posY + 1) % columns;
	if (adjX < 0) {
		adjX += rows;
	}
	if (adjY < 0) {
		adjY += columns;
	}
	if (navmesh[adjX][adjY] < currentLevel && navmesh[adjX][adjY] != -1) {
		posX = adjX;
		posY = adjY;
		return;
	}

	// right
	adjX = posX % rows;
	adjY = (posY - 1) % columns;
	if (adjX < 0) {
		adjX += rows;
	}
	if (adjY < 0) {
		adjY += columns;
	}
	if (navmesh[adjX][adjY] < currentLevel && navmesh[adjX][adjY] != -1) {
		posX = adjX;
		posY = adjY;
		return;
	}
}