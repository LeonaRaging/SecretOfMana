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

pair<int,int> RelativePostion(vector2f a, vector2f b)
{
	int directionX, directionY;

	directionX = (b.x < a.x ? 3 : 2);
	directionY = (b.y < a.y ? 0 : 1);

	return {directionX, directionY};
}

mt19937 mt(chrono::steady_clock::now().time_since_epoch().count());