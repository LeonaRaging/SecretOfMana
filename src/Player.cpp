#include "Player.hpp"

Player::Player() 
{
	Entity temp(640, 360, 50, 50);
	e = &temp;
	speed = 1;
}

Entity Player::getEntity()
{
	return *e;
}

void Player::move() 
{
	const Uint8* keys = SDL_GetKeyboardState(NULL);

	if (keys[SDL_SCANCODE_W]) 
	{
		e->move(-speed, 0);
	}

	if (keys[SDL_SCANCODE_S])
	{
		e->move(speed, 0);
	}

	if (keys[SDL_SCANCODE_A])
	{
		e->move(0, -speed);
	}

	if (keys[SDL_SCANCODE_D]) 
	{
		e->move(0, speed);
	}
}