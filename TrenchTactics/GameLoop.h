#pragma once
#include "Player.h"
#include "Timer.hpp"
#include "Gamefield.h"

// enum for gamephases
namespace GAMEPHASES {
	enum GAMEPHASE
	{
		BUY,
		MOVE,
		ATTACK
	};
	static const GAMEPHASE All[] = { BUY, MOVE, ATTACK };

}
class Game
{
private:
	Player* playerRed;
	Player* playerBlue;
	Player* activePlayer;
	Gamefield* gamefield;

	bool gameRunning;
	void switchActivePlayer();
public:
	Game();
	void initGame();
	void startPhase();
	void gameLoop();
	void quit();
	void updateGame();


};

