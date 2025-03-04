#include "map.hpp"

SDL_Texture* tilesTexture = nullptr;
vector<SDL_Rect> mapTiles;
vector<SDL_Rect> tileHitBox[200];

void init()
{
	for (int y = 0; y < 208; y += 16)
		for (int x = 0; x < 256; x += 16) {
			mapTiles.emplace_back(SDL_Rect{ x, y, 16, 16});
		}
	tilesTexture = window.loadTexture("res/image/map/Tiles.png");
	tileHitBox[1].emplace_back(SDL_Rect{ 0, 0, 1, 16});
	tileHitBox[2].emplace_back(SDL_Rect{ 0, 0, 16, 5});
	tileHitBox[3].emplace_back(SDL_Rect{ 15, 0, 1, 16});
	tileHitBox[4].emplace_back(SDL_Rect{ 0, 0, 1, 16});
	tileHitBox[5].emplace_back(SDL_Rect{ 3, 0, 10, 16});
	tileHitBox[6].emplace_back(SDL_Rect{ 15, 0, 1, 16});
	tileHitBox[7].emplace_back(SDL_Rect{ 0, 0, 1, 16});
	tileHitBox[9].emplace_back(SDL_Rect{ 15, 0, 1, 16});
	tileHitBox[10].emplace_back(SDL_Rect{ 0, 0, 16, 16});
	tileHitBox[11].emplace_back(SDL_Rect{ 0, 0, 16, 16});
	tileHitBox[12].emplace_back(SDL_Rect{ 0, 0, 16, 16});
	tileHitBox[13].emplace_back(SDL_Rect{ 0, 0, 16, 16});
	tileHitBox[14].emplace_back(SDL_Rect{ 0, 0, 16, 16});
	tileHitBox[15].emplace_back(SDL_Rect{ 0, 0, 16, 16});
	tileHitBox[16].emplace_back(SDL_Rect{ 0, 0, 16, 16});
	tileHitBox[17].emplace_back(SDL_Rect{ 0, 0, 16, 16});
	tileHitBox[18].emplace_back(SDL_Rect{ 0, 0, 16, 16});
	tileHitBox[19].emplace_back(SDL_Rect{ 0, 0, 8, 8});
	tileHitBox[19].emplace_back(SDL_Rect{ 8, 8, 8, 8});
	tileHitBox[20].emplace_back(SDL_Rect{ 0, 0, 1, 16 });
	tileHitBox[20].emplace_back(SDL_Rect{ 0, 15, 16, 1});
	tileHitBox[20].emplace_back(SDL_Rect{ 15, 0, 1, 16 });
	tileHitBox[21].emplace_back(SDL_Rect{ 0, 8, 8, 8});
	tileHitBox[21].emplace_back(SDL_Rect{ 8, 0, 8, 8});
	tileHitBox[25].emplace_back(SDL_Rect{ 0, 0, 16, 1});
	tileHitBox[27].emplace_back(SDL_Rect{ 8, 0, 8, 8});
	tileHitBox[27].emplace_back(SDL_Rect{ 0, 8 , 8, 8});
	tileHitBox[28].emplace_back(SDL_Rect{ 0, 0, 8, 8});
	tileHitBox[28].emplace_back(SDL_Rect{ 8, 8, 8, 8});
	tileHitBox[38].emplace_back(SDL_Rect{ 0, 8, 8, 8});
	tileHitBox[38].emplace_back(SDL_Rect{ 8, 0, 8, 8});
	tileHitBox[39].emplace_back(SDL_Rect{ 0, 0, 8, 8});
	tileHitBox[39].emplace_back(SDL_Rect{ 8, 8, 8, 8});
	tileHitBox[40].emplace_back(SDL_Rect{ 0, 0, 1, 16});
	tileHitBox[41].emplace_back(SDL_Rect{ 0, 0, 16, 16});
	tileHitBox[42].emplace_back(SDL_Rect{ 15, 0, 1, 16});
	tileHitBox[52].emplace_back(SDL_Rect{ 0, 0, 8, 8});
	tileHitBox[52].emplace_back(SDL_Rect{ 8, 8, 8, 8});
	tileHitBox[56].emplace_back(SDL_Rect{ 0, 0, 8, 8});
	tileHitBox[56].emplace_back(SDL_Rect{ 8, 8, 8, 8});
	tileHitBox[57].emplace_back(SDL_Rect{ 0, 8, 16, 8});
	tileHitBox[58].emplace_back(SDL_Rect{ 8, 0, 8, 8});
	tileHitBox[58].emplace_back(SDL_Rect{ 0, 8, 8, 8});
	tileHitBox[58].emplace_back(SDL_Rect{ 15, 0, 1, 16});
	tileHitBox[71].emplace_back(SDL_Rect{ 8, 0, 8, 8});
	tileHitBox[71].emplace_back(SDL_Rect{ 0, 8, 8, 8});
	tileHitBox[76].emplace_back(SDL_Rect{ 0, 0, 8, 8});
	tileHitBox[76].emplace_back(SDL_Rect{ 8, 8, 8, 8});
	tileHitBox[121].emplace_back(SDL_Rect{ 0, 0, 16, 16});
	tileHitBox[150].emplace_back(SDL_Rect{ 0, 0, 8, 8});
	tileHitBox[150].emplace_back(SDL_Rect{ 8, 8, 8, 8});
	tileHitBox[151].emplace_back(SDL_Rect{ 8, 0, 8, 8});
	tileHitBox[151].emplace_back(SDL_Rect{ 0, 8, 8, 8});
	tileHitBox[154].emplace_back(SDL_Rect{ 0, 15, 16, 1});
	tileHitBox[170].emplace_back(SDL_Rect{ 0, 0, 8, 8});
	tileHitBox[170].emplace_back(SDL_Rect{ 8, 8, 8, 8});
}

map::map(vector<vector<int>> p_vector, vector<entity> p_tiles)
	: tilesIndex(p_vector), tiles(p_tiles)
{

}

map::map()
{

}

portal::portal(SDL_Rect p_rect, int p_int, vector2f p_vector):
	area(p_rect), targetMap(p_int), targetPosition(p_vector)
{

}

map createMap(int index, int width, int height)
{
	vector<vector<int>> p_vector(height);
	vector<entity> p_tiles;
	SDL_Texture* rectTexture = window.loadTexture("res/image/rect.png");
	ifstream cin(("res/image/map/dragon_cave_" + to_string(index) + ".txt").c_str());

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++)
		{
			int index; cin >> index; 
			// cout << index << endl;
			p_vector[i].push_back(index);
			for (SDL_Rect &p_rect : tileHitBox[index])
				p_tiles.emplace_back(vector2f(j * 16 + p_rect.x, i * 16 + p_rect.y), rectTexture, p_rect);
		}
	}
	return map(p_vector, p_tiles);	
}

map dragon_cave_1()
{
	map p_map = createMap(1, 43, 40);
	
	p_map.portals.emplace_back(SDL_Rect{ 240, 480, 32, 4 }, 2, vector2f(283, 560));
	p_map.portals.emplace_back(SDL_Rect{ 96, 336, 32, 4  }, 2, vector2f(171, 368));
	p_map.portals.emplace_back(SDL_Rect{ 352, 508, 32, 4 }, 3, vector2f(459, 496));
	p_map.portals.emplace_back(SDL_Rect{ 384, 268, 32, 4 }, 3, vector2f(475, 256));
	p_map.portals.emplace_back(SDL_Rect{ 32, 220, 32, 4 }, 3, vector2f(171, 240));

	p_map.index = 1;
	return p_map;
}

map dragon_cave_2()
{
	map p_map = createMap(2, 38, 37);

	p_map.portals.emplace_back(SDL_Rect{ 272, 572, 32, 4 }, 1, vector2f(251, 495 ));
	p_map.portals.emplace_back(SDL_Rect{ 160, 380, 32, 4 }, 1, vector2f(107, 352));

	p_map.enemies.emplace_back(new kimonobird(vector2f(128, 480)));

	p_map.index = 2;
	return p_map;
}

map dragon_cave_3()
{
	map p_map = createMap(3, 51, 41);

	p_map.portals.emplace_back(SDL_Rect{ 448, 480, 32, 4 }, 1, vector2f(363, 496 ));
	p_map.portals.emplace_back(SDL_Rect{ 464, 240, 32, 4 }, 1, vector2f(395, 256 ));
	p_map.portals.emplace_back(SDL_Rect{ 160, 224, 32, 4 }, 1 , vector2f(43, 208 ));
	p_map.portals.emplace_back(SDL_Rect{ 432, 64 , 32, 4 }, 4 , vector2f(235, 176));
	p_map.portals.emplace_back(SDL_Rect{ 240, 556, 32, 4 }, 5 , vector2f(235, 48));

	p_map.index = 3;
	return p_map;
}

map dragon_cave_4()
{
	map p_map = createMap(4, 19, 19);

	p_map.portals.emplace_back(SDL_Rect{ 224, 188, 32, 4 }, 3, vector2f(443, 80));

	p_map.index = 4;
	return p_map;
}

map dragon_cave_5()
{
	map p_map = createMap(5, 18, 17);

	p_map.portals.emplace_back(SDL_Rect{224, 32, 32, 4}, 3, vector2f(251, 544));

	p_map.index = 5;
	return p_map;
}

int map::checkPortals(player &p, int &isFading, int &alpha, float currentTime)
{
	SDL_Rect position = p.getLegRect();
	for (portal p_portal : portals)
	{
		if (SDL_HasIntersection(&position, &p_portal.area))
		{
			isFading = 1; alpha = 0;
			p.setPos(p_portal.targetPosition);
			music.play("door", currentTime);
			return p_portal.targetMap;
		}
	}

	return index;
}