#pragma once

#include "entity.hpp"
#include "RenderWindow.hpp"

class player: public entity
{
public:
	player(vector2f p_pos, RenderWindow &window);
	SDL_Rect getLegRect();
	void update(vector<entity> &wall, float currentTime);
	void update_camera(SDL_Rect &camera);
private:
	int direction, speed, order, isAttacking;
	float lastUpdate;
	vector<SDL_Rect> sprites[4], stance, attack[4];
	SDL_Texture* attackTexture;
	SDL_Texture* movingTexture;
};