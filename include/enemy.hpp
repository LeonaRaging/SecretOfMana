#pragma once
#include "entity.hpp"


class enemy: public entity
{
public:
	enemy(vector2f p_pos, SDL_Texture* p_tex);
	int isHit(vector2f p_pos, SDL_Rect p_rect);
	void resetHitState();
private:
	bool hasBeenHit;
	int hp;
};