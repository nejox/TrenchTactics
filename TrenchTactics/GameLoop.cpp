#include "GameLoop.h"



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
	ctrRounds = 0;
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
	this->field.init(ConfigReader::instance().getMapConf()->getSizeX(), ConfigReader::instance().getMapConf()->getSizeY(), ConfigReader::instance().getMapConf()->getSeed());
	while (gameRunning) {
		this->ctrRounds++;
		startPlayerPhase();
		switchActivePlayer();
		// update player with income and stuff
		this->activePlayer->updatePlayer();
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

		this->activePlayer->setCurrentPhase(phase);
		this->gateway.setCurrentPhase(phase);

		if (phase == GAMEPHASES::BUY) {
			this->startBuyPhase();
		}
		else if (phase == GAMEPHASES::MOVE) {
			this->startMovePhase();
		}
		else if (phase == GAMEPHASES::ATTACK) {
			if (ctrRounds > 2) {
				this->startAttackPhase();
			}
		}
		if (this->endTurn == true) {
			endTurn = false;
			break;
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
		Gamefield::instance().findeTileByUnit(unit).get()->refreshTile();
		unit->update();
	}

	for (std::shared_ptr<Unit>& unit : unitsRed)
	{
		Gamefield::instance().findeTileByUnit(unit).get()->refreshTile();
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
	if (this->activePlayer->getColor()) {
		this->activePlayer = playerBlue;
		this->gateway.setActivePlayer(playerBlue);
	}
	else {
		this->activePlayer = playerRed;
		this->gateway.setActivePlayer(playerRed);
	}
}

/**
 * setup attack phase
 * copys units to queue and displays buttons
 * set the gateway state
 *
 */
void Game::startAttackPhase() {
	Gamefield::instance().deleteButtons();
	this->activePlayer->copyUnitsToQueue();
	this->activePlayer->markActiveUnit();
	//this->activePlayer->popUnit();
	Gamefield::instance().displayButtons(GAMEPHASES::ATTACK);
}

/**
 * setup buy phase
 * set active player to be in buying state and displays buttons
 * set the gateway state
 *
 */
void Game::startBuyPhase() {
	Gamefield::instance().deleteButtons();
	this->activePlayer->setBuying(true);
	Gamefield::instance().displayButtons(GAMEPHASES::BUY);
}

/**
 * setup move phase
 * copys units to queue and displays buttons
 * set the gateway state
 *
 */
void Game::startMovePhase() {
	Gamefield::instance().deleteButtons();
	this->activePlayer->copyUnitsToQueue();
	this->activePlayer->markActiveUnit();

	Gamefield::instance().displayButtons(GAMEPHASES::MOVE);
}