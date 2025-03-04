#pragma once
#include "math.hpp"

class audio
{
public:
	audio();
	void init();
	void play(string filename, float currentTime);
private:
	Mix_Music* bgm;
	Mix_Chunk* current;
	unordered_map<string,float> lastUpdate;
};

extern audio music;