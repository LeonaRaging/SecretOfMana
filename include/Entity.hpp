#pragma once
#include <SDL2/SDL.h>

#include "math.hpp"

class Entity
{
public:
	Entity(vector2f p_pos);
	vector2f& getPos();
	SDL_Rect getCurrentFrame();
private:
	vector2f pos;
	SDL_Rect currentFrame;
};