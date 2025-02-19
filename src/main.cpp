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

	bool gameRunning = true;

	SDL_Event event;
	SDL_Texture* playerTexture = window.loadTexture("res/image/player.png");

	player p(vector2f(300, 500), playerTexture, 19, 32, 16, 32); 

	vector<entity> entities;
	
	map p_map = dragon_cave_2(window);

	while (gameRunning) 
	{
		Uint32 Start = SDL_GetPerformanceCounter();

		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				gameRunning = false;
		}

		window.init();

		entities.clear();

		p.update(p_map.tiles);
		entities.push_back(p);

		window.render(p_map.e);

		for (entity &e: p_map.tiles)
			window.render(e);
		for (entity &e : entities)
			window.render(e);

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