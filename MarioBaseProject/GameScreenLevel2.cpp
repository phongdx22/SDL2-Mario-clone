#include "GameScreenLevel2.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Texture2D.h"
#include "PowBlock.h"

using namespace std;

GameScreenLevel2::GameScreenLevel2(SDL_Renderer* renderer) : GameScreen(renderer)
{
	m_level_map = nullptr;

	SetUpLevel();
}

GameScreenLevel2::~GameScreenLevel2()
{
	delete m_background_texture;
	m_background_texture = nullptr;

	delete my_characterMario;
	my_characterMario = nullptr;

	delete my_characterLuigi;
	my_characterLuigi = nullptr;

	delete m_pow_block;
	m_pow_block = nullptr;
}

void GameScreenLevel2::Render()
{
	//draw the background
	m_background_texture->Render(Vector2D(0, m_background_yPos), SDL_FLIP_NONE);

	my_characterMario->Render();
	my_characterLuigi->Render();
	m_pow_block->Render();

	for (int i = 0; i < m_coins.size(); i++)
	{
		m_coins[i]->Render();
	}

	DrawBoard();
}

void GameScreenLevel2::Update(float deltaTime, SDL_Event e)
{
	//do the screenshake if required
	if (m_screenshake)
	{
		m_shake_time -= deltaTime;
		m_wobble++;
		m_background_yPos = sin(m_wobble);
		m_background_yPos *= 3.0f;

		//end shake after duration
		{
			if (m_shake_time <= 0.0f)
			{
				m_shake_time = false;
				m_background_yPos = 0.0f;
			}
		}
	}

	//update character
	my_characterMario->Update(deltaTime, e);
	my_characterLuigi->Update(deltaTime, e);
	UpdatePOWBlock();
	UpdateCoins(deltaTime, e);
}

void GameScreenLevel2::UpdatePOWBlock()
{
	if (Collisions::Instance()->Box(my_characterMario->GetCollisionBox(), m_pow_block->GetCollisionBox()))
	{
		if (m_pow_block->IsAvailable())
		{
			//collided while jumping
			if (my_characterMario->IsJumping())
			{
				DoScreenShake();
				m_pow_block->TakeHit();
				my_characterMario->CancelJump();
			}
		}
	}
}

bool GameScreenLevel2::SetUpLevel()
{
	srand(time(0));
	//load texture
	m_background_texture = new Texture2D(m_renderer);
	if (!m_background_texture->LoadFromFile("Images/BackgroundMB 2.png"))
	{
		cout << "Failed to load background texture!" << endl;
		return false;
	}

	SetLevelMap();

	//set up player character
	my_characterMario = new CharacterMario(m_renderer, "Images/Mario.png", Vector2D(64, 330), m_level_map);
	my_characterLuigi = new CharacterLuigi(m_renderer, "Images/Luigi.png", Vector2D(264, 330), m_level_map);
	m_pow_block = new PowBlock(m_renderer, m_level_map);

	CreateCoin(Vector2D(50, 32), 0);
	CreateCoin(Vector2D(240, 32), 1);
	CreateCoin(Vector2D(430, 32), 2);
	CreateCoin(Vector2D(30, 150), 3);
	CreateCoin(Vector2D(240, 120), 4);
	CreateCoin(Vector2D(450, 150), 5);
	CreateCoin(Vector2D(30, 250), 6);
	CreateCoin(Vector2D(240, 200), 7);
	CreateCoin(Vector2D(450, 250), 8);

	m_screenshake = false;
	m_background_yPos = 0.0f;
	m_coinTimer = 7.0f;
	m_score = 0;

	SetGameState(GAME_STATE_2);
	SetNextGameState(EXIT_STATE);

	return true;
}

void GameScreenLevel2::SetLevelMap()
{
	int map[MAP_HEIGHT][MAP_WIDTH] = { {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
									   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
									   {1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1},
									   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
									   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
									   {0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0},
									   {1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
									   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
									   {0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0},
									   {1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1},
									   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
									   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
									   {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1} };

	if (m_level_map != nullptr)
	{
		delete m_level_map;
	}

	m_level_map = new LevelMap(map);
}

void GameScreenLevel2::DoScreenShake()
{
	m_screenshake = true;
	m_shake_time = SHAKE_DURATION;
	m_wobble = 0.0f;
}

void GameScreenLevel2::UpdateCoins(float deltaTime, SDL_Event e)
{
	if (!m_coins.empty())
	{
		int coinIndexToDelete = -1;
		for (unsigned int i = 0; i < m_coins.size(); i++)
		{
			m_coins[i]->Update(deltaTime, e);

			if (Collisions::Instance()->Circle(m_coins[i], my_characterMario) ||
				Collisions::Instance()->Circle(m_coins[i], my_characterLuigi))
			{
				m_coins[i]->SetAlive(false);
				AddScore(20);
			}

			if (!m_coins[i]->GetAlive())
			{
				coinIndexToDelete = i;
			}
		}

		if (coinIndexToDelete != -1)
		{
			m_coins.erase(m_coins.begin() + coinIndexToDelete);
		}
	}
}

void GameScreenLevel2::CreateCoin(Vector2D position, int boardpos)
{
	m_coins.push_back(new CharacterCoin(m_renderer, "Images/Coin.png", position, m_level_map, boardpos));
}

void GameScreenLevel2::DrawBoard()
{
	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
	for (int i = 1; i < BOARD_SIZE; ++i)
	{
		SDL_RenderDrawLine(m_renderer, 200, i * CELL_SIZE, 300, i * CELL_SIZE);
	}

	for (int i = 1; i < BOARD_SIZE; ++i)
	{
		SDL_RenderDrawLine(m_renderer, i * CELL_SIZE + 175, 30, i * CELL_SIZE + 175, 130);
	}

	SDL_RenderPresent(m_renderer);
}

void GameScreenLevel2::DrawXAndO(Player board[BOARD_SIZE][BOARD_SIZE])
{
	for (int row = 0; row < BOARD_SIZE; ++row)
	{
		for (int col = 0; col < BOARD_SIZE; ++col)
		{
			if (board[row][col] == Player::PLAYER_1)
			{
				// Draw X
				SDL_RenderDrawLine(m_renderer, col * CELL_SIZE, row * CELL_SIZE, (col + 1) * CELL_SIZE, (row + 1) * CELL_SIZE);
				SDL_RenderDrawLine(m_renderer, col * CELL_SIZE, (row + 1) * CELL_SIZE, (col + 1) * CELL_SIZE, row * CELL_SIZE);
			}
			else if (board[row][col] == Player::PLAYER_2)
			{
				// Draw O
				int centerX = col * CELL_SIZE + CELL_SIZE / 2;
				int centerY = row * CELL_SIZE + CELL_SIZE / 2;
				int radius = CELL_SIZE / 2 - 10;
				const int num_segments = 30;
				for (int i = 0; i < num_segments; i++)
				{
					float angle = 2 * M_PI * i / num_segments;
					int x = centerX + radius * cos(angle);
					int y = centerY + radius * sin(angle);
					SDL_RenderDrawPoint(m_renderer, x, y);
				}
			}
		}
	}
}

bool GameScreenLevel2::CheckWin(Player player)
{
	//Check rows
	for (int i = 0; i < BOARD_SIZE; ++i) {
		if (board[i][0] == player && board[i][1] == player && board[i][2] == player)
			return true;
	}

	// Check columns
	for (int i = 0; i < BOARD_SIZE; ++i) {
		if (board[0][i] == player && board[1][i] == player && board[2][i] == player)
			return true;
	}

	// Check diagonals
	if (board[0][0] == player && board[1][1] == player && board[2][2] == player)
		return true;
	if (board[0][2] == player && board[1][1] == player && board[2][0] == player)
		return true;

	return false;
}



