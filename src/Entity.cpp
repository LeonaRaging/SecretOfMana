#include "entity.hpp"
#include "default.hpp"

entity::entity(vector2f p_pos, SDL_Texture* p_tex, int p_x, int p_y, int p_w, int p_h):
	pos(p_pos), tex(p_tex)
{
	currentFrame.x = p_x;
	currentFrame.y = p_y;
	currentFrame.w = p_w;
	currentFrame.h = p_h;
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
	if (pos.y + p_speed >= 0 && pos.y + p_speed < LEVEL_HEIGHT)
		pos.y += p_speed;
}

void entity::moveY(int p_speed) 
{
	if (pos.x + p_speed >= 0 && pos.x + p_speed < LEVEL_WIDTH)
		pos.x += p_speed;
}