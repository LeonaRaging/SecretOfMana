#pragma once

#include "player.hpp"

using namespace std;

const int LEVEL_WIDTH = 1024;
const int LEVEL_HEIGHT = 896;
const int SCREEN_WIDTH = 256;
const int SCREEN_HEIGHT = 224;
const int TARGET_FPS = 100;
const int FRAME_DELAY = 1000 / TARGET_FPS;

bool isCollision(SDL_Rect a, vector<entity>& b);

void update(SDL_Rect &camera, player &p);
