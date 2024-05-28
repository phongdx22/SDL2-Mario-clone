#pragma once
#ifndef _GAMESCREEN_H_
#define _GAMESCREEN_H_
#endif //_GAMESCREEN_H_
#include <SDL.h>
#include "Commons.h"
#include "TextRenderer.h"

class GameScreen
{
public:
	GameScreen(SDL_Renderer* renderer);
	~GameScreen();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);
	GAMESTATE GetGameState() { return m_current_game_state; }
	GAMESTATE GetNextGameState() { return m_next_game_state; }

protected:
	SDL_Renderer* m_renderer;
	GAMESTATE m_current_game_state;
	GAMESTATE m_next_game_state;

	void SetGameState(GAMESTATE gameState);
	void SetNextGameState(GAMESTATE gameState);

};

