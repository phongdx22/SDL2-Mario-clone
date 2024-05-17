#pragma once
#include "Character.h"
class CharacterMario : public Character
{
public:
	CharacterMario(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map);

	virtual void Update(float deltaTime, SDL_Event e);
};

