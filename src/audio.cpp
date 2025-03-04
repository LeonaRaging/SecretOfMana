#include "audio.hpp"

audio music;

audio::audio()
{
}

void audio::init()
{
	bgm = Mix_LoadMUS("res/audio/Into_the_Thick_of_it.wav");
	Mix_PlayMusic(bgm, -1);
}

void audio::play(string filename, float currentTime)
{
	string filepath = "res/audio/" + filename + ".wav";
	current = Mix_LoadWAV(filepath.c_str());
	if (currentTime - lastUpdate[filepath.c_str()] > 250) {
		Mix_PlayChannel(-1, current, 0);
		lastUpdate[filepath.c_str()] = currentTime;
	}
}
