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

	SDL_Event event;
	SDL_Texture* rectTexture = window.loadTexture("res/image/rect.png");

	player p(vector2f(300, 500), window); 
	SDL_Rect camera;

	init(window);
	vector<entity> entities;
	vector<enemy> enemies;
	enemies.emplace_back(vector2f(300, 600), rectTexture);
	
	map p_map = createMap(window, 5, 18, 17);

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

		window.init();

		entities.clear();

		float Perf = SDL_GetPerformanceFrequency();
		if (Perf == 0) Perf = 1;
		float currentTime = SDL_GetPerformanceCounter() / (float)Perf * 1000.0f;

		p.update(p_map.tiles, enemies, currentTime);
		p.update_camera(camera);

		entities.emplace_back(p.getPos(), rectTexture, 0, 0, 12, 6);

		for (int i = 0; i < (int)p_map.tilesIndex.size(); i++)
			for (int j = 0; j < (int)p_map.tilesIndex[i].size(); j++)
			{
				entity p_entity = entity(vector2f(j * 16, i * 16), tilesTexture, mapTiles[p_map.tilesIndex[i][j]]);
				window.render(p_entity, camera);
			}
		// system("pause");
		// entity p_entity = entity(vector2f(0, 0), tilesTexture, 224, 64, 16, 16);
		// window.render(p_entity, camera);

		for (entity &e: p_map.tiles)
			window.render(e, camera);

		for (entity &e : entities)
			window.render(e, camera);
		for (enemy &e : enemies)
			window.render(e, camera);

		window.render_player(p, camera);

		window.display(p.getPos());

		Uint32 End = SDL_GetPerformanceCounter();

		Perf = SDL_GetPerformanceFrequency();
		if (Perf == 0) Perf = 1;
		float elapsedMS = (End - Start) / (float)Perf * 1000.0f;

		SDL_Delay(floor(16.666f - elapsedMS));
		cout << elapsedMS << endl;
	}

	window.cleanUp();
	SDL_Quit();

	return 0;
}