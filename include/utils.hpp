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
#include <cassert>

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
	float x, y; 
	vector2f(float p_x = 0.0f, float p_y = 0.0f):
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

inline void CreateSprite(vector<SDL_Rect> &sprites, int size)
{
	while ((int)sprites.size() < size)
	{
		SDL_Rect p_rect = sprites.back();
		p_rect.x += 96;
		sprites.push_back(p_rect);
	}
}

inline float Distance(vector2f a, vector2f b)
{
	return sqrt(abs(a.x - b.x) * abs(a.x - b.x) + abs(a.y - b.y) * abs(a.y - b.y));
}

inline pair<int,int> RelativePostion(SDL_Rect a, SDL_Rect b)
{
	int directionX, directionY;

	if (b.x + b.w - 1 < a.x) directionX = 3;
	else if (b.x > a.x + a.w - 1) directionX = 2;
	else directionX = -1;

	if (b.y + b.h - 1 < a.y) directionY = 0;
	else if (b.y > a.y + a.h - 1) directionY = 1;
	else directionY = -1;

	return {directionX, directionY};
}

inline mt19937 mt(chrono::steady_clock::now().time_since_epoch().count());
inline SDL_Rect camera;
inline int isFading, alpha;
inline bool gameStart;
inline vector<numberDisplay> number;

int Reverse(int direction);

inline int areaIntersection(SDL_Rect a, SDL_Rect b)
{
	int left = max(a.x, b.x), right = min(a.x + a.w - 1, b.x + b.w - 1),
		top = max(a.y, b.y), bot = min(a.y + a.h - 1, b.y + b.h - 1);
	return (right - left + 1) * (bot - top + 1);
}


inline int getNumberLength(int number)
{
	if (number == 0) return 1;
	int res = 0;
	while (number > 0)
		number /= 10,
		res++;
	return res;
}