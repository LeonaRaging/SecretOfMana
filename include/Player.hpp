#pragma once
#include <SDL2/SDL.h>
#include "Entity.hpp"

class Player
{
public:
	Player();
	Entity getEntity();
	void move();
private:
	Entity* e;
	int speed;
};