#include "enemy.hpp"
#include "RenderWindow.hpp"

enemy::enemy(vector2f p_pos, SDL_Texture* p_tex)
	:entity(p_pos, p_tex, 0, 0, 16, 16)
{
	hasBeenHit = false;
	hp = 3;
}

void enemy::resetHitState()
{
	hasBeenHit = false;
}

int enemy::isHit(vector2f p_pos, SDL_Rect p_rect)
{
	if (hasBeenHit) return 0;

	p_rect.x = p_pos.x - 42 + p_rect.x;
	p_rect.y = p_pos.y - 42 + p_rect.y;

	SDL_Rect hitbox = getRect();

	if (SDL_HasIntersection(&p_rect, &hitbox))
	{
		hp--;
		hasBeenHit = true;
		if (hp <= 0) 
		{
			cout << "enemy died!" << endl;
			return 2;
		}

		cout << "enemy hit!" << endl;

		return 1;
	}
	return 0;
}
