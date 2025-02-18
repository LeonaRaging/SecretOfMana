#include "player.hpp"
#include "default.hpp"

player::player(vector2f p_pos, SDL_Texture* p_tex)
	:entity(p_pos, p_tex)
{

}

void player::update(vector<entity>& wall) 
{
	const Uint8* keys = SDL_GetKeyboardState(NULL);

	if (keys[SDL_SCANCODE_W])
	{
		moveX(-1);
		if (isCollision(getRect(), wall))
			moveX(1);
	}

	if (keys[SDL_SCANCODE_S]) {
		moveX(1);
		if (isCollision(getRect(), wall))
			moveX(-1);
	}

	if (keys[SDL_SCANCODE_A]) {
		moveY(-1);
		if (isCollision(getRect(), wall))
			moveY(1);
	}

	if (keys[SDL_SCANCODE_D]) {
		moveY(1);
		if (isCollision(getRect(), wall))
			moveY(-1);
	}
}