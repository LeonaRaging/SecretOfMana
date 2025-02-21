#include "map.hpp"

map::map(entity p_entity, vector<entity> p_tiles)
	: e(p_entity), tiles(p_tiles)
{

}

map dragon_cave_2(RenderWindow &window) 
{
	SDL_Texture* mapTexture = window.loadTexture("res/image/map.png");
	entity p_entity(vector2f(16, 16), mapTexture, 16, 16, 608, 592);

	vector<entity> p_tiles;
	SDL_Texture* rectTexture = window.loadTexture("res/image/rect.png");

	// boundary
	p_tiles.emplace_back(vector2f(280, 537), rectTexture, 0, 0, 7, 55);
	p_tiles.emplace_back(vector2f(240, 528), rectTexture, 0, 0, 40, 10);
	p_tiles.emplace_back(vector2f(232, 529), rectTexture, 0, 0, 8, 9);
	p_tiles.emplace_back(vector2f(224, 538), rectTexture, 0, 0, 8, 6);
	p_tiles.emplace_back(vector2f(160, 544), rectTexture, 0, 0, 64, 1);
	p_tiles.emplace_back(vector2f(152, 538), rectTexture, 0, 0, 8, 7);
	p_tiles.emplace_back(vector2f(144, 530), rectTexture, 0, 0, 8, 9);
	p_tiles.emplace_back(vector2f(96, 528), rectTexture, 0, 0, 48, 2);
	p_tiles.emplace_back(vector2f(88, 522), rectTexture, 0, 0, 8, 6);
	p_tiles.emplace_back(vector2f(80, 514), rectTexture, 0, 0, 8, 8);
	p_tiles.emplace_back(vector2f(72, 473), rectTexture, 0, 0, 8, 41);
	p_tiles.emplace_back(vector2f(64, 465), rectTexture, 0, 0, 8, 8);
	p_tiles.emplace_back(vector2f(56, 442), rectTexture, 0, 0, 8, 23);
	p_tiles.emplace_back(vector2f(48, 434), rectTexture, 0, 0, 8, 8);
	p_tiles.emplace_back(vector2f(47, 397), rectTexture, 0, 0, 1, 37);
	p_tiles.emplace_back(vector2f(47, 387), rectTexture, 0, 0, 9, 10);
	p_tiles.emplace_back(vector2f(56, 299), rectTexture, 0, 0, 8, 89);
	p_tiles.emplace_back(vector2f(48, 289), rectTexture, 0, 0, 8, 10);
	p_tiles.emplace_back(vector2f(47, 219), rectTexture, 0, 0, 1, 79);
	p_tiles.emplace_back(vector2f(47, 209), rectTexture, 0, 0, 9, 13);
	p_tiles.emplace_back(vector2f(56, 156), rectTexture, 0, 0, 8, 57);
	p_tiles.emplace_back(vector2f(56, 156), rectTexture, 0, 0, 8, 57);
	p_tiles.emplace_back(vector2f(64, 151), rectTexture, 0, 0, 7, 10);
	p_tiles.emplace_back(vector2f(71, 142), rectTexture, 0, 0, 9, 9);
	p_tiles.emplace_back(vector2f(80, 142), rectTexture, 0, 0, 49, 1);
	p_tiles.emplace_back(vector2f(129, 143), rectTexture, 0, 0, 7, 22);
	p_tiles.emplace_back(vector2f(136, 165), rectTexture, 0, 0, 9, 9);
	p_tiles.emplace_back(vector2f(144, 174), rectTexture, 0, 0, 9, 8);
	p_tiles.emplace_back(vector2f(152, 182), rectTexture, 0, 0, 23, 9);
	p_tiles.emplace_back(vector2f(175, 190), rectTexture, 0, 0, 7, 8);
	p_tiles.emplace_back(vector2f(182, 198), rectTexture, 0, 0, 50, 8);
	p_tiles.emplace_back(vector2f(232, 140), rectTexture, 0, 0, 9, 58);
	p_tiles.emplace_back(vector2f(241, 131), rectTexture, 0, 0, 39, 10);
	p_tiles.emplace_back(vector2f(280, 123), rectTexture, 0, 0, 9, 8);
	p_tiles.emplace_back(vector2f(289, 124), rectTexture, 0, 0, 17, 1);
	p_tiles.emplace_back(vector2f(305, 124), rectTexture, 0, 0, 7, 25);
	p_tiles.emplace_back(vector2f(312, 149), rectTexture, 0, 0, 8, 10);
	p_tiles.emplace_back(vector2f(320, 158), rectTexture, 0, 0, 83, 2);
	p_tiles.emplace_back(vector2f(403, 147), rectTexture, 0, 0, 7, 10);
	p_tiles.emplace_back(vector2f(410, 147), rectTexture, 0, 0, 16, 1);
	p_tiles.emplace_back(vector2f(425, 126), rectTexture, 0, 0, 56, 32);
	p_tiles.emplace_back(vector2f(417, 115), rectTexture, 0, 0, 9, 10);
	p_tiles.emplace_back(vector2f(416, 92), rectTexture, 0, 0, 1, 24);
	p_tiles.emplace_back(vector2f(417, 82), rectTexture, 0, 0, 11, 10);
	p_tiles.emplace_back(vector2f(428, 68), rectTexture, 0, 0, 11, 14);
	p_tiles.emplace_back(vector2f(439, 60), rectTexture, 0, 0, 11, 12);
	p_tiles.emplace_back(vector2f(450, 61), rectTexture, 0, 0, 92, 1);
	p_tiles.emplace_back(vector2f(542, 61), rectTexture, 0, 0, 10, 10);
	p_tiles.emplace_back(vector2f(542, 61), rectTexture, 0, 0, 10, 10);
	p_tiles.emplace_back(vector2f(552, 71), rectTexture, 0, 0, 52, 9);
	p_tiles.emplace_back(vector2f(577, 79), rectTexture, 0, 0, 8, 8);
	p_tiles.emplace_back(vector2f(577, 79), rectTexture, 0, 0, 8, 8);
	p_tiles.emplace_back(vector2f(585, 87), rectTexture, 0, 0, 1, 19);
	p_tiles.emplace_back(vector2f(576, 105), rectTexture, 0, 0, 8, 41);
	p_tiles.emplace_back(vector2f(568, 145), rectTexture, 0, 0, 8, 8);
	p_tiles.emplace_back(vector2f(560, 153), rectTexture, 0, 0, 8, 58);
	p_tiles.emplace_back(vector2f(567, 211), rectTexture, 0, 0, 41, 12);
	p_tiles.emplace_back(vector2f(608, 223), rectTexture, 0, 0, 1, 51);
	p_tiles.emplace_back(vector2f(600, 273), rectTexture, 0, 0, 8, 10);
	p_tiles.emplace_back(vector2f(592, 282), rectTexture, 0, 0, 8, 6);
	p_tiles.emplace_back(vector2f(568, 288), rectTexture, 0, 0, 24, 9);
	p_tiles.emplace_back(vector2f(560, 297), rectTexture, 0, 0, 9, 23);
	p_tiles.emplace_back(vector2f(536, 320), rectTexture, 0, 0, 24, 10);
	p_tiles.emplace_back(vector2f(528, 329), rectTexture, 0, 0, 8, 25);
	p_tiles.emplace_back(vector2f(521, 354), rectTexture, 0, 0, 7, 7);
	p_tiles.emplace_back(vector2f(512, 361), rectTexture, 0, 0, 9, 23);
	p_tiles.emplace_back(vector2f(345, 384), rectTexture, 0, 0, 167, 10);
	p_tiles.emplace_back(vector2f(336, 395), rectTexture, 0, 0, 9, 134);
	p_tiles.emplace_back(vector2f(328, 529), rectTexture, 0, 0, 8, 8);
	p_tiles.emplace_back(vector2f(320, 537), rectTexture, 0, 0, 8, 56);

	// inside
	p_tiles.emplace_back(vector2f(320, 416), rectTexture, 0, 0, 16, 31);
	p_tiles.emplace_back(vector2f(311, 377), rectTexture, 0, 0, 9, 108);
	p_tiles.emplace_back(vector2f(297, 368), rectTexture, 0, 0, 15, 127);
	p_tiles.emplace_back(vector2f(288, 368), rectTexture, 0, 0, 9, 118);
	p_tiles.emplace_back(vector2f(281, 369), rectTexture, 0, 0, 8, 94);
	p_tiles.emplace_back(vector2f(272, 376), rectTexture, 0, 0, 10, 79);
	p_tiles.emplace_back(vector2f(255, 400), rectTexture, 0, 0, 17, 47);
	p_tiles.emplace_back(vector2f(242, 346), rectTexture, 0, 0, 13, 115);
	p_tiles.emplace_back(vector2f(230, 460), rectTexture, 0, 0, 12, 30);
	p_tiles.emplace_back(vector2f(152, 483), rectTexture, 0, 0, 78, 11);
	p_tiles.emplace_back(vector2f(218, 336), rectTexture, 0, 0, 32, 10);
	p_tiles.emplace_back(vector2f(208, 345), rectTexture, 0, 0, 9, 55);
	p_tiles.emplace_back(vector2f(143, 474), rectTexture, 0, 0, 9, 10);
	p_tiles.emplace_back(vector2f(127, 428), rectTexture, 0, 0, 16, 46);
	p_tiles.emplace_back(vector2f(118, 420), rectTexture, 0, 0, 10, 8);
	p_tiles.emplace_back(vector2f(112, 364), rectTexture, 0, 0, 6, 56);
	p_tiles.emplace_back(vector2f(104, 356), rectTexture, 0, 0, 8, 8);
	p_tiles.emplace_back(vector2f(96, 265), rectTexture, 0, 0, 8, 91);
	p_tiles.emplace_back(vector2f(104, 257), rectTexture, 0, 0, 8, 8);
	p_tiles.emplace_back(vector2f(112, 234), rectTexture, 0, 0, 8, 23);
	p_tiles.emplace_back(vector2f(120, 226), rectTexture, 0, 0, 32, 9);
	p_tiles.emplace_back(vector2f(152, 235), rectTexture, 0, 0, 17, 13);
	p_tiles.emplace_back(vector2f(169, 247), rectTexture, 0, 0, 75, 7);
	p_tiles.emplace_back(vector2f(244, 237), rectTexture, 0, 0, 11, 10);
	p_tiles.emplace_back(vector2f(254, 228), rectTexture, 0, 0, 11, 9);
	p_tiles.emplace_back(vector2f(264, 205), rectTexture, 0, 0, 8, 23);
	p_tiles.emplace_back(vector2f(271, 197), rectTexture, 0, 0, 10, 9);
	p_tiles.emplace_back(vector2f(281, 188), rectTexture, 0, 0, 9, 9);
	p_tiles.emplace_back(vector2f(290, 178), rectTexture, 0, 0, 8, 10);
	p_tiles.emplace_back(vector2f(297, 171), rectTexture, 0, 0, 72, 7);
	p_tiles.emplace_back(vector2f(369, 176), rectTexture, 0, 0, 11, 7);
	p_tiles.emplace_back(vector2f(380, 183), rectTexture, 0, 0, 57, 1);
	p_tiles.emplace_back(vector2f(437, 172), rectTexture, 0, 0, 18, 11);
	p_tiles.emplace_back(vector2f(455, 182), rectTexture, 0, 0, 9, 5);
	p_tiles.emplace_back(vector2f(464, 187), rectTexture, 0, 0, 9, 25);
	p_tiles.emplace_back(vector2f(473, 212), rectTexture, 0, 0, 14, 12);
	p_tiles.emplace_back(vector2f(512, 121), rectTexture, 0, 0, 19, 37);
	p_tiles.emplace_back(vector2f(530, 127), rectTexture, 0, 0, 13, 11);
	p_tiles.emplace_back(vector2f(543, 137), rectTexture, 0, 0, 7, 8);
	p_tiles.emplace_back(vector2f(550, 145), rectTexture, 0, 0, 1, 175);
	p_tiles.emplace_back(vector2f(528, 158), rectTexture, 0, 0, 9, 8);
	p_tiles.emplace_back(vector2f(537, 166), rectTexture, 0, 0, 13, 8);
	p_tiles.emplace_back(vector2f(448, 223), rectTexture, 0, 0, 15, 11);
	p_tiles.emplace_back(vector2f(463, 223), rectTexture, 0, 0, 24, 1);
	p_tiles.emplace_back(vector2f(487, 224), rectTexture, 0, 0, 29, 8);
	p_tiles.emplace_back(vector2f(516, 226), rectTexture, 0, 0, 9, 8);
	p_tiles.emplace_back(vector2f(525, 234), rectTexture, 0, 0, 3, 75);
	p_tiles.emplace_back(vector2f(518, 308), rectTexture, 0, 0, 7, 3);
	p_tiles.emplace_back(vector2f(512, 311), rectTexture, 0, 0, 6, 8);
	p_tiles.emplace_back(vector2f(504, 319), rectTexture, 0, 0, 8, 8);
	p_tiles.emplace_back(vector2f(481, 327), rectTexture, 0, 0, 23, 8);
	p_tiles.emplace_back(vector2f(474, 334), rectTexture, 0, 0, 7, 7);
	p_tiles.emplace_back(vector2f(464, 341), rectTexture, 0, 0, 10, 8);
	p_tiles.emplace_back(vector2f(417, 349), rectTexture, 0, 0, 47, 15);
	p_tiles.emplace_back(vector2f(399, 349), rectTexture, 0, 0, 19, 1);
	p_tiles.emplace_back(vector2f(399, 317), rectTexture, 0, 0, 1, 33);
	p_tiles.emplace_back(vector2f(367, 317), rectTexture, 0, 0, 1, 34);
	p_tiles.emplace_back(vector2f(349, 350), rectTexture, 0, 0, 19, 2);
	p_tiles.emplace_back(vector2f(343, 342), rectTexture, 0, 0, 7, 8);
	p_tiles.emplace_back(vector2f(336, 320), rectTexture, 0, 0, 7, 22);
	p_tiles.emplace_back(vector2f(447, 233), rectTexture, 0, 0, 2, 24);
	p_tiles.emplace_back(vector2f(439, 257), rectTexture, 0, 0, 9, 8);
	p_tiles.emplace_back(vector2f(433, 265), rectTexture, 0, 0, 6, 6);
	p_tiles.emplace_back(vector2f(352, 271), rectTexture, 0, 0, 81, 1);
	p_tiles.emplace_back(vector2f(343, 271), rectTexture, 0, 0, 9, 9);
	p_tiles.emplace_back(vector2f(336, 280), rectTexture, 0, 0, 8, 6);
	p_tiles.emplace_back(vector2f(335, 286), rectTexture, 0, 0, 1, 34);
	p_tiles.emplace_back(vector2f(272, 319), rectTexture, 0, 0, 64, 1);
	p_tiles.emplace_back(vector2f(264, 313), rectTexture, 0, 0, 9, 6);
	p_tiles.emplace_back(vector2f(256, 304), rectTexture, 0, 0, 8, 9);
	p_tiles.emplace_back(vector2f(185, 304), rectTexture, 0, 0, 72, 1);
	p_tiles.emplace_back(vector2f(176, 304), rectTexture, 0, 0, 9, 15);
	p_tiles.emplace_back(vector2f(175, 318), rectTexture, 0, 0, 1, 82);
	p_tiles.emplace_back(vector2f(397, 317), rectTexture, 0, 0, 73, 1);
	p_tiles.emplace_back(vector2f(471, 297), rectTexture, 0, 0, 33, 21);
	p_tiles.emplace_back(vector2f(504, 285), rectTexture, 0, 0, 12, 12);
	p_tiles.emplace_back(vector2f(516, 277), rectTexture, 0, 0, 10, 8);

	return map(p_entity, p_tiles);
}