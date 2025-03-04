#include "math.hpp"

void CreateSprite(vector<SDL_Rect> &sprites, int size)
{
	while ((int)sprites.size() < size)
	{
		SDL_Rect p_rect = sprites.back();
		p_rect.x += 96;
		sprites.push_back(p_rect);
	}
}

float Distance(vector2f a, vector2f b)
{
	return sqrt(abs(a.x - b.x) * abs(a.x - b.x) + abs(a.y - b.y) * abs(a.y - b.y));
}

pair<int,int> RelativePostion(SDL_Rect a, SDL_Rect b)
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

mt19937 mt(chrono::steady_clock::now().time_since_epoch().count());

SDL_Rect camera;

int isFading, alpha;

bool gameStart;

vector<numberDisplay> number;

int areaIntersection(SDL_Rect a, SDL_Rect b)
{
	int left = max(a.x, b.x), right = min(a.x + a.w - 1, b.x + b.w - 1),
		top = max(a.y, b.y), bot = min(a.y + a.h - 1, b.y + b.h - 1);
	return (right - left + 1) * (bot - top + 1);
}

int getNumberLength(int number)
{
	if (number == 0) return 1;
	int res = 0;
	while (number > 0)
		number /= 10,
		res++;
	return res;
}