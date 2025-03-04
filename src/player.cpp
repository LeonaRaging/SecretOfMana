#include "player.hpp"

player::player(vector2f p_pos)
	:entity(p_pos, NULL)
{
	hp = 50; speed = 1; order = 0; lastUpdate = 0; direction = 0; state = 0; timeLeft = 0;
	hitbox = SDL_Rect{pos.x, pos.y - 26, 12, 32};

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

	hurt[0].emplace_back(SDL_Rect{ 0, 384, 96, 64});
	hurt[1].emplace_back(SDL_Rect{ 0, 320, 96, 64});
	hurt[2].emplace_back(SDL_Rect{ 0, 256, 96, 64});
	hurt[3].emplace_back(SDL_Rect{ 0, 256, 96, 64});

	for (int i = 0; i < 4; i++)
		CreateSprite(hurt[i], 7);

	die.emplace_back(SDL_Rect{ 0, 448, 96, 64});

	CreateSprite(die, 8);
}

SDL_Rect player::getLegRect() 
{
	SDL_Rect p_rect = getRect();
	p_rect.w = 12;
	p_rect.h = 6;

	return p_rect;
}

SDL_Rect player::getHitbox()
{
	return hitbox;
}

int player::getHp()
{
	return hp;
}

void player::setPos(vector2f p_pos)
{
	pos = p_pos;
}

void player::update(vector<entity>& wall, vector<enemy*> &enemies, float currentTime, vector<numberDisplay> &number) 
{
	const Uint8* keys = SDL_GetKeyboardState(NULL);

	if (timeLeft == 0)
	{
		if (keys[SDL_SCANCODE_J])
		{
			order = 0;
			timeLeft = 5;
			state = 2;
			music.play("SwordSlash", currentTime);
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

	hitbox = SDL_Rect{pos.x, pos.y - 26, 12, 32};

	// cout << hp << endl;

	if (state != 3 && state != 4)
	{
		for (int index = 0; index < (int)enemies.size(); index++)
		{
			bool hasbeenHit = false;
			for (SDL_Rect p_rect : enemies[index]->projectileHitbox)
			{
				if (SDL_HasIntersection(&hitbox, &p_rect))
				{
					state = 3;
					timeLeft = 12;
					int hit = 20 + mt() % 20;
					hp -= hit;
					number.emplace_back(hit, pos);
					hasbeenHit = true;
					order = 0;
					music.play("playerhit", currentTime);
					hp = max(hp, 0);
					if (hp == 0)
					{
						state = 4;
						direction = 2;
						timeLeft = 40;
						break;
					}

					SDL_Rect rect;
					int best = 0;

					rect = SDL_Rect{hitbox.x, hitbox.y, hitbox.w, hitbox.h / 2};
					if (areaIntersection(rect, p_rect) > best) direction = 0, best = areaIntersection(rect, p_rect);
					// cout << areaIntersection(rect, p_rect) << endl;

					rect = SDL_Rect{hitbox.x, hitbox.y + hitbox.h / 2, hitbox.w, hitbox.h / 2};
					if (areaIntersection(rect, p_rect) > best) direction = 1, best = areaIntersection(rect, p_rect);
					// cout << areaIntersection(rect, p_rect) << endl;

					rect = SDL_Rect{hitbox.x, hitbox.y, hitbox.w / 2, hitbox.h};
					if (areaIntersection(rect, p_rect) > best) direction = 3, best = areaIntersection(rect, p_rect);
					// cout << areaIntersection(rect, p_rect) << endl;

					rect = SDL_Rect{hitbox.x + hitbox.w / 2, hitbox.y, hitbox.w / 2, hitbox.h};
					if (areaIntersection(rect, p_rect) > best) direction = 2, best = areaIntersection(rect, p_rect);
					// cout << areaIntersection(rect, p_rect) << endl;
					// cout << endl;
					if (direction == 3) setFlip(SDL_FLIP_HORIZONTAL);
					else setFlip(SDL_FLIP_NONE);

					// cout << direction << endl << endl;
					break;
				}
			}

			if (hasbeenHit) break;
		}
	}

	switch (state)
	{
		case 0:
			tex = movingTexture;
			currentFrame = stance[direction];
			break;

		case 1:
			tex = movingTexture;
			currentFrame = sprites[direction][order];
			break;

		case 2:
			tex = attackTexture;
			currentFrame = attack[direction][order];
			break;

		case 3:
			tex = movingTexture;
			order = min(order, 6);
			currentFrame = hurt[direction][order];
			if (order < 3) speed = 2;
			else if (order < 5) speed = 1;
			else speed = 0;
			if (direction <= 1) moveY((direction ? -1 : 1) * speed, getLegRect(), wall);
			else moveX((direction == 2 ? -1 : 1) * speed, getLegRect(), wall);
			speed = 1;
			break;

		case 4:
			tex = movingTexture;
			order = min(order, 7);
			currentFrame = die[order];
			break;
	}

	if (currentTime - lastUpdate > 100)
	{
		order++;
		
		switch (state) {
			case 0:
				order %= 6;
				break;

			case 1:
				order %= 6;
				music.play("playermoving", currentTime);
				break;

			case 2:
				timeLeft--;
				order %= 5;

				if (order == 2)
				{
					for (int index = 0; index < (int)enemies.size(); index++)
					{	
						int current = enemies[index]->isHit(pos, attackHitbox[direction], number, currentTime);
						if (current == 1) {

							if (kimonobird* p_enemy = dynamic_cast<kimonobird*>(enemies[index]))
							{
								p_enemy->hurting();
							}

							if (pebbler* p_enemy = dynamic_cast<pebbler*>(enemies[index]))
							{
								p_enemy->hurting();
							}

							if (waterthug* p_enemy = dynamic_cast<waterthug*>(enemies[index]))
							{
								p_enemy->hurting();
							}

						}
						else if (current == 2) {

							if (kimonobird* p_enemy = dynamic_cast<kimonobird*>(enemies[index]))
							{
								p_enemy->dying();
							}

							if (pebbler* p_enemy = dynamic_cast<pebbler*>(enemies[index]))
							{
								p_enemy->dying();
							}

							if (waterthug* p_enemy = dynamic_cast<waterthug*>(enemies[index]))
							{
								p_enemy->dying();
							}
						}
					}
				}
				break;

			case 3:
				timeLeft--;
				if (timeLeft == 0) order = 0;
				break;

			case 4:
				timeLeft--;
				if (timeLeft >= 35) moveX(-speed, getLegRect(), wall);
				Mix_VolumeMusic(3 * timeLeft);
				Mix_Volume(-1, 3 * timeLeft);
				if (timeLeft == 0) 
				{
					isFading = 1;		
					gameStart = false;
					Mix_VolumeMusic(128);
					Mix_Volume(-1, 128);
					Mix_PlayMusic(music.titlescreen, -1);
				}
				break;
		}
		lastUpdate = currentTime;

	}

}

void player::update_camera()
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