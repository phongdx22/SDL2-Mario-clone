#pragma once
#include "GameScreen.h"
#include "Commons.h"
#include "constants.h"
#include "CharacterMario.h"

class GameScreenMainMenu : GameScreen
{
public:
	GameScreenMainMenu(SDL_Renderer* renderer);
	~GameScreenMainMenu();

	void Render() override;
	void Update(float deltaTime, SDL_Event e);

private:
	int position1y;
	int position2y;
	TextRenderer* startText;
	TextRenderer* quitText;
	TextRenderer* titleText;
	Character* my_characterMario;
	LevelMap* m_level_map;

	bool SetUpLevel();
};

