#pragma once

#include "RenderWindow.hpp"
#include "entity.hpp"

class map
{
public:
	map(entity p_e, vector<entity> p_tiles);
	entity e;
	vector<entity> tiles;

private:
};

map dragon_cave_2(RenderWindow &window);