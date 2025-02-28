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
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_RenderClear(renderer);
	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}

SDL_Texture* RenderWindow::loadTexture(const char* p_filePath)
{
	SDL_Surface* loadedSurface = IMG_Load(p_filePath);

	if (loadedSurface == NULL)
		cout << "image could not be loaded!, Error" << SDL_GetError() << endl;

	SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 128, 255, 128));

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);

	SDL_FreeSurface(loadedSurface);

	return texture;
}

void RenderWindow::display()
{
	SDL_RenderPresent(renderer);
}

void RenderWindow::render_map(entity &p_entity, SDL_Rect &camera)
{
	SDL_Rect src;
	src.x = p_entity.getCurrentFrame().x;
	src.y = p_entity.getCurrentFrame().y;
	src.w = p_entity.getCurrentFrame().w;
	src.h = p_entity.getCurrentFrame().h;

	SDL_Rect dst;
	dst.x = p_entity.getPos().x - camera.x;
	dst.y = p_entity.getPos().y - camera.y;
	dst.w = p_entity.getCurrentFrame().w;
	dst.h = p_entity.getCurrentFrame().h;

	SDL_RenderCopy(renderer, p_entity.getTex(), &src, &dst);
}

void RenderWindow::render_entity(entity &p_entity, SDL_Rect &camera)
{
	SDL_Rect src;
	src.x = p_entity.getCurrentFrame().x;
	src.y = p_entity.getCurrentFrame().y;
	src.w = p_entity.getCurrentFrame().w;
	src.h = p_entity.getCurrentFrame().h;

	SDL_Rect dst;
	dst.x = p_entity.getPos().x - 42 - camera.x;
	dst.y = p_entity.getPos().y - 42 - camera.y;
	dst.w = p_entity.getCurrentFrame().w;
	dst.h = p_entity.getCurrentFrame().h;

	SDL_RenderCopyEx(renderer, p_entity.getTex(), &src, &dst, 0, NULL, p_entity.getFlip());
}

void RenderWindow::fade(int &isFading, int &alpha)
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, alpha);
	SDL_RenderFillRect(renderer, NULL);
	
	int speed = 5;

	if (isFading == 1)
	{
		alpha += speed;
		if (alpha >= 255) isFading = 2;
	}
	else
	{
		alpha -= speed;
		if (alpha <= 0) isFading = 0;
	}
}


void RenderWindow::cleanUp()
{
	SDL_DestroyWindow(window);
}