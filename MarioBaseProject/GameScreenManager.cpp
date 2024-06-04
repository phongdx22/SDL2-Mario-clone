#include "GameScreen.h"
#include "GameScreenLevel1.h"
#include "GameScreenMainMenu.h"
#include "GameScreenManager.h"

GameScreenManager::GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen)
{
	m_renderer = renderer;
	m_current_screen = nullptr;
	ChangeScreen(startScreen);
}

GameScreenManager::~GameScreenManager()
{
	m_renderer = nullptr;
	delete m_current_screen;
	m_current_screen = nullptr;
}

void GameScreenManager::Render()
{
	m_current_screen->Render();
}

void GameScreenManager::Update(float deltaTime, SDL_Event e)
{
	m_current_screen->Update(deltaTime, e);
}

void GameScreenManager::ChangeScreen(SCREENS new_screen)
{
	//clear up the old screen
	if (m_current_screen != nullptr)
	{
		delete m_current_screen;
	}

	GameScreenMainMenu* tempScreenIntro;
	GameScreenLevel1* tempScreenLevel1;

	switch (new_screen)
	{
	case SCREEN_LEVEL1:
		tempScreenLevel1 = new GameScreenLevel1(m_renderer);
		m_current_screen = (GameScreen*)tempScreenLevel1;
		tempScreenLevel1 = nullptr;
		break;
	case SCREEN_INTRO:
		tempScreenIntro = new GameScreenMainMenu(m_renderer);
		m_current_screen = (GameScreen*)tempScreenIntro;
		tempScreenIntro = nullptr;
		break;
	default:
		;
	}
}

GAMESTATE GameScreenManager::GetCurrentGameState()
{
	return m_current_screen->GetGameState();
}

GAMESTATE GameScreenManager::GetNextGameState()
{
	return m_current_screen->GetNextGameState();
}



