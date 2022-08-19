#pragma once
#include <stdlib.h>
#include <math.h>
#include <chrono>
#include <thread>

inline void sleep(int ms) {
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}
#define CANVAS_WIDTH 28.0F
#define CANVAS_HEIGHT 16.0f

#define ASSET_PATH ".\\assets\\"

#define PLAYER_SIZE 2.0f
#define PLAYERB 4.0f
#define MENU_SIZE 6.0f
#define LETTER_SIZE 1.0f
#define LETTERS 0.23
#define PLAYER_MOTION_RANGE 3.0f
#define PLAYER_ATTACK_RANGE 3.0f

#define SETCOLOR(c,d,b,p){c[0]=d;c[1]=b;c[2]=p;}
#define SETCOLOR_1(c,d){c[0]=d;}
#define RAND0TO1() (rand()/(float)RAND_MAX)

inline float distance(float x1, float y1, float x2, float y2)
{
	float dx = x1 - x2;
	float dy = y1 - y2;
	return sqrtf(dx * dx + dy * dy);
}

