#include "player.hpp"

player::player(vector2f p_pos, RenderWindow &window)
	:entity(p_pos, NULL)
{
	speed = 1; order = 0; lastUpdate = 0; direction = 0; isAttacking = 0;

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

void player::update(vector<entity>& wall, vector<enemy> &enemies, float currentTime) 
{
	const Uint8* keys = SDL_GetKeyboardState(NULL);

	bool isMoving = false;

	if (!isAttacking)
	{
		if (keys[SDL_SCANCODE_J])
		{
			isAttacking = 5;
			order = 0;
			for (enemy &p_enemy : enemies)
				p_enemy.resetHitState();
		}

		else if (keys[SDL_SCANCODE_W])
		{
			moveX(-speed);
			if (isCollision(getLegRect(), wall))
				moveX(speed);

			direction = 0;
			isMoving = true;
			setFlip(SDL_FLIP_NONE);
		}

		else if (keys[SDL_SCANCODE_S]) {
			moveX(speed);
			if (isCollision(getLegRect(), wall))
				moveX(-speed);
			
			direction = 1;
			isMoving = true;
			setFlip(SDL_FLIP_NONE);
		}

		else if (keys[SDL_SCANCODE_A]) {
			moveY(-speed);
			if (isCollision(getLegRect(), wall))
				moveY(speed);
			
			direction = 2;
			isMoving = true;
			setFlip(SDL_FLIP_HORIZONTAL);
		}

		else if (keys[SDL_SCANCODE_D]) {
			moveY(speed);
			if (isCollision(getLegRect(), wall))
				moveY(-speed);
			
			direction = 3;
			isMoving = true;
			setFlip(SDL_FLIP_NONE);
		}
	}

	if (isAttacking)
	{
		tex = attackTexture;
		currentFrame = attack[direction][order];
		if (order == 2)
		{
			for (int index = 0; index < (int)enemies.size(); index++)
			{	
				int state = enemies[index].isHit(pos, attackHitbox[direction]);

				if (state == 2) 
				{
					swap(enemies[index], enemies.back());
					enemies.pop_back();
					index--;
				}
			}
		}
	}

	else if (isMoving) 
	{
		tex = movingTexture;
		currentFrame = sprites[direction][order];
	}

	else
	{
		tex = movingTexture;
		currentFrame = stance[direction];
	}

	if (currentTime - lastUpdate > 70) {
		order++;
		if (isAttacking) {

			isAttacking--;
			order %= 5;
		}
		else order %= 6;
		lastUpdate = currentTime;

	}

}

void player::update_camera(SDL_Rect &camera)
{
	camera.x = pos.x - SCREEN_HEIGHT / 2;
	camera.y = pos.y - SCREEN_WIDTH / 2;
	camera.w = SCREEN_WIDTH;
	camera.h = SCREEN_HEIGHT;

	if (camera.x < 0) camera.x = 0;
	if (camera.x > LEVEL_HEIGHT - camera.x) camera.x = LEVEL_HEIGHT - camera.x;
	if (camera.y < 0) camera.y = 0;
	if (camera.y > LEVEL_WIDTH - camera.y) camera.y = LEVEL_WIDTH - camera.y;
}