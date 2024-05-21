#pragma once
#include <SDL_mixer.h>
#include <string>

class SoundEffect
{
public:
	void Play();
	void Load(std::string path);
};

