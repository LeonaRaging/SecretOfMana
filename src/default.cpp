#include "default.hpp"

bool isCollision(SDL_Rect a, vector<entity>& b)
{
	for (int j = 0; j < (int)b.size(); j++)
	{
		SDL_Rect cur = b[j].getRect();
		if (SDL_HasIntersection(&a, &cur) == SDL_TRUE) {
			std::cout << "wall hit" << endl;
			return true;
		}
	}
	return false;
}

void update(SDL_Rect &camera, player &p)
{
	camera.x = p.getPos().x - SCREEN_HEIGHT / 2;
	camera.y = p.getPos().y - SCREEN_WIDTH / 2;
	camera.w = SCREEN_WIDTH;
	camera.h = SCREEN_HEIGHT;

	if (camera.x < 0) camera.x = 0;
	if (camera.x > LEVEL_HEIGHT - camera.x) camera.x = LEVEL_HEIGHT - camera.x;
	if (camera.y < 0) camera.y = 0;
	if (camera.y > LEVEL_WIDTH - camera.y) camera.y = LEVEL_WIDTH - camera.y;
}