#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "default.hpp"
#include "entity.hpp"

class RenderWindow 
{
public:
	RenderWindow(const char* p_title);
	void init();
	SDL_Texture* loadTexture(const char* p_filePath);
	void render(entity &e, SDL_Rect &camera);
	void display(vector2f p_pos);
	void cleanUp();
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
};
