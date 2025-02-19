#include "player.hpp"
#include "default.hpp"

player::player(vector2f p_pos, SDL_Texture* p_tex, int p_x, int p_y, int p_w, int p_h)
	:entity(p_pos, p_tex, p_x, p_y, p_w, p_h)
{
	speed = 1;
}

SDL_Rect player::getLegRect() 
{
	SDL_Rect p_rect = getRect();
	p_rect.y = pos.y + 26;
	p_rect.h = 6;

	return p_rect;
}

void player::update(vector<entity>& wall) 
{
	const Uint8* keys = SDL_GetKeyboardState(NULL);

	if (keys[SDL_SCANCODE_W])
	{
		moveX(-speed);
		if (isCollision(getLegRect(), wall))
			moveX(speed);
	}

	if (keys[SDL_SCANCODE_S]) {
		moveX(speed);
		if (isCollision(getLegRect(), wall))
			moveX(-speed);
	}

	if (keys[SDL_SCANCODE_A]) {
		moveY(-speed);
		if (isCollision(getLegRect(), wall))
			moveY(speed);
	}

	if (keys[SDL_SCANCODE_D]) {
		moveY(speed);
		if (isCollision(getLegRect(), wall))
			moveY(-speed);
	
	}
}