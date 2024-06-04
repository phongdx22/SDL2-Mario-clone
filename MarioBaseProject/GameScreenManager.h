#pragma once
#ifndef _GAMESCREENMANAGER_H_
#define _GAMESCREENMANAGER_H_
#include <SDL.h>
#include "Commons.h"

class GameScreen;

class GameScreenManager
{
public:
	GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen);
	~GameScreenManager();

	void Render();
	void Update(float deltaTime, SDL_Event e);

	void ChangeScreen(SCREENS new_screen);

	GAMESTATE GetCurrentGameState();
	GAMESTATE GetNextGameState();

private:
	SDL_Renderer* m_renderer;
	GameScreen* m_current_screen;
};

#endif // _GAMESCREENMANAGER_H_

