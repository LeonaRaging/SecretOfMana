#pragma once

#include "RenderWindow.hpp"
#include "player.hpp"

extern SDL_Texture* tilesTexture;
extern vector<SDL_Rect> mapTiles;
extern vector<SDL_Rect> tileHitbox[200];

class portal {
	public:
	portal(SDL_Rect p_rect, int p_int, vector2f p_vector);
	SDL_Rect area;
	int targetMap;
	vector2f targetPosition;
};

class map
{
public:
	map();
	map(vector<vector<int>> p_vector, vector<entity> p_tiles);
	vector<vector<int>> tilesIndex;
	vector<entity> tiles;
	vector<portal> portals;
	int checkPortals(player &p_player, float currentTime);
	int index;
	vector<enemy*> enemies;
private:
};

void init();

map createMap(int index, int width, int height);

map dragon_cave_1();
map dragon_cave_2();
map dragon_cave_3();
map dragon_cave_4();
map dragon_cave_5();
map boss_arena();