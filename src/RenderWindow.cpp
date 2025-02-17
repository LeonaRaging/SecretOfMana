#include <iostream>
#include "RenderWindow.hpp"

using namespace std;

RenderWindow::RenderWindow(const char* p_title)
	:window(NULL), renderer(NULL)
{
	window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	
	if (window == NULL) {
		cout << "window could not be created!, Error: " << SDL_GetError() << endl;
	}	

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

void RenderWindow::init() 
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
}

void RenderWindow::display()
{
	SDL_RenderPresent(renderer);
}

void RenderWindow::render(Entity &e)
{
	SDL_Rect rect = e.getCurrentFrame();

	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_RenderDrawRect(renderer, &rect);
}

void RenderWindow::cleanUp()
{
	SDL_DestroyWindow(window);
}