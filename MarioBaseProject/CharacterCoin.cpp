#include "CharacterCoin.h"

CharacterCoin::CharacterCoin(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map) : Character(renderer, imagePath, start_position, map)
{
	m_position = start_position;
	m_single_sprite_w = m_texture->GetWidth() / 3;
	m_single_sprite_h = m_texture->GetHeight();
}

void CharacterCoin::Render()
{
	SDL_Rect portion_of_sprite = { m_single_sprite_w * m_current_frame,0,m_single_sprite_w,m_single_sprite_h };

	SDL_Rect desRect = { (int)(m_position.x),(int)(m_position.y),m_single_sprite_w,m_single_sprite_h };

	m_texture->Render(portion_of_sprite, desRect, SDL_FLIP_NONE);
}

void CharacterCoin::Update(float deltaTime, SDL_Event e)
{
	m_frame_delay = -deltaTime;
	if (m_frame_delay <= 0.0f)
	{
		m_frame_delay = ANIMATION_DELAY;
		m_current_frame++;
		if (m_current_frame > 2)
		{
			m_current_frame = 0;
		}
	}
}
