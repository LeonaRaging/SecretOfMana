#pragma once
#include "math.hpp"

class audio
{
public:
	audio();
	void init();
	void play(string filename, float currentTime);
	Mix_Music* ingame;
	Mix_Music* titlescreen;
private:
	Mix_Chunk* current;
	unordered_map<string,float> lastUpdate;
};

extern audio music;