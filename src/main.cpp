#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>
#include <math.h>

#include "RenderWindow.hpp"
#include "entity.hpp"
#include "player.hpp"
#include "enemy.hpp"
#include "map.hpp"

using namespace std;

int main(int argc, char* args[]) 
{
	if (SDL_Init(SDL_INIT_EVERYTHING) > 0)
		cout << "SDL_Init has failed, Error: " << SDL_GetError() << endl;

	if (!(IMG_Init(IMG_INIT_PNG)))
		cout << "IMG_Init has failed, Error: " << SDL_GetError() << endl;
	RenderWindow window("GAME");

	bool gameRunning = true, pause = false;
	int isFading = 0, alpha;

	SDL_Event event;

	player p(vector2f(248, 586), window); 
	SDL_Rect camera;

	init(window);
	
	map maps[6];
	maps[1] = dragon_cave_1(window);
	maps[2] = dragon_cave_2(window);
	maps[3] = dragon_cave_3(window);
	maps[4] = dragon_cave_4(window);
	maps[5] = dragon_cave_5(window);
	map currentMap = maps[1];

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
		}

		if (pause) continue;



		float Perf = SDL_GetPerformanceFrequency();
		if (Perf == 0) Perf = 1;
		float currentTime = SDL_GetPerformanceCounter() / (float)Perf * 1000.0f;

		currentMap = maps[currentMap.checkPortals(p, isFading, alpha)];

		if (isFading == 1) {
			window.fade(isFading, alpha);
		}
		
		else 
		{
			window.init();

			for (enemy *e : currentMap.enemies) {
				if (kimonobird* p_enemy = dynamic_cast<kimonobird*>(e))
				{
					p_enemy->update(p.getPos(), currentMap.tiles, currentTime);
				}

				if (pebbler* p_enemy = dynamic_cast<pebbler*>(e))
				{
					p_enemy->update(p.getPos(), currentMap.tiles, currentTime);
				}

				if (waterthug* p_enemy = dynamic_cast<waterthug*>(e))
				{
					p_enemy->update(p.getPos(), currentMap.tiles, currentTime);
				}
			}
						
			p.update(currentMap.tiles, currentMap.enemies, currentTime);
			p.update_camera(camera);

			for (int i = 0; i < (int)currentMap.tilesIndex.size(); i++)
				for (int j = 0; j < (int)currentMap.tilesIndex[i].size(); j++)
				{
					entity p_entity = entity(vector2f(j * 16, i * 16), tilesTexture, mapTiles[currentMap.tilesIndex[i][j]]);
					window.render_map(p_entity, camera);
				}

			// for (entity &e: currentMap.tiles)
				// window.render(e, camera);

			for (auto &e : currentMap.enemies)
				if ((*e).getPos().y < p.getPos().y)
					window.render_entity(*e, camera);

			SDL_Texture* rectTexture = window.loadTexture("res/image/rect.png");
			// for (enemy *e : currentMap.enemies) {
			// 	entity p_entity = entity(dynamic_cast<pebbler*>(e)->getPos(), rectTexture, dynamic_cast<pebbler*>(e)->getLegRect());
			// 	window.render_map(p_entity, camera);
			// 	cout << p_entity.getPos().x << ' ' << p_entity.getPos().y << endl;
			// }

			window.render_entity(p, camera);

			for (auto &e : currentMap.enemies) {
				if ((*e).getPos().y >= p.getPos().y)
					window.render_entity(*e, camera);
				window.render_entity((*e).projectile, camera);

				for (SDL_Rect p_rect : e->projectileHitbox)
				{
					entity p_entity(vector2f(p_rect.x, p_rect.y), rectTexture, 0, 0, p_rect.w, p_rect.h);
					window.render_map(p_entity, camera);
				}
			}

			if (isFading == 2) window.fade(isFading, alpha);
		}		

		window.display();

		Uint32 End = SDL_GetPerformanceCounter();

		Perf = SDL_GetPerformanceFrequency();
		if (Perf == 0) Perf = 1;
		float elapsedMS = (End - Start) / (float)Perf * 1000.0f;

		if (elapsedMS < 16.666f) SDL_Delay(floor(16.666f - elapsedMS));
		// cout << elapsedMS << endl;
	}

	window.cleanUp();
	SDL_Quit();

	return 0;
}