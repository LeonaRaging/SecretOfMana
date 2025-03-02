#pragma once
#include "entity.hpp"
#include "RenderWindow.hpp"

class enemy: public entity
{
public:
	virtual ~enemy() = default;
	enemy(vector2f p_pos);
	int isHit(vector2f p_pos, SDL_Rect p_rect, vector<numberDisplay> &number);
	entity projectile;
	vector<SDL_Rect> projectileHitbox;
protected:
	int directionX, directionY, direction, state, speed, order, timeLeft;
	float lastUpdate;
	int hp;
	SDL_Rect hitbox;
};

class pebbler : public enemy
{
public:
	pebbler(vector2f p_pos, RenderWindow &window);
	void update(SDL_Rect p_rect, vector<entity> &wall, float currentTime);
	void hurting();
	void dying();
	SDL_Rect getLegRect();
private:
	bool isSpawn;
	// state = {idle, spinning, digging, hurting, dying}
	vector<SDL_Rect> idle, spin[4], dig, die;
	SDL_Rect hurt;
};

class kimonobird : public enemy
{
public:
	kimonobird(vector2f p_pos, RenderWindow &window);
	void update(SDL_Rect p_rect, vector<entity> &wall, float currentTime);
	void hurting();
	void dying();
	SDL_Rect getLegRect();
private:
	// state = {idle, moving, summoning, casting, hurting, dying};
	vector<SDL_Rect> idle, summon, cast, die, bolt;
	SDL_Rect hurt;
};

class waterthug : public enemy
{
public:
	waterthug(vector2f p_pos, RenderWindow &window);
	void update(SDL_Rect p_rect, vector<entity> &wall, float currentTime);
	void hurting();
	void dying();
	SDL_Rect getLegRect();
private:
	// state = {idle, moving, throwing trident, circle attack, hurting, dying}
	vector<SDL_Rect> idle[4], throwing[4], trident, circle, die;
	SDL_Rect hurt; 
};