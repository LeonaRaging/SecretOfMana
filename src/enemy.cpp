#include "enemy.hpp"

enemy::enemy(vector2f p_pos)
	:entity(p_pos)
{
	isDeath = false;
}

int enemy::isHit(vector2f p_pos, SDL_Rect p_rect, float currentTime)
{

	p_rect.x = p_pos.x - 42 + p_rect.x;
	p_rect.y = p_pos.y - 42 + p_rect.y;
	if (SDL_HasIntersection(&p_rect, &hitbox))
	{
		int hit = 40 + mt() % 20;
		hp -= hit;
		number.push_back(numberDisplay(hit, pos));
		if (hp <= 0) 
		{
			cout << "enemy died!" << endl;
			music.play("enemydie", currentTime);
			return 2;
		}

		music.play("enemyhit", currentTime);
		cout << "enemy hit!" << endl;
		return 1;
	}
	return 0;
}

pebbler::pebbler(vector2f p_pos):
	enemy(p_pos)
{
	direction = directionX = directionY = state = timeLeft = order = 0; speed = 0.05;
	hp = 186;
	hitbox = SDL_Rect{(int)pos.x - 42 + 38, (int)pos.y - 42 + 21, 20, 27};
	isSpawn = false;
	tex = window.loadTexture("res/image/enemy/pebbler.png");

	idle.emplace_back(SDL_Rect{ 0, 0, 96, 64});
	CreateSprite(idle, 16);

	spin[0].emplace_back(SDL_Rect{ 0, 128, 96, 64});
	spin[1].emplace_back(SDL_Rect{ 0, 64, 96, 64});
	spin[2].emplace_back(SDL_Rect{ 0, 192, 96, 64});
	spin[3].emplace_back(SDL_Rect{ 0, 192, 96, 64});
	dig.emplace_back(SDL_Rect{ 0, 256, 96, 64});
	hurt = SDL_Rect{0, 320, 96, 64};
	die.emplace_back(SDL_Rect{ 0, 384, 96, 64});

	for (int i = 0; i < 4; i++)
		CreateSprite(spin[i], 4);
	CreateSprite(dig, 13);
	CreateSprite(die, 9);
}	

SDL_Rect pebbler::getLegRect()
{
	SDL_Rect p_rect = getRect();
	p_rect.w = 12;
	p_rect.h = 6;

	return p_rect;
}

void pebbler::hurting()
{
	timeLeft = 10;
	state = 3;
}

void pebbler::dying()
{
	order = 0;
	timeLeft = 9;
	state = 4;
}

void pebbler::update(SDL_Rect p_rect, vector<entity> &wall, float currentTime)
{	
	timeLeft = max(timeLeft, 0);
	if (timeLeft == 0)
	{
		if (Distance(pos, vector2f(p_rect.x, p_rect.y)) > aggroRadius)
		{
			state = 0;
			timeLeft = 1;
		}
		else
		{
			if (!isSpawn)
			{
				music.play("dig", currentTime);
				order = 0;
				state = 2;
				timeLeft = 12;
				isSpawn = true;
			}

			else
			{
				order = 0; 
				state = 1;
				speed = 0.1;
				timeLeft = 6;
				music.play("spin", currentTime);
				hitbox = SDL_Rect{(int)pos.x - 42 + 38, (int)pos.y - 42 + 21, 20, 27};

				tie(directionX, directionY) = RelativePostion(hitbox, p_rect);
				
				if (directionX == -1 && directionY != -1) direction = directionY;
				if (directionX != -1 && directionY == -1) direction = directionX;

				if (direction == 3) setFlip(SDL_FLIP_HORIZONTAL);
				else setFlip(SDL_FLIP_NONE);

			}
		}

	}

	hitbox = SDL_Rect{0, 0, 0, 0};

	float delta = currentTime - physicUpdate;

	projectileHitbox.clear();
	switch (state)
	{
		case 0:
			currentFrame = idle[order];
			hitbox = SDL_Rect{(int)pos.x - 42 + 38, (int)pos.y - 42 + 21, 20, 27};
			break;

		case 1:
			currentFrame = spin[direction][order];
			if (directionX != -1) moveX((directionX == 2 ? speed : -speed) * delta, getLegRect(), wall);
			if (directionY != -1) moveY((directionY ? speed : -speed) * delta, getLegRect(), wall);
			
			projectileHitbox.emplace_back(SDL_Rect{(int)pos.x - 42 + 38, (int)pos.y - 42 + 25, 20, 20});
			
			break;

		case 2:
			currentFrame = dig[order];
			break;

		case 3:
			currentFrame = hurt;
			break;

		case 4:
			currentFrame = die[order];
			break;

	}
	physicUpdate = currentTime;

	if (currentTime - lastUpdate > 150)
	{
		timeLeft--;
		order++;

		switch (state)
		{
			case 0:
				order %= 16;
				break;
			case 1:
				
				if (order == 3) 
				{
					order = 1;
				}

				if (timeLeft == 0)
				{
					state = 0;
					timeLeft = 16;
				}

				break;
			case 4:
				if (timeLeft == 0)
				{
					pos = {0, 0};
					isDeath = true;
				}

				break;
		}

		lastUpdate = currentTime;
	}
	if (!isSpawn) currentFrame = dig[0];
}

kimonobird::kimonobird(vector2f p_pos)
	:enemy(p_pos)
{
	directionX = directionY = state = timeLeft = order = 0; speed = 0.05;
	hp = 160;
	hitbox = SDL_Rect{(int)pos.x - 42 + 40, (int)pos.y - 42 + 14, 16, 34};
	tex = window.loadTexture("res/image/enemy/kimonobird.png");

	idle.emplace_back(SDL_Rect{0, 0, 96, 64});
	summon.emplace_back(SDL_Rect{0, 64, 96, 64});
	cast.emplace_back(SDL_Rect{0, 128, 96, 64});
	hurt = SDL_Rect{0, 192, 96, 64};
	die.emplace_back(SDL_Rect{0, 256, 96, 64});
	bolt.emplace_back(SDL_Rect{0, 320, 96, 112});

	CreateSprite(idle, 6);
	CreateSprite(summon, 5);
	CreateSprite(cast, 4);
	CreateSprite(die, 20);
	CreateSprite(bolt, 6);

}

SDL_Rect kimonobird::getLegRect()
{
	SDL_Rect p_rect = getRect();
	p_rect.y = p_rect.y + 16;
	p_rect.w = 12; 
	p_rect.h = 6;
	return p_rect;
}

void kimonobird::hurting()
{
	state = 4;
	timeLeft = 10;
}

void kimonobird::dying()
{
	state = 5;
	timeLeft = 20;
	order = 0;
}

void kimonobird::update(SDL_Rect p_rect, vector<entity> &wall, float currentTime)
{
	timeLeft = max(timeLeft, 0);
	// cout << timeLeft << ' ' << order << endl;
	if (timeLeft == 0)
	{
		if (Distance(pos, vector2f(p_rect.x, p_rect.y)) > aggroRadius)
		{
			state = 0;
			timeLeft = 1;
		}
		else
		{
			int value = mt() % 10;
			order = 0;

			if (value < 4)
			{
				state = 1;
				timeLeft = 6;

				tie(directionX, directionY) = RelativePostion(hitbox, p_rect);
			}

			else
			{
				state = 3;
				timeLeft = 10;
				music.play("kimonobirdhowl", currentTime);
			}
		}
	}

	float delta = currentTime - physicUpdate;

	hitbox = SDL_Rect{0, 0, 0, 0};

	switch (state)
	{
		case 0:
			currentFrame = idle[order];
			hitbox = SDL_Rect{(int)pos.x - 42 + 40, (int)pos.y - 42 + 14, 16, 34};
			
			break;
		case 1:
			currentFrame = idle[order];
			if (directionX != -1) moveX((directionX == 2 ? speed : -speed) * delta, getLegRect(), wall);
			if (directionY != -1) moveY((directionY ? speed : -speed) * delta, getLegRect(), wall);
			hitbox = SDL_Rect{(int)pos.x - 42 + 40, (int)pos.y - 42 + 14, 16, 34};
			break;
		case 3:
			if (order == 0) currentFrame = cast[0];
			else currentFrame = cast[(order - 1) % 3 + 1];

			break;
		case 4:
			currentFrame = hurt; 
			break;

		case 5:
			currentFrame = die[order];
			break;
	}
	physicUpdate = currentTime;

	if (currentTime - lastUpdate > 150)
	{
		projectileHitbox.clear();
		order++;
		timeLeft--;

		switch (state)
		{
			case 0:
				order %= 6;
				
				break;
			case 1:
				order %= 6;
				if (timeLeft == 0) timeLeft = 12, state = 0;
				
				break;
			case 3:
				if (order == 4)
				{
					projectile = entity(vector2f(p_rect.x, p_rect.y - 48), tex, bolt[0]);
					music.play("Bolt", currentTime);
				}
				else if (order > 4)
					projectile.setRect(bolt[order - 4]);

				if (timeLeft == 0) projectile.setRect(SDL_Rect{0, 0, 0, 0}), timeLeft = 12, state = 0, order = 0;

				if (order >= 6 && order <= 7)
					projectileHitbox.emplace_back(SDL_Rect{(int)projectile.getPos().x, (int)projectile.getPos().y + 48, 12, 12});

				break;
			case 5:
				if (timeLeft == 0) 
				{
					pos = {0, 0};
					isDeath = true;
				}
				break;
		}

		lastUpdate = currentTime;
	}
}

waterthug::waterthug(vector2f p_pos)
	:enemy(p_pos)
{
	direction = directionX = directionY = state = timeLeft = order = 0; speed = 0.05;
	hp = 145;
	hitbox = SDL_Rect{(int)pos.x - 42 + 40, (int)pos.y - 42 + 28, 16, 18};
	tex = window.loadTexture("res/image/enemy/waterthug.png");

	idle[0].emplace_back(SDL_Rect{0, 64, 96, 64});
	idle[1].emplace_back(SDL_Rect{0, 0, 96, 64});
	idle[2].emplace_back(SDL_Rect{0, 128, 96, 64});
	idle[3].emplace_back(SDL_Rect{0, 128, 96, 64});

	throwing[0].emplace_back(SDL_Rect{0, 256, 96, 64});
	throwing[1].emplace_back(SDL_Rect{0, 192, 96, 64});
	throwing[2].emplace_back(SDL_Rect{0, 320, 96, 64});
	throwing[3].emplace_back(SDL_Rect{0, 320, 96, 64});

	trident.emplace_back(SDL_Rect{0, 384, 96, 64});

	circle.emplace_back(SDL_Rect{0, 448, 96, 64});

	hurt = SDL_Rect{0, 512, 96, 64};

	die.emplace_back(SDL_Rect{0, 576, 96, 64});

	for (int i = 0; i < 4; i++) {
		CreateSprite(idle[i], 4);
		CreateSprite(throwing[i], 2);
	}

	CreateSprite(trident, 4);
	CreateSprite(circle, 4);
	CreateSprite(die, 7);
}

SDL_Rect waterthug::getLegRect()
{
	SDL_Rect p_rect = getRect();
	p_rect.x = p_rect.x - 4;
	p_rect.w = 20;
	p_rect.h = 6;
	return p_rect;
}

void waterthug::hurting()
{
	state = 4;
	timeLeft = 10;
}

void waterthug::dying()
{
	state = 5;
	timeLeft = 7;
	order = 0;
}

void waterthug::update(SDL_Rect p_rect, vector<entity> &wall, float currentTime)
{
	timeLeft = max(timeLeft, 0);
	if (timeLeft == 0)
	{
		tie(directionX, directionY) = RelativePostion(hitbox, p_rect);

		if (directionX != -1 && directionY == -1) direction = directionX;
		if (directionX == -1 && directionY != -1) direction = directionY;
		if (directionX != -1 && directionY != -1) direction = (mt() & 1 ? directionX : directionY);

		if (direction == 3) setFlip(SDL_FLIP_HORIZONTAL);
		else setFlip(SDL_FLIP_NONE);

		if (Distance(pos, vector2f(p_rect.x, p_rect.y)) > aggroRadius)
		{
			state = 0;
			timeLeft = 1;
		}
		else
		{
			int value = mt() % 10;
			order = 0;

			if (value < 4)
			{
				state = 1;
				timeLeft = 3;
			}

			else if (value < 7)
			{
				state = 2;
				timeLeft = 5;
				music.play("cut", currentTime);
			}

			else
			{
				state = 3;
				timeLeft = 4;
				music.play("circle", currentTime);
			}
		}
	}

	float delta = currentTime - physicUpdate;
	hitbox = SDL_Rect{0, 0, 0, 0};

	switch (state)
	{
		case 0:
			currentFrame = idle[direction][order];
			hitbox = SDL_Rect{(int)pos.x - 42 + 40, (int)pos.y - 42 + 28, 16, 18};
			break;

		case 1:
			currentFrame = idle[direction][order];
			if (directionX != -1) moveX((directionX == 2 ? speed : -speed) * delta, getLegRect(), wall);
			if (directionY != -1) moveY((directionY ? speed : -speed) * delta, getLegRect(), wall);
			hitbox = SDL_Rect{(int)pos.x - 42 + 40, (int)pos.y - 42 + 28, 16, 18};
			break;

		case 2:
			projectile.setFlip(SDL_FLIP_NONE);
			if (order <= 1) currentFrame = throwing[direction][order];
			else currentFrame = idle[direction][order % 4];
			hitbox = SDL_Rect{(int)pos.x - 42 + 40, (int)pos.y - 42 + 28, 16, 18};
			// cout << trident[direction].x << ' ' << trident[direction].y << endl;
			// if (projectile.flip == SDL_FLIP_HORIZONTAL) cout << "bad" << endl;
			if (order == 0) projectile = entity(pos, tex, trident[direction]);
			else 
			{
				float speed = 0.15;
				if (direction > 1)
				{
					if (order == 4 || projectile.moveX((directionX == 2 ? speed : -speed) * delta, SDL_Rect{(int)projectile.getPos().x + 4, (int)projectile.getPos().y - 11, 8, 16}, wall)) projectile.setPos({0, 0});
				}
				else
				{
					if (order == 4 || projectile.moveY((directionY ? speed : -speed) * delta, SDL_Rect{(int)projectile.getPos().x + 4, (int)projectile.getPos().y - 11, 8, 16}, wall)) projectile.setPos({0, 0});
				} 
			}
			break;

		case 3:
			currentFrame = circle[order % 4];
			break;

		case 4:
			currentFrame = hurt;
			break;

		case 5:
			currentFrame = die[order];
			break;
	}
	physicUpdate = currentTime;

	if (currentTime - lastUpdate > 200)
	{
		projectileHitbox.clear();
		order++;
		timeLeft--;

		SDL_Rect p_rect;

		switch (state)
		{
			case 0:
				order %= 4;
				break;

			case 1:
				order %= 4;
				break;

			case 2:
				if (direction <= 1) projectileHitbox.push_back(SDL_Rect{(int)projectile.getPos().x + 4, (int)projectile.getPos().y - 11, 8, 16});
				else projectileHitbox.push_back(SDL_Rect{(int)projectile.getPos().x - 4, (int)projectile.getPos().y - 4, 16, 8});
				if (timeLeft == 0) timeLeft = 8, state = 0, order = 0;
				break;

			case 3:
				p_rect = getLegRect();
				if (order % 4 == 0) projectileHitbox.emplace_back(SDL_Rect{p_rect.x, p_rect.y, 12, 22});
				if (order % 4 == 1) projectileHitbox.emplace_back(SDL_Rect{p_rect.x + 22, p_rect.y - 12, 22, 12});
				if (order % 4 == 2) projectileHitbox.emplace_back(SDL_Rect{p_rect.x, p_rect.y - 22, 12, 22});
				if (order % 4 == 3) projectileHitbox.emplace_back(SDL_Rect{p_rect.x - 22, p_rect.y - 12, 22, 12});
				if (timeLeft == 0) timeLeft = 8, state = 0, order = 0;
				break;

			case 5:	
				if (timeLeft == 0)
				{
					pos = {0, 0};
					isDeath = true;
				}
				break;
		}

		lastUpdate = currentTime;
	}

}