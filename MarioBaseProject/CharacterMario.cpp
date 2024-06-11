#include "CharacterMario.h"

CharacterMario::CharacterMario(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map) 
	: Character(renderer, imagePath, start_position, map)
{
}

void CharacterMario::Update(float deltaTime, SDL_Event e)
{
	switch (e.type)
	{
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT:
			m_moving_left = true;
			break;
		case SDLK_RIGHT:
			m_moving_right = true;
			break;
		case SDLK_UP:
			if (m_can_jump)
			{
				Jump();
			}
			break;
		}
	break;

	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT:
			m_moving_left = false;
			break;
		case SDLK_RIGHT:
			m_moving_right = false;
			break;
		}
	break;
	}

	if (m_moving_left)
	{
		MoveLeft(deltaTime, MOVESPEED);
	}
	else if (m_moving_right)
	{
		MoveRight(deltaTime, MOVESPEED);
	}

	Character::Update(deltaTime, e);
}
