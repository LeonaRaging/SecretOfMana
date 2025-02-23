#pragma once

#include "RenderWindow.hpp"
#include "entity.hpp"

extern SDL_Texture* tilesTexture;
extern vector<SDL_Rect> mapTiles;
extern vector<SDL_Rect> tileHitbox[200];

class map
{
public:
	map(vector<vector<int>> p_vector, vector<entity> p_tiles);
	vector<vector<int>> tilesIndex;
	vector<entity> tiles;
private:
};

void init(RenderWindow &window);

map createMap(RenderWindow &window, int index, int width, int height);