#pragma once

#include "entity.hpp"

class player: public entity
{
public:
	player(vector2f p_pos, SDL_Texture* p_tex);
	SDL_Rect getLegRect();
	void update(vector<entity> &wall, float currentTime);
private:
	int direction, speed, order;
	float lastUpdate;
	vector<SDL_Rect> sprites[4], stance;
};