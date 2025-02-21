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