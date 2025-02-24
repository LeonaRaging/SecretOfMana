#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "entity.hpp"

class RenderWindow 
{
public:
	RenderWindow(const char* p_title);
	void init();
	SDL_Texture* loadTexture(const char* p_filePath);
	void render(entity &e, SDL_Rect &camera);
	void render_player(entity &e, SDL_Rect &camera);
	void fade(int &isFading, int &alpha);
	void display();
	void cleanUp();
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
};

bool isCollision(SDL_Rect a, vector<entity>& b);
