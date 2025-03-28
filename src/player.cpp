#include "player.hpp"

player::player(vector2f p_pos)
	:entity(p_pos, NULL)
{
	hp = 250; speed = 0.0625; order = 0; lastUpdate = 0; direction = 0; state = 0; timeLeft = 0; healLeft = 3;
	lastParry = 0; physicUpdate = 0;
	hitbox = SDL_Rect{(int)pos.x, (int)pos.y - 26, 12, 32};

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

	parry.emplace_back(SDL_Rect{ 0, 512, 96, 64});
	parry.emplace_back(SDL_Rect{ 96, 512, 96, 64});
	parry.emplace_back(SDL_Rect{ 192, 512, 96, 64});
	parry.emplace_back(SDL_Rect{ 288, 512, 96, 64});

	heal.emplace_back(SDL_Rect{ 0, 576, 96, 64});

	CreateSprite(heal, 12);
	projectile = entity({0, 0}, movingTexture, heal[0]);
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

void player::update(vector<entity>& wall, vector<enemy*> &enemies, float currentTime) 
{
	const Uint8* keys = SDL_GetKeyboardState(NULL);

	if (timeLeft == 0)
	{
		if (keys[SDL_SCANCODE_J])
		{
			order = 0;
			timeLeft = 5;
			state = 2;
			music.play("SwordSlash");
		}

		else if (keys[SDL_SCANCODE_K] && currentTime - lastParry >= 1000.0)
		{
			order = 0;
			timeLeft = 4;
			state = 5;
			lastParry = currentTime;
		}

		else if (keys[SDL_SCANCODE_F] && healLeft > 0)
		{
			timeLeft = 12;
			state = 6;
			order = 0;
			projectile.setPos(pos);
			healLeft--;
			music.play("healing");
		}

		else 
		{
			state = 0;
			if (physicUpdate == 0) physicUpdate = currentTime;
			float delta = currentTime - physicUpdate;
			delta = min(delta, 16.0);
			if (keys[SDL_SCANCODE_W])
			{
				moveY(-speed * delta, getLegRect(), wall);

				direction = 0;
				setFlip(SDL_FLIP_NONE);
				state = 1;
			}

			if (keys[SDL_SCANCODE_S]) {
				moveY(speed * delta, getLegRect(), wall);
				direction = 1;
				setFlip(SDL_FLIP_NONE);
				state = 1;
			}

			if (keys[SDL_SCANCODE_A]) {
				moveX(-speed * delta, getLegRect(), wall);
				
				direction = 2;
				setFlip(SDL_FLIP_HORIZONTAL);
				state = 1;
			}

			if (keys[SDL_SCANCODE_D]) {
				moveX(speed * delta, getLegRect(), wall);
				
				direction = 3;
				setFlip(SDL_FLIP_NONE);
				state = 1;
			}
		}
	}
	

	hitbox = SDL_Rect{(int)pos.x, (int)pos.y - 26, 12, 32};

	// cout << hp << endl;

	if (state != 3 && state != 4 && (number.empty() || number.back().value != 0))
	{
		for (int index = 0; index < (int)enemies.size(); index++)
		{
			bool hasbeenHit = false;
			for (SDL_Rect p_rect : enemies[index]->projectileHitbox)
			{
				if (SDL_HasIntersection(&hitbox, &p_rect))
				{
					
					int hit = 20 + mt() % 20;
					if (state == 5)
					{
						music.play("Detect");
						if (number.empty() || number.back().value != 0)
							number.emplace_back(0, pos);
						break;
					}
					else
					{
						timeLeft = 12;
						state = 3;
						music.play("playerhit");
					}
					hp -= hit;
					number.emplace_back(hit, pos);
					hasbeenHit = true;
					order = 0;
					hp = max(hp, 0);
					if (hp == 0)
					{
						state = 4;
						direction = 2;
						timeLeft = 40;
						score = scoreRate = 0;
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
			if (hasbeenHit) {
				projectile.setPos({0, 0});
				break;
			}
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
			if (order > 5) speed = 0;
			if (direction <= 1) moveY((direction ? -1 : 1) * speed * (currentTime - physicUpdate), getLegRect(), wall);
			else moveX((direction == 2 ? -1 : 1) * speed * (currentTime - physicUpdate), getLegRect(), wall);
			physicUpdate = currentTime;
			speed = 0.0625;
			break;

		case 4:
			tex = movingTexture;
			order = min(order, 7);
			currentFrame = die[order];
			break;
		case 5:
			tex = movingTexture;
			currentFrame = parry[direction];
			break;
		case 6:
			tex = movingTexture;
			currentFrame = stance[direction];
			projectile.setRect(heal[order]);
			break;
	}

	physicUpdate = currentTime;

	if (currentTime - lastUpdate > 100)
	{
		order++;
		score -= scoreRate;	
		switch (state) {
			case 0:
				order %= 6;
				break;

			case 1:
				order %= 6;
				music.play("playermoving");
				break;

			case 2:
				timeLeft--;
				order %= 5;

				if (order == 2)
				{
					for (int index = 0; index < (int)enemies.size(); index++)
					{	
						int current = enemies[index]->isHit(pos, attackHitbox[direction], currentTime);
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

							if (mantisant* p_enemy = dynamic_cast<mantisant*>(enemies[index]))
							{
								p_enemy->hurting();
							}

						}
						else if (current == 2) {
							healLeft++;
							if (kimonobird* p_enemy = dynamic_cast<kimonobird*>(enemies[index]))
							{
								p_enemy->dying();
								score += 250;
							}

							if (pebbler* p_enemy = dynamic_cast<pebbler*>(enemies[index]))
							{
								p_enemy->dying();
								score += 150;
							}

							if (waterthug* p_enemy = dynamic_cast<waterthug*>(enemies[index]))
							{
								p_enemy->dying();
								score += 150;
							}

							if (mantisant* p_enemy = dynamic_cast<mantisant*>(enemies[index]))
							{
								p_enemy->dying();
								scoreRate = 0;
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
				Mix_VolumeMusic(2 * timeLeft);
				Mix_Volume(-1, 2 * timeLeft);
				if (timeLeft == 0) 
				{
					isFading = 1;		
					gameStart = 2;
				}
				break;
			case 5:
				timeLeft--;
				if (timeLeft == 0) order = 0;
				break;
			case 6:
				timeLeft--;
				if (timeLeft == 0) order = 0, projectile.setPos({0, 0}), hp += 50, hp = min(hp, 250);
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