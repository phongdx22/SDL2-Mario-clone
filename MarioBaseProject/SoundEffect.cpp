#include "SoundEffect.h"
#include <iostream>
using namespace std;

void SoundEffect::Play()
{
	Mix_PlayMusic(m_music, -1);
}

void SoundEffect::Load(std::string path)
{
	m_music = Mix_LoadMUS(path.c_str());
	if (m_music == nullptr)
	{
		cout << "Failed to load music. Error: " << Mix_GetError() << endl;
	}
}
