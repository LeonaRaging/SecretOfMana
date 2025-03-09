#pragma once
#include "utils.hpp"

class audio
{
public:
	audio();
	void init();
	void play(string filename);
	Mix_Music* ingame;
	Mix_Music* titlescreen;
	Mix_Music* bosstheme;
private:
	Mix_Chunk* current;
	unordered_map<string,int> channel;
};

extern audio music;