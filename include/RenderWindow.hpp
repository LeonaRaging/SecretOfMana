#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "entity.hpp"

class RenderWindow 
{
public:
	RenderWindow(const char* p_title);
	void init();
	void fontInit();
	SDL_Texture* loadTexture(const char* p_filePath);
	void render_map(entity &e);
	void render_entity(entity &e);
	void render_font(int number, vector2f p_pos, bool isPlayer);
	void fade(int &isFading, int &alpha);
	void display();
	void cleanUp();
private:
	SDL_Texture* fontTexture;
	SDL_Rect numRect[10], playerRect[10];
	SDL_Window* window;
	SDL_Renderer* renderer;
};
