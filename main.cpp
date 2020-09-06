#include <iostream>
#include <cstdio>
#include <thread>
#include <conio.h>
#include "map.h"

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

int directionX = 0;
int directionY = 0;

void inputThread(int* buffer) {
    int c = 0;
    while (1)
    {
        c = 0;
        if (_getch() != 224) continue;
        switch ((c = _getch())) {
        case KEY_UP:
            buffer[0] = -1;
            buffer[1] = 0;
            break;
        case KEY_DOWN:
            buffer[0] = 1;
            buffer[1] = 0;
            break;
        case KEY_LEFT:
            buffer[0] = 0;
            buffer[1] = -1;
            break;
        case KEY_RIGHT:
            buffer[0] = 0;
            buffer[1] = 1;
            break;
        default:
            break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(25));
        /*
        while (_kbhit()) {
            _getch();
        }*/
    }
}

void main() {
    int* inputBuffer = new int[2]{ 0, 0 };

    std::thread myThread = std::thread(inputThread, inputBuffer);
    myThread.detach();

    Map map(20, 20);
	while (1) {
        map.setSpeed(inputBuffer[0], inputBuffer[1]);
        map.move();
        map.display();
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}
}