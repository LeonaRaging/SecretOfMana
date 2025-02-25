#pragma once

#include "entity.hpp"
#include "enemy.hpp"
#include "RenderWindow.hpp"

class player: public entity
{
public:
	player(vector2f p_pos, RenderWindow &window);
	SDL_Rect getLegRect();
	void setPos(vector2f p_pos);
	void update(vector<entity> &wall, vector<enemy*> &enemies, float currentTime);
	void update_camera(SDL_Rect &camera);
private:
	int direction, speed, order, timeLeft, state;
	// state = {idle, moving, attacking}
	float lastUpdate;
	vector<SDL_Rect> sprites[4], stance, attack[4];
	SDL_Rect attackHitbox[4];
	SDL_Texture* attackTexture;
	SDL_Texture* movingTexture;
};