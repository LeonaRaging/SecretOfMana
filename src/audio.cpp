#include "audio.hpp"

audio music;

audio::audio()
{
}

void audio::init()
{
	ingame = Mix_LoadMUS("res/audio/Into_the_Thick_of_it.wav");
	titlescreen = Mix_LoadMUS("res/audio/Fear_of_the_Heavens.wav");
	bosstheme = Mix_LoadMUS("res/audio/Danger.wav");
	Mix_PlayMusic(titlescreen, -1);
}

void audio::play(string filename)
{
	
	string filepath = "res/audio/" + filename + ".wav";
	current = Mix_LoadWAV(filepath.c_str());
	if (channel.find(filepath) == channel.end())
		channel[filepath] = channel[""]++;
	if (!Mix_Playing(channel[filepath]))
		Mix_PlayChannel(channel[filepath], current, 0);
}
