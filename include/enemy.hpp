#pragma once
#include "entity.hpp"


class enemy: public entity
{
public:
	enemy(vector2f p_pos, SDL_Texture* p_tex);
private:
};