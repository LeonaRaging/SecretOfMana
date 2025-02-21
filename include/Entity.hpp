#pragma once

#include "math.hpp"

using namespace std;

class entity
{
public:
	entity(vector2f p_pos, SDL_Texture* p_tex, int p_x = 0, int p_y = 0, int p_h = 32, int p_w = 32);
	vector2f& getPos();
	SDL_Rect getCurrentFrame();
	SDL_Rect getRect();
	SDL_Texture* getTex();
	SDL_RendererFlip getFlip();

	void setFlip(SDL_RendererFlip p_flip);
	void moveX(int p_speed);
	void moveY(int p_speed);
protected:
	vector2f pos;

	int disX, disY;
	SDL_RendererFlip flip;
	SDL_Rect currentFrame;
	SDL_Texture* tex;
};