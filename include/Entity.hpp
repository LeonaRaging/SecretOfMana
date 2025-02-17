#pragma once
#include <SDL2/SDL.h>

#include "math.hpp"

class Entity
{
public:
	Entity(vector2f p_pos, SDL_Texture* p_tex);
	vector2f& getPos();
	SDL_Rect getCurrentFrame();
	SDL_Texture* getTex();
	void update();
private:
	vector2f pos;

	SDL_Rect currentFrame;
	SDL_Texture* tex;
};