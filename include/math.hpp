#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <iostream>

using namespace std;

const int LEVEL_WIDTH = 1024;
const int LEVEL_HEIGHT = 896;
const int SCREEN_WIDTH = 256;
const int SCREEN_HEIGHT = 224;
const int TARGET_FPS = 100;
const int FRAME_DELAY = 1000 / TARGET_FPS;

struct vector2f 
{
	vector2f(float p_x, float p_y):
		x(p_x), y(p_y) {}
	vector2f():
		x(0.0f), y(0.0f) {}
	float x, y;
};

void CreateSprite(vector<SDL_Rect> &sprites, int size);