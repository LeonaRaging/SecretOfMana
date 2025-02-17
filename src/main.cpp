#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>

#include "RenderWindow.hpp"
#include "Entity.hpp"

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
	vector<Entity> entities = {Entity(vector2f())};
	
	while (gameRunning) 
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				gameRunning = false;

			window.init();

			
			
			for (Entity &e : entities)
				window.render(e);


			window.display();
		}
		SDL_Delay(100);
	}

	window.cleanUp();
	SDL_Quit();

	return 0;
}