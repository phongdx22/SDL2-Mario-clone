#include "GameScreen.h"
#include <iostream>
using namespace std;

GameScreen::GameScreen(SDL_Renderer* renderer)
{
	m_renderer = renderer;
}

GameScreen::~GameScreen()
{
	m_renderer = nullptr;
}

void GameScreen::Render() {}

void GameScreen::Update(float deltaTime, SDL_Event e) {}

void GameScreen::SetGameState(GAMESTATE gameState)
{
	m_current_game_state = gameState;
}

void GameScreen::SetNextGameState(GAMESTATE gameState)
{
	m_next_game_state = gameState;
}
