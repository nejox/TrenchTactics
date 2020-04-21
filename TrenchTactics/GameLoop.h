#pragma once
#include "Player.h"
#include "Timer.hpp"
#include "Gamefield.h"

// enum for gamephases
enum GAMEPHASE
{
	BUY,
	MOVE,
	ATTACK
};


class Game
{
private:
	Player* playerRed;
	Player* playerBlue;
	Player* activePlayer;
	Gamefield* gamefield;
	bool gameRunning;
	GAMEPHASE currentPhase;
	void switchActivePlayer();
public:
	Game();
	void initGame();
	void startPhase();
	void gameLoop();
	void quit();
	void updateGame();

};

