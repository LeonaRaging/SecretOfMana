#include "Entity.hpp"

Entity::Entity(int p_x, int p_y, int p_w, int p_h)
	:x(p_x), y(p_y), w(p_w), h(p_h)
{

}

int Entity::getX() 
{
	return x;
}

int Entity::getY() 
{
	return y;
}

int Entity::getW() 
{
	return w;
}

int Entity::getH() 
{
	return h;
}

void Entity::move(int p_x, int p_y)
{
	x += p_x; y += p_y;
}