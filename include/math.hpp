#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <memory>
#include <cmath>
#include <random>
#include <utility>
#include <chrono>
#include <iomanip>
#include <algorithm>
#include <unordered_map>

using namespace std;

const int LEVEL_WIDTH = 1024;
const int LEVEL_HEIGHT = 764;
const int SCREEN_WIDTH = 256;
const int SCREEN_HEIGHT = 191;
const int TARGET_FPS = 100;
const int FRAME_DELAY = 1000 / TARGET_FPS;
const int aggroRadius = 150;

struct vector2f 
{
	int x, y; 
	vector2f(int p_x = 0.0f, int p_y = 0.0f):
		x(p_x), y(p_y) {}
};

struct numberDisplay
{
	int value;
	vector2f pos;
	int timeLeft;
	float lastUpdate;

	numberDisplay(int value = 0, vector2f pos = {0, 0}):
		value(value), pos(pos), timeLeft(10), lastUpdate(0.0f)
	{

	};
};

void CreateSprite(vector<SDL_Rect> &sprites, int size);

float Distance(vector2f a, vector2f b);

pair<int,int> RelativePostion(SDL_Rect a, SDL_Rect b);

extern mt19937 mt;
extern SDL_Rect camera;
extern int isFading, alpha;
extern bool gameStart;
extern vector<numberDisplay> number;

int Reverse(int direction);

int areaIntersection(SDL_Rect a, SDL_Rect b);

int getNumberLength(int number);