#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "default.hpp"
#include "Entity.hpp"

class RenderWindow 
{
public:
	RenderWindow(const char* p_title);
	void init();
	void render(Entity &e);
	void display();
	void cleanUp();
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
};
