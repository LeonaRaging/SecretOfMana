#include <iostream>
#include "RenderWindow.hpp"

using namespace std;

RenderWindow::RenderWindow(const char* p_title)
	:window(NULL), renderer(NULL)
{
	window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, LEVEL_WIDTH, LEVEL_HEIGHT, SDL_WINDOW_SHOWN);
	
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

SDL_Texture* RenderWindow::loadTexture(const char* p_filePath)
{
	SDL_Texture* texture = NULL;
	texture = IMG_LoadTexture(renderer, p_filePath);

	if (texture == NULL)
		cout << "texture could not be loaded!, Error" << SDL_GetError() << endl;
	return texture;
}

void RenderWindow::display(vector2f p_pos)
{
	// SDL_Rect viewport;
	// viewport.x = p_pos.x - SCREEN_HEIGHT / 2;
	// viewport.y = p_pos.y - SCREEN_WIDTH / 2;
	// viewport.w = SCREEN_WIDTH;
	// viewport.h = SCREEN_HEIGHT;

	// SDL_RenderSetClipRect(renderer, &viewport);
	SDL_RenderPresent(renderer);
}

void RenderWindow::render(entity &p_entity)
{
	SDL_Rect src;
	src.x = p_entity.getCurrentFrame().x;
	src.y = p_entity.getCurrentFrame().y;
	src.w = p_entity.getCurrentFrame().w;
	src.h = p_entity.getCurrentFrame().h;

	SDL_Rect dst;
	dst.x = p_entity.getPos().x;
	dst.y = p_entity.getPos().y;
	dst.w = p_entity.getCurrentFrame().w;
	dst.h = p_entity.getCurrentFrame().h;

	SDL_RenderCopy(renderer, p_entity.getTex(), &src, &dst);
}

void RenderWindow::cleanUp()
{
	SDL_DestroyWindow(window);
}