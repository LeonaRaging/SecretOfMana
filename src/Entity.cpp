#include "Entity.hpp"

Entity::Entity(vector2f p_pos):
	pos(p_pos)
{
	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = 32;
	currentFrame.h = 32;
}

vector2f& Entity::getPos()
{
	return pos;
}

SDL_Rect Entity::getCurrentFrame()
{
	return currentFrame;
}