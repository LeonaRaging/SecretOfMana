#include "player.hpp"
#include "default.hpp"

player::player(vector2f p_pos, SDL_Texture* p_tex)
	:entity(p_pos, p_tex, 19, 32, 16, 32)
{
	speed = 1; order = 0; lastUpdate = 0; direction = 0;

	stance.emplace_back(SDL_Rect{ 38, 32, 16, 32 });
	stance.emplace_back(SDL_Rect{ 19, 32, 16, 32 });
	stance.emplace_back(SDL_Rect{ 59, 32, 15, 32 });
	stance.emplace_back(SDL_Rect{ 59, 32, 15, 32 });


	sprites[0].emplace_back(SDL_Rect{ 228, 32, 20, 32 });
	while (sprites[0].size() < 6) {
		SDL_Rect p_rect = sprites[0].back();
		p_rect.x += 20;
		sprites[0].push_back(p_rect);
	}

	sprites[1].emplace_back(SDL_Rect{ 95, 32, 22, 32 });
	while (sprites[1].size() < 6) {
		SDL_Rect p_rect = sprites[1].back();
		p_rect.x += 22;
		sprites[1].push_back(p_rect);
	}

	sprites[2].emplace_back(SDL_Rect{ 350, 32, 22, 32 });
	while (sprites[2].size() < 6) {
		SDL_Rect p_rect = sprites[2].back();
		p_rect.x += 22;
		sprites[2].push_back(p_rect);
	}

	sprites[3].emplace_back(SDL_Rect{ 350, 32, 22, 32 });
	while (sprites[3].size() < 6) {
		SDL_Rect p_rect = sprites[3].back();
		p_rect.x += 22;
		sprites[3].push_back(p_rect);
	}
}

SDL_Rect player::getLegRect() 
{
	SDL_Rect p_rect = getRect();
	p_rect.y = pos.y + 26;
	p_rect.h = 6;

	return p_rect;
}

void player::update(vector<entity>& wall, float currentTime) 
{
	const Uint8* keys = SDL_GetKeyboardState(NULL);

	bool isMoving = false;

	if (keys[SDL_SCANCODE_W])
	{
		moveX(-speed);
		if (isCollision(getLegRect(), wall))
			moveX(speed);

		direction = 0;
		isMoving = true;
		setFlip(SDL_FLIP_NONE);
	}

	if (keys[SDL_SCANCODE_S]) {
		moveX(speed);
		if (isCollision(getLegRect(), wall))
			moveX(-speed);
		
		direction = 1;
		isMoving = true;
		setFlip(SDL_FLIP_NONE);
	}

	if (keys[SDL_SCANCODE_A]) {
		moveY(-speed);
		if (isCollision(getLegRect(), wall))
			moveY(speed);
		
		direction = 2;
		isMoving = true;
		setFlip(SDL_FLIP_HORIZONTAL);
	}

	if (keys[SDL_SCANCODE_D]) {
		moveY(speed);
		if (isCollision(getLegRect(), wall))
			moveY(-speed);
		
		direction = 3;
		isMoving = true;
		setFlip(SDL_FLIP_NONE);
	}

	if (isMoving) {
		currentFrame = sprites[direction][order];

		if (currentTime - lastUpdate > 100) {
			order++;
			order %= 6;
			lastUpdate = currentTime;
		}

	}
	else
	{
		currentFrame = stance[direction];
	}
}