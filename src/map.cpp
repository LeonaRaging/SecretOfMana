#include "map.hpp"

SDL_Texture* tilesTexture = nullptr;
vector<SDL_Rect> mapTiles;
vector<SDL_Rect> tileHitBox[200];

void init(RenderWindow &window)
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
	tileHitBox[40].emplace_back(SDL_Rect{ 0, 0, 1, 16 });
	tileHitBox[41].emplace_back(SDL_Rect{ 0, 0, 16, 16 });
	tileHitBox[42].emplace_back(SDL_Rect{ 15, 0, 1 , 16 });
	tileHitBox[52].emplace_back(SDL_Rect{ 0, 0, 8, 8});
	tileHitBox[52].emplace_back(SDL_Rect{ 8, 8, 8, 8});
	tileHitBox[56].emplace_back(SDL_Rect{ 0, 0, 8, 8});
	tileHitBox[56].emplace_back(SDL_Rect{ 8, 8, 8, 8});
	tileHitBox[57].emplace_back(SDL_Rect{ 0, 8, 16, 8});
	tileHitBox[58].emplace_back(SDL_Rect{ 8, 0, 8, 8});
	tileHitBox[58].emplace_back(SDL_Rect{ 8, 0, 8, 8});
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

map createMap(RenderWindow &window, int index, int width, int height)
{
	vector<vector<int>> p_vector(height);
	vector<entity> p_tiles;
	SDL_Texture* rectTexture = window.loadTexture("res/image/rect.png");
	ifstream cin(("res/image/map/dragon_cave_" + to_string(index) + ".txt").c_str());

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++)
		{
			int index; cin >> index; 
			cout << index << endl;
			p_vector[i].push_back(index);
			for (SDL_Rect &p_rect : tileHitBox[index])
				p_tiles.emplace_back(vector2f(j * 16 + p_rect.x, i * 16 + p_rect.y), rectTexture, p_rect);
		}
	}
	return map(p_vector, p_tiles);	
}