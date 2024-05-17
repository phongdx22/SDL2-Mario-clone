#pragma once
#ifndef _GAMESCREENLEVEL1_H_
#define _GAMESCREENLEVEL1_H_

#include "GameScreen.h"
#include "Commons.h"
#include "Texture2D.h"
#include "Character.h"
#include "CharacterMario.h"
#include "CharacterLuigi.h"
#include "CharacterKoopa.h"
#include "CharacterCoin.h"
#include "Collisions.h"
#include "LevelMap.h"
#include <vector>

class Texture2D;
class Character;
class PowBlock;

class GameScreenLevel1 : GameScreen
{
public:
	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;
	void UpdatePOWBlock();

private:
	Texture2D* m_background_texture;
	Character* my_characterMario;
	Character* my_characterLuigi;
	CharacterCoin* m_coin;
	LevelMap* m_level_map;
	PowBlock* m_pow_block;
	bool m_screenshake;
	float m_shake_time;
	float m_wobble;
	float m_background_yPos;
	float m_koopaTimer;
	vector<CharacterKoopa*> m_enemies;

	bool SetUpLevel();
	void SetLevelMap();
	void DoScreenShake();
	void UpdateEnemies(float deltaTime, SDL_Event e);
	void CreateKoopa(Vector2D position, FACING direction, float speed);
};

#endif // _GAMESCREENLEVEL1_H_
