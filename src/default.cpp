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