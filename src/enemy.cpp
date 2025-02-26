#include "enemy.hpp"
#include "RenderWindow.hpp"

enemy::enemy(vector2f p_pos)
	:entity(p_pos)
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

pebbler::pebbler(vector2f p_pos, RenderWindow &window):
	enemy(p_pos)
{
	direction = directionX = directionY = state = timeLeft = order = 0; speed = 1;
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

void pebbler::update(vector2f p_pos, vector<entity> &wall, float currentTime)
{
	if (timeLeft == 0)
	{
		if (Distance(pos, p_pos) > aggroRadius)
		{
			state = 0;
			speed = 0;
			timeLeft = 16;
		}
		else
		{
			if (!isSpawn)
			{
				order = 0;
				state = 2;
				timeLeft = 12;
				isSpawn = true;
			}

			else
			{
				order = 0; 
				state = 1;
				speed = 2;
				timeLeft = 6;

				tie(directionX, directionY) = RelativePostion(pos, p_pos);
				direction = (rand() & 1 ? directionX : directionY);
				if (directionY == 3) setFlip(SDL_FLIP_HORIZONTAL);
				else setFlip(SDL_FLIP_NONE);
			}
		}

	}

	hitbox = SDL_Rect{0, 0, 0, 0};
	cout << state << endl;
	switch (state)
	{
		case 0:
			currentFrame = idle[order];
			hitbox = SDL_Rect{pos.x - 42 + 38, pos.y - 42 + 21, 20, 27};
			break;
		case 1:
			currentFrame = spin[direction][order];

			moveX(directionX == 2 ? speed : -speed, getLegRect(), wall);
			moveY(directionY ? speed : -speed, getLegRect(), wall);
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
				}

				break;
		}

		lastUpdate = currentTime;
	}
	if (!isSpawn) currentFrame = dig[0];
}

kimonobird::kimonobird(vector2f p_pos, RenderWindow &window)
	:enemy(p_pos)
{
	direction = directionX = directionY = state = timeLeft = order = 0; speed = 1;
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

void kimonobird::update(vector2f p_pos, vector<entity> &wall, float currentTime)
{
	if (timeLeft == 0)
	{
		if (Distance(pos, p_pos) > aggroRadius)
		{
			state = 0;
			timeLeft = 6;
		}
		else
		{
			int value = mt() % 10;
			order = 0;

			if (value < 5)
			{
				state = 1;
				timeLeft = 6;

				tie(directionX, directionY) = RelativePostion(pos, p_pos);
			}

			else if (value < 0)
			{
				// state = 2;
			}

			else
			{
				state = 3;
				timeLeft = 10;
			}
		}
	}
	// cout << state << endl;

	hitbox = SDL_Rect{0, 0, 0, 0};

	switch (state)
	{
		case 0:
			currentFrame = idle[order];
			hitbox = SDL_Rect{pos.x - 42 + 40, pos.y - 42 + 14, 16, 34};
			
			break;
		case 1:
			currentFrame = idle[order];
			moveX(directionX == 2 ? speed : -speed, getLegRect(), wall);
			moveY(directionY ? speed : -speed, getLegRect(), wall);
			
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

	if (currentTime - lastUpdate > 150)
	{
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
					projectile = entity(vector2f(p_pos.x, p_pos.y - 64), tex, bolt[0]);
				}
				else if (order > 4)
					projectile.setRect(bolt[order - 4]);

				if (timeLeft == 0) projectile.setRect(SDL_Rect{0, 0, 0, 0}), timeLeft = 12, state = 0, order = 0;

				break;
			case 5:
				if (timeLeft == 0)
					pos = {0, 0};
		}

		lastUpdate = currentTime;
	}
}