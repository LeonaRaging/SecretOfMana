#pragma once

#include "entity.hpp"

using namespace std;

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const int TARGET_FPS = 100;
const int FRAME_DELAY = 1000 / TARGET_FPS;

bool isCollision(SDL_Rect a, vector<entity>& b);
