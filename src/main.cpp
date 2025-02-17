#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>
#include <math.h>

#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "default.hpp"

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

	vector<Entity> entities = {Entity(vector2f(100, 100), playerTexture)};
	
	while (gameRunning) 
	{
		Uint32 Start = SDL_GetPerformanceCounter();

		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				gameRunning = false;
		}

		window.init();

		entities[0].update();
		
		for (Entity &e : entities)
			window.render(e);

		window.display();

		Uint32 End = SDL_GetPerformanceCounter();

		float elapsedMS = (End - Start) / (float)SDL_GetPerformanceFrequency() * 1000.0f;

		SDL_Delay(floor(16.666f - elapsedMS));
	}

	window.cleanUp();
	SDL_Quit();

	return 0;
}