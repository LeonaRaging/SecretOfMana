#include "entity.hpp"
#include "default.hpp"

entity::entity(vector2f p_pos, SDL_Texture* p_tex):
	pos(p_pos), tex(p_tex)
{
	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = 32;
	currentFrame.h = 32;
}

vector2f& entity::getPos()
{
	return pos;
}

SDL_Rect entity::getCurrentFrame()
{
	return currentFrame;
}

SDL_Rect entity::getRect()
{
	SDL_Rect res;
	res.x = pos.x;
	res.y = pos.y;
	res.w = currentFrame.w;
	res.h = currentFrame.h;
	return res;
}

SDL_Texture* entity::getTex()
{
	return tex;
}

void entity::moveX(int p_speed)
{
	if (pos.y + p_speed >= 0 && pos.y + p_speed < SCREEN_WIDTH)
		pos.y += p_speed;
}

void entity::moveY(int p_speed) 
{
	if (pos.x + p_speed >= 0 && pos.x + p_speed < SCREEN_HEIGHT)
		pos.x += p_speed;
}