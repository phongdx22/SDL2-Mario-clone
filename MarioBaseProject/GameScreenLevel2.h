#pragma once
#ifndef _GAMESCREENLEVEL2_H_
#define _GAMESCREENLEVEL2_H_

#include "GameScreen.h"
#include "Commons.h"
#include "Texture2D.h"
#include "Character.h"
#include "CharacterMario.h"
#include "CharacterLuigi.h"
#include "CharacterCoin.h"
#include "Collisions.h"
#include "LevelMap.h"
#include "TextRenderer.h"
#include <vector>

class Texture2D;
class Character;
class PowBlock;

class GameScreenLevel2 : GameScreen
{
public:
	GameScreenLevel2(SDL_Renderer* renderer);
	~GameScreenLevel2();

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;
	void UpdatePOWBlock();

private:
	Texture2D* m_background_texture;
	Character* my_characterMario;
	Character* my_characterLuigi;
	LevelMap* m_level_map;
	PowBlock* m_pow_block;
	bool m_screenshake;
	float m_shake_time;
	float m_wobble;
	float m_background_yPos;
	float m_coinTimer;
	int m_score;
	vector<CharacterCoin*> m_coins;
	TextRenderer* scoreText;
	Player currentPlayer = Player::PLAYER_1;
	Player board[BOARD_SIZE][BOARD_SIZE] = { {Player::NONE} };

	bool SetUpLevel();
	void SetLevelMap();
	void DoScreenShake();
	void UpdateCoins(float deltaTime, SDL_Event e);
	void CreateCoin(Vector2D position, int boardpos);
	void AddScore(int score) { m_score += score; }
	void DrawBoard();
	void DrawXAndO(Player board[BOARD_SIZE][BOARD_SIZE]);
	bool CheckWin(Player player);
};

#endif // _GAMESCREENLEVEL2_H_


