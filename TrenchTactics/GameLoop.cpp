#include "GameLoop.h"
#include "MenuBar.h"



/**
 * Constructor for game class
 *
 */
Game::Game() {
	Logger::instance().log(LOGLEVEL::INFO, "Starting Game Class");
	playerRed = NULL;
	playerBlue = NULL;
	gameRunning = NULL;
	activePlayer = NULL;
	ctrTurns = 0; 
	endTurn = false;
}

/**
 * Function to init the game
 * Inits: Renderer, ConfigReader, both players, gamefield, eventgateway
 * Sets the active player and starts game loop
 *
 */
void Game::initGame() {
	Logger::instance().log(LOGLEVEL::INFO, "Initializing Game Class");
	Logger::instance().log(LOGLEVEL::INFO, "Initializing Configuration");
	ConfigReader::instance().initConfigurations();
	Logger::instance().log(LOGLEVEL::INFO, "Initializing Players");
	this->playerRed = std::make_shared<Player>();
	this->playerRed->init(true);
	this->playerBlue = std::make_shared<Player>();
	this->playerBlue->init(false);

	EventBus::instance().subscribe(this, &Game::handleEndTurn);

	Logger::instance().log(LOGLEVEL::INFO, "Initializing Renderer");
	this->renderer.init(ConfigReader::instance().getTechnicalConf()->getWindowSizeX(), ConfigReader::instance().getTechnicalConf()->getWindowSizeY(), 16, false);

	Logger::instance().log(LOGLEVEL::INFO, "Initializing Gamefield");
	this->field.init(ConfigReader::instance().getMapConf()->getSizeX(), ConfigReader::instance().getMapConf()->getSizeY(), ConfigReader::instance().getMapConf()->getSeed());

	Logger::instance().log(LOGLEVEL::INFO, "Initializing MenuBar");
	this->menuBar.init();

	Logger::instance().log(LOGLEVEL::INFO, "Initializing Gateway");
	this->gateway.init();

	this->activePlayer = playerBlue;
	this->gateway.setActivePlayer(playerBlue);

	this->gameRunning = true;

	this->renderer.updateTimer();

	startGame();

}

/**
 * Main game loop
 * switches between gamephases and players
 * updates players each loop
 * controlled by gameRunning variable
 *
 */
void Game::startGame() {
	Logger::instance().log(LOGLEVEL::INFO, "Game Running");
	// start a player phase and switch player afterwards

	while (gameRunning) {
		this->ctrTurns++; 

		if (this->ctrTurns > 2)
		{
			// update player with income and stuff  
			this->activePlayer->updatePlayer();
		}

		startPlayerPhase();
		switchActivePlayer();
	}
	quit();
}

/**
 * start a player phase
 * in buy phase: waits for purchase
 * in move and attack phase: inits the queue of a player with every unit and waits until its empty
 *
 * when condition is met the next phase of a player starts
 * should update the game every time in the time waiting for the empty queue
 *
 */
void Game::startPlayerPhase() {
	//loop over the different phases and wait for the active player to finish it
	for (GAMEPHASES::GAMEPHASE phase : GAMEPHASES::All) {

		if (this->endTurn == true) {
			endTurn = false;
			break;
		}

		this->activePlayer->setCurrentPhase(phase);
		this->gateway.setCurrentPhase(phase);

		if (phase == GAMEPHASES::BUY) {
			this->startBuyPhase();
		}

		
		else if (phase == GAMEPHASES::MOVE) {
			this->startMovePhase();
		}
		else if (phase == GAMEPHASES::ATTACK) {
			if (ctrTurns > 2) {
				this->startAttackPhase();
			}
		}

		// update game while in phase, buy phase as long as player buys, attack and move as long as there are units to move and stuff
		while (!this->activePlayer->getUnitQueue().empty() || this->activePlayer->getBuying()) {
			updateGame();
		}

		
	}
}

/**
 * updates timer of the game
 * triggers the event manager to forward the events
 *
 */
void Game::updateGame() {
	std::vector<std::shared_ptr<Unit>> unitsBlue = this->playerBlue->getUnitArray();
	std::vector<std::shared_ptr<Unit>> unitsRed = this->playerRed->getUnitArray();

	for (std::shared_ptr<Unit>& unit : unitsBlue)
	{
		if (Gamefield::instance().findTileByUnit(unit).get() != nullptr) {
			Gamefield::instance().findTileByUnit(unit).get()->refreshTile();
		}

		unit->update();
	}

	for (std::shared_ptr<Unit>& unit : unitsRed)
	{
		if (Gamefield::instance().findTileByUnit(unit).get() != nullptr) {
			Gamefield::instance().findTileByUnit(unit).get()->refreshTile();
		}

		unit->update();
	}

	renderer.updateTimer();
	manager.processEvents();

}

void Game::handleEndTurn(EndTurnEvent* event)
{
	this->endTurn = true;
}

/**
 * quits the game
 *
 */
void Game::quit() {
	this->gameRunning = false;
}

/**
 * switch the acitve player based on the color of the active player
 *
 */
void Game::switchActivePlayer() {
	this->activePlayer->demarkActiveUnit();
	this->endTurn = false;
	if (this->activePlayer->getColor()) {
		this->activePlayer = playerBlue;
		this->gateway.setActivePlayer(playerBlue);
	}
	else {
		this->activePlayer = playerRed;
		this->gateway.setActivePlayer(playerRed);
	}
	this->activePlayer->resetApForAllUnits();
}

/**
 * setup attack phase
 * copys units to queue and displays buttons
 * set the gateway state
 *
 */
void Game::startAttackPhase() {

	menuBar.resetUnitStats();
	menuBar.updateMenuBar(GAMEPHASES::ATTACK, activePlayer);
	this->gateway.setCurrentPhase(GAMEPHASES::ATTACK);
	this->activePlayer->copyUnitsToQueue();


	//if (!this->activePlayer->getUnitQueue().empty())
		//Gamefield::instance().selectAndMarkeTilesByUnit(this->activePlayer->getUnitQueue().front(), GAMEPHASES::ATTACK, this->activePlayer->getColor());

	this->activePlayer->markActiveUnit();
	//this->activePlayer->popUnit();

}

/**
 * setup buy phase
 * set active player to be in buying state and displays buttons
 * set the gateway state
 *
 */
void Game::startBuyPhase() {
		menuBar.resetUnitStats();

			menuBar.updateMenuBar(GAMEPHASES::BUY, activePlayer);
			this->activePlayer->setBuying(true);
			this->gateway.setCurrentPhase(GAMEPHASES::BUY);

}

/**
 * setup move phase
 * copys units to queue and displays buttons
 * set the gateway state
 *
 */
void Game::startMovePhase() {



	Gamefield::instance().deselectAndUnmarkAllTiles();
	menuBar.updateMenuBar(GAMEPHASES::MOVE, activePlayer);
	this->gateway.setCurrentPhase(GAMEPHASES::MOVE);
	this->activePlayer->copyUnitsToQueue();

	//if (!this->activePlayer->getUnitQueue().empty())
		//Gamefield::instance().selectAndMarkeTilesByUnit(this->activePlayer->getUnitQueue().front(), GAMEPHASES::MOVE, this->activePlayer->getColor());
	
	menuBar.reInitButtons(GAMEPHASES::MOVE);  
	this->activePlayer->markActiveUnit();
	

}