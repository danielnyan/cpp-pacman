#include <iostream>
#include <windows.h>
#include "map.h"

// https://stackoverflow.com/questions/28196983/is-there-a-faster-way-to-clear-the-console
void clearscreen()
{
	HANDLE hOut;
	COORD Position;

	hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	Position.X = 0;
	Position.Y = 0;
	SetConsoleCursorPosition(hOut, Position);
}

Map::Map(int x, int y) : rows(x), columns(y) {
	map = new char* [rows];
	for (int i = 0; i < rows; i++) {
		map[i] = new char[columns];
		for (int j = 0; j < columns; j++) {
			map[i][j] = ' ';
		}
	}
	obstacles = new GameObject*[2];
	obstacles[0] = new GameObject(3, 3, 'X');
	obstacles[1] = new GameObject(6, 9, 'X');
	pacman = new Player(0, 0, 'C');
}

void Map::refresh() {
	clearscreen();
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			map[i][j] = ' ';
		}
	}
	for (int i = 0; i < 2; i++) {
		map[obstacles[i]->posX][obstacles[i]->posY] = obstacles[i]->representation;
	}
	map[pacman->posX][pacman->posY] = pacman->representation;
}

void Map::setSpeed(int xDelta, int yDelta) {
	pacman->speedX = xDelta;
	pacman->speedY = yDelta;
}

void Map::move() {
	int futurePosX = pacman->posX + pacman->speedX;
	int futurePosY = pacman->posY + pacman->speedY;

	for (int i = 0; i < 2; i++) {
		if (obstacles[i]->posX == futurePosX
			&& obstacles[i]->posY == futurePosY) {
			pacman->speedX = 0;
			pacman->speedY = 0;
			return;
		}
	}

	pacman->posX = futurePosX;
	pacman->posY = futurePosY;
	if (pacman->posX >= rows) {
		pacman->posX -= rows;
	}
	else if (pacman->posX < 0) {
		pacman->posX += rows;
	}
	if (pacman->posY >= columns) {
		pacman->posY -= columns;
	}
	else if (pacman->posY < 0) {
		pacman->posY += columns;
	}
}

void Map::display() {
	refresh();
	for (int i = 0; i < columns + 2; i++) {
		std::cout << "-";
	}
	std::cout << "\n";
	for (int i = 0; i < rows; i++) {
		std::cout << "|";
		for (int j = 0; j < columns; j++) {
			std::cout << map[i][j];
		}
		std::cout << "|\n";
	}
	for (int i = 0; i < columns + 2; i++) {
		std::cout << "-";
	}
	std::cout << "\n" << std::flush;
}

Map::~Map() {
	for (int i = 0; i < rows; i++) {
		delete[] map[i];
	}
	delete[] map;
}