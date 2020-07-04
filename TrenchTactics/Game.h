#pragma once
#include "Player.h"
#include "Gamefield.h"
#include "Logger.hpp"
#include "IRenderer.h"
#include "RendererImpl.h"
#include "Timer.h"
#include "ConfigReader.h"
#include "Unit.h"
#include "EventGateway.h"
#include "EventManagerImpl.h"
#include "Gamephases.h"
#include "MenuBar.h"
#include "EndTurnEvent.h"
#include "EndGameEvent.h"
#include "Menu.h"
#include "StartGameEvent.h"
#include "Tutorial.h"
#include "EndTutorialEvent.h"
#include "IngameMenuEvent.h"
#include "ReturnToMenuEvent.h"
#include "GameEnd.h"

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
	Menu& menu =  Menu::instance();
	Tutorial& tutorial = Tutorial::instance();

	bool isTutorial;
	bool gameOver = false;
	void switchActivePlayer();
	void startBuyPhase();
	void startMovePhase();
	void startAttackPhase();
	void resetGame();
public:
	Game();

	bool isRunning();
	void initGame();
	void startMenu();
	void startTutorial();
	void startPlayerPhase();
	void startGame();
	void quit(EndGameEvent* event);
	void updateGame();
	void handleEndTurn(EndTurnEvent* event);
	void handleStartGame(StartGameEvent* event);
	void handleStartTutorial(StartTutorialEvent* event);
	void handleEndTutorial(EndTutorialEvent* event);
	void handleIngameMenu(IngameMenuEvent* event);
	void handleReturnToMenu(ReturnToMenuEvent* event);
	void handleGameEnd(GameEndEvent* event);


};
