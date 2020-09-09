#include <iostream>
#include <windows.h>
#include "map.h"
#include <iterator>

static void getNeighbours(std::list<int>* nodes,
	int** navmesh, int queryX, int queryY, int rows, int columns) {
	int adjX, adjY;

	queryX = queryX % rows;
	queryY = queryY % columns;

	// up
	adjX = (queryX - 1) % rows;
	adjY = queryY % columns;
	if (adjX < 0) {
		adjX += rows;
	}
	if (adjY < 0) {
		adjY += columns;
	}
	if (navmesh[adjX][adjY] == -2) {
		navmesh[adjX][adjY] = navmesh[queryX][queryY] + 1;
		nodes->push_back(adjX);
		nodes->push_back(adjY);
	}

	// down
	adjX = (queryX + 1) % rows;
	adjY = queryY % columns;
	if (adjX < 0) {
		adjX += rows;
	}
	if (adjY < 0) {
		adjY += columns;
	}
	if (navmesh[adjX][adjY] == -2) {
		navmesh[adjX][adjY] = navmesh[queryX][queryY] + 1;
		nodes->push_back(adjX);
		nodes->push_back(adjY);
	}

	// left
	adjX = queryX % rows;
	adjY = (queryY - 1) % columns;
	if (adjX < 0) {
		adjX += rows;
	}
	if (adjY < 0) {
		adjY += columns;
	}
	if (navmesh[adjX][adjY] == -2) {
		navmesh[adjX][adjY] = navmesh[queryX][queryY] + 1;
		nodes->push_back(adjX);
		nodes->push_back(adjY);
	}

	// right
	adjX = queryX % rows;
	adjY = (queryY + 1) % columns;
	if (adjX < 0) {
		adjX += rows;
	}
	if (adjY < 0) {
		adjY += columns;
	}
	if (navmesh[adjX][adjY] == -2) {
		navmesh[adjX][adjY] = navmesh[queryX][queryY] + 1;
		nodes->push_back(adjX);
		nodes->push_back(adjY);
	}
}

static void updateNavmesh(int** navmesh, int playerX, int playerY, int rows, int columns) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			if (navmesh[i][j] != -1) {
				navmesh[i][j] = -2;
			}
			if (i == playerX && j == playerY) {
				navmesh[i][j] = 0;
			}
		}
	}
	std::list<int>* nodes = new std::list<int>();
	int xPos, yPos;
	nodes->push_back(playerX);
	nodes->push_back(playerY);

	while (!nodes->empty()) {
		xPos = nodes->front();
		nodes->pop_front();
		yPos = nodes->front();
		nodes->pop_front();
		getNeighbours(nodes, navmesh, xPos, yPos, rows, columns);
	}

	delete nodes;
}

// https://stackoverflow.com/questions/28196983/is-there-a-faster-way-to-clear-the-console
static void clearscreen()
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
	navmesh = new int* [rows];
	timer = 0;
	for (int i = 0; i < rows; i++) {
		map[i] = new char[columns];
		navmesh[i] = new int[columns];
		for (int j = 0; j < columns; j++) {
			map[i][j] = ' ';
			navmesh[i][j] = -2;
		}
	}
	pacman = new Player(0, 0, 'C');
	ghost = new Ghost(10, 8, 'G');
}

void Map::placeObstacle(int x, int y) {
	obstacles.push_back(*(new GameObject(x, y, 'X')));
	navmesh[x][y] = -1;
}

void Map::refresh() {
	clearscreen();
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			map[i][j] = ' ';
		}
	}
	std::list<GameObject>::iterator it;
	for (it = obstacles.begin(); it != obstacles.end(); ++it) {
		map[it->posX][it->posY] = it->representation;
	}
	map[pacman->posX][pacman->posY] = pacman->representation;
	map[ghost->posX][ghost->posY] = ghost->representation;
}

void Map::setSpeed(int xDelta, int yDelta) {
	pacman->speedX = xDelta;
	pacman->speedY = yDelta;
}

void Map::move() {
	pacman->move(obstacles, rows, columns);
	updateNavmesh(navmesh, pacman->posX, pacman->posY, rows, columns);
	if (timer % 2 == 0)
		ghost->move(navmesh, rows, columns);
	timer++;
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