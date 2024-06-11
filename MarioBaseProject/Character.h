#pragma once
#include <SDL.h>
#include <iostream>
#include "Commons.h"
#include "constants.h"
#include <string>
#include "Texture2D.h"
#include "LevelMap.h"
using namespace std;

class Character
{
public:
	Character(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map);
	~Character();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);
	void SetPosition(Vector2D new_position);
	Vector2D GetPosition();
	float GetCollisionRadius();
	Rect2D GetCollisionBox()
	{
		return Rect2D(m_position.x, m_position.y, m_texture->GetWidth(), m_texture->GetHeight());
	}
	bool IsJumping() { return m_jumping; }
	void CancelJump() { m_jumping = false; }
	void SetAlive(bool isAlive) { m_alive = isAlive; }
	bool GetAlive() { return m_alive; }
	void SetMovingLeft();
	void SetMovingRight();

protected:
	SDL_Renderer* m_renderer;
	Vector2D m_position;
	Texture2D* m_texture;
	FACING m_facing_direction;
	bool m_moving_left;
	bool m_moving_right;
	bool m_jumping;
	bool m_can_jump;
	bool m_alive;
	float m_jump_force;
	float m_collision_radius;

	virtual void MoveLeft(float deltaTime, float characterSpeed);
	virtual void MoveRight(float deltaTime, float characterSpeed);
	virtual void AddGravity(float deltaTime);
	virtual void Jump();

private:
	LevelMap* m_current_level_map;
};

