#include "player.hpp"

player::player(vector2f p_pos, RenderWindow &window)
	:entity(p_pos, NULL)
{
	speed = 1; order = 0; lastUpdate = 0; direction = 0; state = 0;

	movingTexture = window.loadTexture("res/image/player/moving.png");
	attackTexture = window.loadTexture("res/image/player/attack.png");

	stance.emplace_back(SDL_Rect{ 0, 0, 96, 64 });
	stance.emplace_back(SDL_Rect{ 96, 0, 96, 64 });
	stance.emplace_back(SDL_Rect{ 192, 0, 96, 64 });
	stance.emplace_back(SDL_Rect{ 192, 0, 96, 64 });

	sprites[0].emplace_back(SDL_Rect{ 0, 64, 96, 64 });
	sprites[1].emplace_back(SDL_Rect{ 0, 192, 96, 64 });
	sprites[2].emplace_back(SDL_Rect{ 0, 128, 96, 64});
	sprites[3].emplace_back(SDL_Rect{ 0, 128, 96, 64 });

	for (int i = 0; i < 4; i++)
		CreateSprite(sprites[i], 6);

	attack[0].emplace_back(SDL_Rect{ 0, 0, 96, 64});
	attack[1].emplace_back(SDL_Rect{ 0, 128, 96, 64});
	attack[2].emplace_back(SDL_Rect{ 0, 64, 96, 64});
	attack[3].emplace_back(SDL_Rect{ 0, 64, 96, 64});

	for (int i = 0; i < 4; i++)
		CreateSprite(attack[i], 5);

	attackHitbox[0] = SDL_Rect{ 16, 0, 64, 48};
	attackHitbox[1] = SDL_Rect{ 16, 32, 48, 32};
	attackHitbox[2] = SDL_Rect{ 16, 16, 32, 32};
	attackHitbox[3] = SDL_Rect{ 48, 16, 32, 32};
}

SDL_Rect player::getLegRect() 
{
	SDL_Rect p_rect = getRect();
	p_rect.w = 12;
	p_rect.h = 6;

	return p_rect;
}

void player::setPos(vector2f p_pos)
{
	pos = p_pos;
}

void player::update(vector<entity>& wall, vector<enemy*> &enemies, float currentTime) 
{
	const Uint8* keys = SDL_GetKeyboardState(NULL);

	if (timeLeft == 0)
	{
		if (keys[SDL_SCANCODE_J])
		{
			timeLeft = 5;
			order = 0;
			for (auto &p_enemy : enemies)
				p_enemy->resetHitState();
			state = 2;
		}

		else 
		{
			state = 0;
			if (keys[SDL_SCANCODE_W])
			{
				moveY(-speed, getLegRect(), wall);

				direction = 0;
				setFlip(SDL_FLIP_NONE);
				state = 1;
			}

			if (keys[SDL_SCANCODE_S]) {
				moveY(speed, getLegRect(), wall);
				
				direction = 1;
				setFlip(SDL_FLIP_NONE);
				state = 1;
			}

			if (keys[SDL_SCANCODE_A]) {
				moveX(-speed, getLegRect(), wall);
				
				direction = 2;
				setFlip(SDL_FLIP_HORIZONTAL);
				state = 1;
			}

			if (keys[SDL_SCANCODE_D]) {
				moveX(speed, getLegRect(), wall);
				
				direction = 3;
				setFlip(SDL_FLIP_NONE);
				state = 1;
			}
		}
	}

	if (state == 2)
	{
		tex = attackTexture;
		currentFrame = attack[direction][order];
		if (order == 2)
		{
			for (int index = 0; index < (int)enemies.size(); index++)
			{	
				int current = enemies[index]->isHit(pos, attackHitbox[direction]);
				if (current == 1) {
					dynamic_cast<pebbler*>(enemies[index])->hurting();
				}
				else if (current == 2) {
					dynamic_cast<pebbler*>(enemies[index])->dying();
				}
			}
		}
	}

	if (state == 1) 
	{
		tex = movingTexture;
		currentFrame = sprites[direction][order];
	}

	if (state == 0)
	{
		tex = movingTexture;
		currentFrame = stance[direction];
	}

	if (currentTime - lastUpdate > 100)
	{
		order++;
		if (state == 2) {

			timeLeft--;
			order %= 5;
		}
		else order %= 6;
		lastUpdate = currentTime;

	}

}

void player::update_camera(SDL_Rect &camera)
{
	camera.x = pos.x - SCREEN_WIDTH / 2;
	camera.y = pos.y - SCREEN_HEIGHT / 2;
	camera.w = SCREEN_WIDTH;
	camera.h = SCREEN_HEIGHT;

	if (camera.x < 0) camera.x = 0;
	if (camera.x > LEVEL_WIDTH - SCREEN_WIDTH) camera.x = LEVEL_WIDTH - SCREEN_WIDTH;
	if (camera.y < 0) camera.y = 0;
	if (camera.y > LEVEL_HEIGHT - SCREEN_HEIGHT) camera.y = LEVEL_HEIGHT - SCREEN_HEIGHT;
}