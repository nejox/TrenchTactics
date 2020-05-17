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
#include "Gamephases.h"
#include "MenuBar.h"
#include "EndTurnEvent.h"
#include "EndGameEvent.h"

/**
 * Main class to start the game
 * initializes all necessary components: Renderer, Eventmanager, Players
 * Also has the main game loop
 */
class Game
{
private:
	int ctrTurns;
	bool endTurn;
	std::shared_ptr<Player> playerRed;
	std::shared_ptr<Player>  playerBlue;
	std::shared_ptr<Player>  activePlayer;
	IEventManager& manager = EventManagerImpl::instance();
	IRenderer& renderer = RendererImpl::instance();
	Gamefield& field = Gamefield::instance();
	EventGateway& gateway = EventGateway::instance();
	MenuBar& menuBar = MenuBar::instance();


	bool gameRunning;
	void switchActivePlayer();
	void startBuyPhase();
	void startMovePhase();
	void startAttackPhase();
public:
	Game();
	void initGame();
	void startPlayerPhase();
	void startGame();
	void quit(EndGameEvent* event);
	void updateGame();
	void handleEndTurn(EndTurnEvent* event);

};
