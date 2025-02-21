#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>
#include <math.h>

#include "RenderWindow.hpp"
#include "entity.hpp"
#include "default.hpp"
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
	SDL_Texture* playerTexture = window.loadTexture("res/image/player.png");
	SDL_Texture* rectTexture = window.loadTexture("res/image/rect.png");

	player p(vector2f(300, 500), playerTexture); 
	SDL_Rect camera;

	vector<entity> entities;
	
	map p_map = dragon_cave_2(window);

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

		float currentTime = SDL_GetPerformanceCounter() / (float)SDL_GetPerformanceFrequency() * 1000.0f;

		p.update(p_map.tiles, currentTime);
		update(camera, p);

		entities.push_back(p);
		
		// entities.emplace_back(vector2f(p.getPos().x, p.getPos().y + 26), rectTexture, 0, 0, p.getLegRect().w, 6);

		window.render(p_map.e, camera);

		// for (entity &e: p_map.tiles)
			// window.render(e, camera);

		for (entity &e : entities)
			window.render(e, camera);

		window.display(p.getPos());

		Uint32 End = SDL_GetPerformanceCounter();

		float elapsedMS = (End - Start) / (float)SDL_GetPerformanceFrequency() * 1000.0f;

		SDL_Delay(floor(16.666f - elapsedMS));
		cout << elapsedMS << endl;
	}

	window.cleanUp();
	SDL_Quit();

	return 0;
}