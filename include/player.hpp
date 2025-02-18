#pragma once

#include "entity.hpp"

class player: public entity
{
public:
	player(vector2f p_pos, SDL_Texture* p_tex);
	void update(vector<entity> &wall);
private:
};