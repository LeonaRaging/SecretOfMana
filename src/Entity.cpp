#include "entity.hpp"

entity::entity(vector2f p_pos, SDL_Texture* p_tex, int p_x, int p_y, int p_w, int p_h):
	pos(p_pos), tex(p_tex)
{
	flip = SDL_FLIP_NONE;

	currentFrame.x = p_x;
	currentFrame.y = p_y;
	currentFrame.w = p_w;
	currentFrame.h = p_h;
}

entity::entity(vector2f p_pos, SDL_Texture* p_tex, SDL_Rect p_rect):
	pos(p_pos), tex(p_tex), currentFrame(p_rect)
{
	
}

vector2f entity::getPos()
{
	return pos;
}

SDL_Rect entity::getCurrentFrame()
{
	return currentFrame;
}

SDL_Rect entity::getRect()
{
	SDL_Rect res;
	res.x = pos.x;
	res.y = pos.y;
	res.w = currentFrame.w;
	res.h = currentFrame.h;
	return res;
}

SDL_Texture* entity::getTex()
{
	return tex;
}

SDL_RendererFlip entity::getFlip()
{
	return flip;
}

void entity::setRect(SDL_Rect p_rect)
{
	currentFrame = p_rect;
}

void entity::setFlip(SDL_RendererFlip p_flip)
{
	flip = p_flip;
}

bool isCollision(SDL_Rect a, vector<entity>& b)
{
	for (int j = 0; j < (int)b.size(); j++)
	{
		SDL_Rect cur = b[j].getRect();
		if (SDL_HasIntersection(&a, &cur) == SDL_TRUE) {
			// std::cout << "wall hit" << endl;
			return true;
		}
	}
	return false;
}

void entity::moveX(int p_speed, SDL_Rect p_rect, vector<entity> &wall)
{

	pos.x += p_speed; p_rect.x += p_speed;
	if (isCollision(p_rect, wall))
		pos.x -= p_speed;
}

void entity::moveY(int p_speed, SDL_Rect p_rect, vector<entity> &wall) 
{
	pos.y += p_speed; p_rect.y += p_speed;

	if (isCollision(p_rect, wall))
		pos.y -= p_speed;
}