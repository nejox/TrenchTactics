#include "GameLoop.h"


Game::Game() {
	Logger::instance().log(LOGLEVEL::INFO, "Starting Game Class");
	playerRed = NULL;
	playerBlue = NULL;
	gameRunning = NULL;
	activePlayer = NULL;
}

void Game::initGame() {
	Logger::instance().log(LOGLEVEL::INFO, "Initializing Game Class");
	Logger::instance().log(LOGLEVEL::INFO, "Initializing Configuration");
	ConfigReader::instance().initConfigurations();
	Logger::instance().log(LOGLEVEL::INFO, "Initializing Players");
	this->playerRed = new Player();
	this->playerRed->init(true);
	this->playerBlue = new Player();
	this->playerBlue->init(false);

	Logger::instance().log(LOGLEVEL::INFO, "Initializing Gamefield");
	Gamefield::instance().init(ConfigReader::instance().getMapConf()->getSizeX(), ConfigReader::instance().getMapConf()->getSizeY(), ConfigReader::instance().getMapConf()->getSeed());

	Logger::instance().log(LOGLEVEL::INFO, "Initializing Renderer");
	renderer.init(ConfigReader::instance().getTechnicalConf()->getWindowSizeX(), ConfigReader::instance().getTechnicalConf()->getWindowSizeY());
	this->activePlayer = playerRed;
	this->gameRunning = true;
	EventGateway::instance().init();
	gameLoop();
}


void Game::gameLoop() {
	Logger::instance().log(LOGLEVEL::INFO, "Game Running");
	while (gameRunning) {
		startPhases();
		switchActivePlayer();
		this->activePlayer->updatePlayer();
	}
	quit();
}
void Game::startPhases() {
	this->activePlayer->copyUnitsToQueue();
	for (GAMEPHASES::GAMEPHASE phase : GAMEPHASES::All) {
		this->activePlayer->setCurrentPhase(phase);
		if (phase = GAMEPHASES::BUY) {
			this->activePlayer->setBuying(true);
		}
		while (!this->activePlayer->getUnitQueue().empty() || this->activePlayer->getBuying()) {
			updateGame();
		}

	}

}

void Game::updateGame() {
	renderer.updateTimer();
	manager.processEvents();
}

void Game::quit() {
	this->gameRunning = false;
}

void Game::switchActivePlayer() {
	if (this->activePlayer->getColor()) {
		this->activePlayer = playerRed;
	}
	else {
		this->activePlayer = playerBlue;
	}
}