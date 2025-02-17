#include "Entity.hpp"
#include "default.hpp"

Entity::Entity(vector2f p_pos, SDL_Texture* p_tex):
	pos(p_pos), tex(p_tex)
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

SDL_Texture* Entity::getTex()
{
	return tex;
}

void Entity::update()
{
	const Uint8* keys = SDL_GetKeyboardState(NULL);

	if (keys[SDL_SCANCODE_W] && pos.y > 0)
	{
		pos.y--;
	}

	if (keys[SDL_SCANCODE_S] && pos.y < SCREEN_WIDTH - 1) {
		pos.y++;
	}

	if (keys[SDL_SCANCODE_A] && pos.x > 0) {
		pos.x--;
	}

	if (keys[SDL_SCANCODE_D] && pos.x < SCREEN_HEIGHT - 1) {
		pos.x++;
	}
}