#pragma once
#include "Character.h"
class CharacterKoopa : public Character
{
public:
	CharacterKoopa(SDL_Renderer* renderer, string imagePath, LevelMap* map, Vector2D start_position, FACING start_facing,
		float movement_speed);
	void TakeDamage();
	void Jump();
	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;
	bool GetInjured() { return m_injured; }
	void SetMovementSpeed(float speed);

private:
	float m_single_sprite_w;
	float m_single_sprite_h;
	bool m_injured;
	float m_injured_time;
	float m_movement_speed;

	void FlipRightwayUp();
};

