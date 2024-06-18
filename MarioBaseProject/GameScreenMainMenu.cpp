#include "GameScreenMainMenu.h"

GameScreenMainMenu::GameScreenMainMenu(SDL_Renderer* renderer) : GameScreen(renderer)
{
	m_level_map = nullptr;

	SetUpLevel();
}

GameScreenMainMenu::~GameScreenMainMenu()
{
	delete startText;
	startText = nullptr;

	delete quitText;
	quitText = nullptr;

	delete titleText;
	titleText = nullptr;

	delete my_characterMario;
	my_characterMario = nullptr;

	delete m_level_map;
	m_level_map = nullptr;
}

void GameScreenMainMenu::Render()
{
	startText->Render(m_renderer, "START", SCREEN_WIDTH / 2 - 30, SCREEN_HEIGHT / 4);
	quitText->Render(m_renderer, "QUIT", SCREEN_WIDTH / 2 - 30, SCREEN_HEIGHT / 4 + 50);
	titleText->Render(m_renderer, "MARIO GAME!", SCREEN_WIDTH / 4 - 50, SCREEN_HEIGHT / 4 - 70);

	my_characterMario->Render();
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
			my_characterMario->SetPosition(Vector2D(160, SCREEN_HEIGHT / 4 + 50));
			SetNextGameState(EXIT_STATE);
			break;
		case SDLK_UP:
			position1y = 160;
			my_characterMario->SetPosition(Vector2D(160, SCREEN_HEIGHT / 4));
			SetNextGameState(GAME_STATE_1);
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
	titleText = new TextRenderer(50);

	my_characterMario = new CharacterMario(m_renderer, "Images/Mario.png", Vector2D(160, position1y), m_level_map);

	SetGameState(INTRO_STATE);
	SetNextGameState(GAME_STATE_1);

	return true;
}
