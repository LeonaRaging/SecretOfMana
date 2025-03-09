#pragma once

#include "entity.hpp"
#include "enemy.hpp"
#include "RenderWindow.hpp"
#include "audio.hpp"

class player: public entity
{
public:
	player(vector2f p_pos = {0, 0});
	SDL_Rect getLegRect();
	SDL_Rect getHitbox();
	int getHp();
	void update(vector<entity> &wall, vector<enemy*> &enemies, float currentTime);
	void update_camera();
private:
	int hp, direction, order, timeLeft, state;
	// state = {idle, moving, attacking, hurting, dying, parrying}
	float lastUpdate, physicUpdate, lastParry, speed;
	vector<SDL_Rect> sprites[4], stance, attack[4], hurt[4], die, parry;
	SDL_Rect attackHitbox[4], hitbox;
	SDL_Texture* attackTexture;
	SDL_Texture* movingTexture;
};