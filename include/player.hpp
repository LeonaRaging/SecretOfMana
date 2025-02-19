#pragma once

#include "entity.hpp"

class player: public entity
{
public:
	player(vector2f p_pos, SDL_Texture* p_tex, int p_x, int p_y, int p_w, int p_h);
	SDL_Rect getLegRect();
	void update(vector<entity> &wall);
private:
	int speed;
};