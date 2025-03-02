#pragma once

#include "math.hpp"

using namespace std;

class entity
{
public:
	entity(vector2f p_pos = {0, 0}, SDL_Texture* p_tex = NULL, int p_x = 0, int p_y = 0, int p_h = 32, int p_w = 32);
	entity(vector2f p_pos, SDL_Texture* p_tex, SDL_Rect p_rect);
	vector2f getPos();
	SDL_Rect getCurrentFrame();
	SDL_Rect getRect();
	SDL_Texture* getTex();
	SDL_RendererFlip getFlip();

	void setRect(SDL_Rect p_rect);
	void setFlip(SDL_RendererFlip p_flip);
	void moveX(float p_speed, SDL_Rect p_rect, vector<entity> &wall);
	void moveY(float p_speed, SDL_Rect p_rect, vector<entity> &wall);
protected:
	vector2f pos;
	SDL_RendererFlip flip;
	SDL_Texture* tex;
	SDL_Rect currentFrame;
};

bool isCollision(SDL_Rect a, vector<entity>& b);