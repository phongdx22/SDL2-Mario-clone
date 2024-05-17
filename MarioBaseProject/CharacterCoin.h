#pragma once
#include "Character.h"
class CharacterCoin : public Character
{
public:
	CharacterCoin(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map);
	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;

private:
	float m_single_sprite_w;
	float m_single_sprite_h;
	float m_frame_delay;
	int m_current_frame;
};

