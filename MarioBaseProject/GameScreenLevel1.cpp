#include "GameScreenLevel1.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Texture2D.h"
#include "PowBlock.h"

using namespace std;

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer)
{
	m_level_map = nullptr;

	SetUpLevel();
}

GameScreenLevel1::~GameScreenLevel1()
{
	delete m_background_texture;
	m_background_texture = nullptr;

	delete my_characterMario;
	my_characterMario = nullptr;

	delete my_characterLuigi;
	my_characterLuigi = nullptr;

	delete m_pow_block;
	m_pow_block = nullptr;

	for (int i = 0; i < m_enemies.size(); i++)
	{
		delete m_enemies[i];
	}
	m_enemies.clear();
}

void GameScreenLevel1::Render()
{
	//draw the background
	m_background_texture->Render(Vector2D(0, m_background_yPos), SDL_FLIP_NONE);

	for (int i = 0; i < m_enemies.size(); i++)
	{
		m_enemies[i]->Render();
	}

	my_characterMario->Render();
	my_characterLuigi->Render();
	m_pow_block->Render();

	for (int i = 0; i < m_coins.size(); i++)
	{
		m_coins[i]->Render();
	}

	scoreText->Render(m_renderer, m_score, SCREEN_WIDTH / 2 - 30, SCREEN_HEIGHT / 4 - 50);
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
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
	UpdateEnemies(deltaTime, e);
	UpdatePOWBlock();
	UpdateCoins(deltaTime, e);

	m_koopaTimer -= deltaTime;
	if (m_koopaTimer <= 0.0f)
	{
		CreateKoopa(Vector2D(150, 32), FACING_RIGHT, KOOPA_SPEED);
		m_koopaTimer = 5.0f;
	}

	m_coinTimer -= deltaTime;
	if (m_coinTimer <= 0.0f)
	{
		double randomNumber = (double)rand() / ((double)RAND_MAX + 1);
		CreateCoin(Vector2D(SCREEN_WIDTH * randomNumber, 32));
		m_coinTimer = 7.0f;
	}
}

void GameScreenLevel1::UpdatePOWBlock()
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

bool GameScreenLevel1::SetUpLevel()
{
	srand(time(0));
	//load texture
	m_background_texture = new Texture2D(m_renderer);
	if (!m_background_texture->LoadFromFile("Images/BackgroundMB.png"))
	{
		cout << "Failed to load background texture!" << endl;
		return false;
	}

	SetLevelMap();

	//set up player character
	my_characterMario = new CharacterMario(m_renderer, "Images/Mario.png", Vector2D(64, 330), m_level_map);
	my_characterLuigi = new CharacterLuigi(m_renderer, "Images/Luigi.png", Vector2D(264, 330), m_level_map);
	m_pow_block = new PowBlock(m_renderer, m_level_map);

	CreateKoopa(Vector2D(150, 32), FACING_RIGHT, KOOPA_SPEED);
	CreateKoopa(Vector2D(325, 32), FACING_LEFT, KOOPA_SPEED);

	CreateCoin(Vector2D(180, 32));

	m_screenshake = false;
	m_background_yPos = 0.0f;
	m_koopaTimer = 5.0f;
	m_coinTimer = 7.0f;
	scoreText = new TextRenderer(40);
	m_score = 0;

	SetGameState(GAME_STATE);
	SetNextGameState(EXIT_STATE);

	return true;
}

void GameScreenLevel1::SetLevelMap()
{
	int map[MAP_HEIGHT][MAP_WIDTH] = { {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
									   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
									   {1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1},
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

void GameScreenLevel1::DoScreenShake()
{
	m_screenshake = true;
	m_shake_time = SHAKE_DURATION;
	m_wobble = 0.0f;

	for (unsigned int i = 0; i < m_enemies.size(); i++)
	{
		m_enemies[i]->TakeDamage();
	}
}

void GameScreenLevel1::UpdateEnemies(float deltaTime, SDL_Event e)
{
	if (!m_enemies.empty())
	{
		int enemyIndexToDelete = -1;
		for (unsigned int i = 0; i < m_enemies.size(); i++)
		{
			if (m_enemies[i]->GetPosition().y > 300.0f)
			{
				if (m_enemies[i]->GetPosition().x < (float)(-m_enemies[i]->GetCollisionBox().width * 0.5f))
				{
					m_enemies[i]->SetMovingRight();
				}
				else if (m_enemies[i]->GetPosition().x > SCREEN_WIDTH - (float)(m_enemies[i]->GetCollisionBox().width * 0.55f))
				{
					m_enemies[i]->SetMovingLeft();
				}
			}

			m_enemies[i]->Update(deltaTime, e);

			if ((m_enemies[i]->GetPosition().y > 300.0f || m_enemies[i]->GetPosition().y <= 64.0f) &&
				(m_enemies[i]->GetPosition().x < 64.0f || m_enemies[i]->GetPosition().x > SCREEN_WIDTH - 96.0f))
			{

			}
			else
			{
				if (Collisions::Instance()->Circle(m_enemies[i], my_characterMario))
				{
					if (m_enemies[i]->GetInjured())
					{
						m_enemies[i]->SetAlive(false);
						AddScore(10);
					}
					else
					{
						my_characterMario->SetAlive(false);
					}
				}
			}

			if (!m_enemies[i]->GetAlive())
			{
				enemyIndexToDelete = i;
			}
		}

		if (enemyIndexToDelete != -1)
		{
			m_enemies.erase(m_enemies.begin() + enemyIndexToDelete);
		}
	}
}

void GameScreenLevel1::UpdateCoins(float deltaTime, SDL_Event e)
{
	if (!m_coins.empty())
	{
		int coinIndexToDelete = -1;
		for (unsigned int i = 0; i < m_coins.size(); i++)
		{
			m_coins[i]->Update(deltaTime, e);

			if (Collisions::Instance()->Circle(m_coins[i], my_characterMario))
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

void GameScreenLevel1::CreateKoopa(Vector2D position, FACING direction, float speed)
{
	m_enemies.push_back(new CharacterKoopa(m_renderer, "Images/Koopa.png", m_level_map, position, direction, speed));
}

void GameScreenLevel1::CreateCoin(Vector2D position)
{
	m_coins.push_back(new CharacterCoin(m_renderer, "Images/Coin.png", position, m_level_map));
}
