#include "GameScreenMainMenu.h"

GameScreenMainMenu::GameScreenMainMenu(SDL_Renderer* renderer) : GameScreen(renderer)
{
	SetUpLevel();
}

void GameScreenMainMenu::Render()
{
	startText->Render(m_renderer, "START", SCREEN_WIDTH / 2 - 30, position1y);
	quitText->Render(m_renderer, "QUIT", SCREEN_WIDTH / 2 - 30, position2y);
}

void GameScreenMainMenu::Update(float deltaTime, SDL_Event e)
{
	switch (e.type)
	{
	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case SDLK_DOWN:
			position1y = position2y;
			SetNextGameState(EXIT_STATE);
			break;
		case SDLK_UP:
			position1y = 200;
			SetNextGameState(GAME_STATE);
			break;
		}
	}
}

bool GameScreenMainMenu::SetUpLevel()
{
	position1y = SCREEN_HEIGHT / 4;
	position2y = SCREEN_HEIGHT / 4 + 50;

	startText = new TextRenderer(50);
	quitText = new TextRenderer(50);

	SetGameState(INTRO_STATE);
	SetNextGameState(GAME_STATE);

	return true;
}
