#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <memory>
#include <cmath>
#include <random>
#include <utility>
#include <chrono>
#include <iomanip>

using namespace std;

const int LEVEL_WIDTH = 1024;
const int LEVEL_HEIGHT = 896;
const int SCREEN_WIDTH = 256;
const int SCREEN_HEIGHT = 244;
const int TARGET_FPS = 100;
const int FRAME_DELAY = 1000 / TARGET_FPS;
const int aggroRadius = 150;

struct vector2f 
{
	vector2f(float p_x = 0.0f, float p_y = 0.0f):
		x(p_x), y(p_y) {}
	int x, y; 
};

void CreateSprite(vector<SDL_Rect> &sprites, int size);

float Distance(vector2f a, vector2f b);

pair<int,int> RelativePostion(SDL_Rect a, SDL_Rect b);

extern mt19937 mt;

int Reverse(int direction);

int areaIntersection(SDL_Rect a, SDL_Rect b);