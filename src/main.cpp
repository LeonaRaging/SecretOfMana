#include "RenderWindow.hpp"
#include "entity.hpp"
#include "player.hpp"
#include "enemy.hpp"
#include "map.hpp"
#include "audio.hpp"

using namespace std;

int main(int argc, char* args[]) 
{
	if (SDL_Init(SDL_INIT_EVERYTHING) > 0)
		cout << "SDL_Init has failed, Error: " << SDL_GetError() << endl;

	if (!(IMG_Init(IMG_INIT_PNG)))
		cout << "IMG_Init has failed, Error: " << IMG_GetError() << endl;

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		cout << "Mix_OpenAudio has failed, Error: " << Mix_GetError() << endl;

	music.init();
	window.fontInit();
	init();

	bool gameRunning = true, pause = false;
	gameStart = false; isFading = alpha = 0;
	SDL_Event event;
	player p;
	map maps[6];
	int currentMap;

	auto resetGame = [&]()
	{
		p = player(vector2f(248, 586)); 
		maps[1] = dragon_cave_1();
		maps[2] = dragon_cave_2();
		maps[3] = dragon_cave_3();
		maps[4] = dragon_cave_4();
		maps[5] = dragon_cave_5();
		currentMap = 1;
	};

	while (gameRunning) 
	{
		Uint32 Start = SDL_GetPerformanceCounter();

		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				gameRunning = false;
			
			else if (event.type == SDL_WINDOWEVENT) 
			{
				switch (event.window.event)
				{
					case SDL_WINDOWEVENT_FOCUS_LOST: 
						pause = true;
						cout << "window lost focus!" << endl;
						break;
					case SDL_WINDOWEVENT_FOCUS_GAINED:
						pause = false;
						cout << "window gain focus!" << endl;
						break;
					case SDL_WINDOWEVENT_MOVED:
						pause = true;
						cout << "window is moving!" << endl;
						break;
				}
			}

			else if (gameStart == false && event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN)
			{
				gameStart = true;
				isFading = 1;
				Mix_PlayMusic(music.ingame, -1);
				resetGame();
			}
		}

		if (pause) continue;



		float Perf = SDL_GetPerformanceFrequency();
		float currentTime = SDL_GetPerformanceCounter() / Perf * 1000.0f;

		if (gameStart) currentMap = maps[currentMap].checkPortals(p, currentTime);

		if (isFading == 1) {
			window.fade(isFading, alpha);
		}
		
		else 
		{
			window.init();

			if (!gameStart)
			{
				camera.x = camera.y = 0;
				SDL_Texture* title = window.loadTexture("res/image/miscellaneous/title.png");
				entity p_entity(vector2f(0, 0), title, 0, 0, 256, 191);
				window.render_map(p_entity);
			}

			else
			{

				for (enemy *e : maps[currentMap].enemies) {
					if (kimonobird* p_enemy = dynamic_cast<kimonobird*>(e))
					{
						p_enemy->update(p.getHitbox(), maps[currentMap].tiles, currentTime);
					}

					if (pebbler* p_enemy = dynamic_cast<pebbler*>(e))
					{
						p_enemy->update(p.getHitbox(), maps[currentMap].tiles, currentTime);
					}

					if (waterthug* p_enemy = dynamic_cast<waterthug*>(e))
					{
						p_enemy->update(p.getHitbox(), maps[currentMap].tiles, currentTime);
					}
				}

				for (int index = 0; index < (int)maps[currentMap].enemies.size(); index++)
				{
					if (maps[currentMap].enemies[index]->isDeath) 
					{
						swap(maps[currentMap].enemies[index], maps[currentMap].enemies.back());
						maps[currentMap].enemies.pop_back();
						cout << maps[currentMap].enemies.size() << endl;
						index--;
					}
				}

				p.update(maps[currentMap].tiles, maps[currentMap].enemies, currentTime);
				p.update_camera();

				for (int i = 0; i < (int)maps[currentMap].tilesIndex.size(); i++)
					for (int j = 0; j < (int)maps[currentMap].tilesIndex[i].size(); j++)
					{
						entity p_entity = entity(vector2f(j * 16, i * 16), tilesTexture, mapTiles[maps[currentMap].tilesIndex[i][j]]);
						window.render_map(p_entity);
					}

				for (auto &e : maps[currentMap].enemies) {
					if ((*e).getPos().y < p.getPos().y)
						window.render_entity(*e);
				}

				window.render_entity(p);

				for (auto &e : maps[currentMap].enemies) {
					if ((*e).getPos().y >= p.getPos().y)
						window.render_entity(*e);
					window.render_entity((*e).projectile);
					// for (SDL_Rect p_rect : (*e).projectileHitbox)
					// {
					// 	SDL_Texture* tex = window.loadTexture("res/image/miscellaneous/rect.png");
					// 	entity p_entity({p_rect.x, p_rect.y}, tex, 0, 0, p_rect.w, p_rect.h);
					// 	window.render_map(p_entity);
					// }
				}

				for (int index = 0; index < (int)number.size(); index++) {

					window.render_font(number[index].value, number[index].pos, 0);

					if (currentTime - number[index].lastUpdate > 100) 
					{
						number[index].timeLeft--;
						if (number[index].timeLeft >= 5) number[index].pos.y += 2;
						else number[index].pos.y -= 1;

						
						number[index].lastUpdate = currentTime;
						
						if (number[index].timeLeft == 0)
						{
							swap(number[index], number.back());
							number.pop_back();
							index--;
						}

					}
				}

				window.render_font(p.getHp(), vector2f(camera.x + 34 - getNumberLength(p.getHp()) * 8, camera.y + SCREEN_HEIGHT - 20), 1);
				window.render_font(-1, vector2f(camera.x + 34, camera.y + SCREEN_HEIGHT - 20), 1);
				window.render_font(250, vector2f(camera.x + 42, camera.y + SCREEN_HEIGHT - 20), 1);
			}


			if (isFading == 2)
			{
				window.fade(isFading, alpha);
			}
		}		

		window.display();

		Uint32 End = SDL_GetPerformanceCounter();

		Perf = SDL_GetPerformanceFrequency();
		float elapsedMS = (End - Start) / Perf * 1000.0f;

		if (elapsedMS < 16.666f) SDL_Delay(floor(16.666f - elapsedMS));
	}

	window.cleanUp();
	SDL_Quit();

	return 0;
}