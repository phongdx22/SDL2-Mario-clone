#pragma once
#include "GameScreen.h"
#include "Commons.h"
#include "constants.h"

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

	bool SetUpLevel();
};

