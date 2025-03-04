#include "RenderWindow.hpp"

using namespace std;

RenderWindow window("GAME");

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

	if (loadedSurface == NULL) {
		cout << "image could not be loaded!, Error" << SDL_GetError() << endl;
		system("pause");
	}

	SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 128, 255, 128));

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);

	SDL_FreeSurface(loadedSurface);

	return texture;
}

void RenderWindow::display()
{
	SDL_RenderPresent(renderer);
}

void RenderWindow::render_map(entity &p_entity)
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

void RenderWindow::render_entity(entity &p_entity)
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

void RenderWindow::fontInit()
{
	for (int i = 0; i < 10; i++)
	{
		numRect[i] = SDL_Rect{8 * i, 0, 8, 8};
		playerRect[i] = SDL_Rect{8 * i, 8, 8, 8};
	}
	fontTexture = loadTexture("res/image/miscellaneous/font.png");
}

void RenderWindow::render_font(int number, vector2f p_pos, bool isPlayer)
{
	// cout << number << ' ' << p_pos.x << ' ' << p_pos.y << endl;
	if (number == -1) 
	{
		entity p_entity(p_pos, fontTexture, 80, 8, 8, 8);
		render_map(p_entity);
		return;
	}

	vector<int> p_vector;
	if (number == 0) p_vector.push_back(0);
	while (number > 0)
	{
		p_vector.push_back(number % 10);
		number /= 10;
	}

	reverse(p_vector.begin(), p_vector.end());

	for (int index = 0; index < (int)p_vector.size(); index++)
	{
		entity p_entity(vector2f(p_pos.x + index * 8, p_pos.y), fontTexture, numRect[p_vector[index]]);
		if (isPlayer) p_entity.setRect(playerRect[p_vector[index]]);
		render_map(p_entity);
	}
}

void RenderWindow::fade(int &isFading, int &alpha)
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, alpha);
	SDL_RenderFillRect(renderer, NULL);
	int speed = 5;

	if (isFading == 1)
	{
		alpha += speed;
		alpha = min(alpha, 255);
		if (alpha == 255) isFading = 2;
	}
	else
	{
		alpha -= speed;
		alpha = max(alpha, 0);
		if (alpha == 0) isFading = 0;
	}
}


void RenderWindow::cleanUp()
{
	SDL_DestroyWindow(window);
}
