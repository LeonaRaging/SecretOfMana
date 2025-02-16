#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Entity.hpp"

class RenderWindow 
{
public:
	RenderWindow(const char* p_title, int p_w, int p_h);
	void init();
	void render(Entity &e);
	void display();
	void cleanUp();
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
};
