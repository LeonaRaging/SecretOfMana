#pragma once
#include "entity.hpp"
// #include "map.hpp"
#include "RenderWindow.hpp"

class enemy: public entity
{
public:
	virtual ~enemy() = default;
	enemy(vector2f p_pos);
	int isHit(vector2f p_pos, SDL_Rect p_rect);
	void resetHitState();
	entity projectile;
protected:
	bool hasBeenHit;
	int hp;
	SDL_Rect hitbox;
};

class pebbler : public enemy
{
public:
	pebbler(vector2f p_pos, RenderWindow &window);
	void update(vector2f p_pos, vector<entity> &wall, float currentTime);
	void hurting();
	void dying();
	SDL_Rect getLegRect();
private:
	bool isSpawn;
	int directionX, directionY, direction, state, speed, order, timeLeft;
	float lastUpdate;
	// state = {idle, spinning, digging, hurting, dying}
	vector<SDL_Rect> idle, spin[4], dig, die;
	SDL_Rect hurt;
};

class kimonobird : public enemy
{
public:
	kimonobird(vector2f p_pos, RenderWindow &window);
	void update(vector2f p_pos, vector<entity> &wall, float currentTime);
	void hurting();
	void dying();
	SDL_Rect getLegRect();
private:
	int directionX, directionY, direction, state, speed, order, timeLeft;
	float lastUpdate;
	// state = {idle, moving, summoning, casting, hurting, dying};
	vector<SDL_Rect> idle, summon, cast, die, bolt;
	SDL_Rect hurt;
};