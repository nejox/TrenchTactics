#pragma once
#include "Player.h"
#include "Timer.hpp"
#include "Gamefield.h"
#include "Logger.hpp"
#include "IRenderer.h"
#include "RendererImpl.h"
#include "Timer.hpp"
#include "ConfigReader.h"
#include "Unit.h"
#include "EventGateway.h"
#include "EventManagerImpl.h"

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
	IEventManager& manager = EventManagerImpl::instance();
	IRenderer& renderer = RendererImpl::instance();

	bool gameRunning;
	void switchActivePlayer();
public:
	Game();
	void initGame();
	void startPhases();
	void gameLoop();
	void quit();
	void updateGame();


};

