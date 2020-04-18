#include "GameLoop.h"
#include "Logger.hpp"
#include "RendererImpl.h"
#include "Timer.hpp"
#include "ConfigReader.h"
#include "UnitBase.h"

Game::Game() {
	Logger::instance().log(LOGLEVEL::INFO, "Starting Game Class");
	playerRed = NULL;
	playerBlue = NULL;
	gamefield = NULL;
	gameRunning = NULL;
	activePlayer = NULL;
}

void Game::initGame() {
	Logger::instance().log(LOGLEVEL::INFO, "Initializing Game Class");
	this->playerRed = new Player();
	this->playerRed->init(true);
	this->playerBlue = new Player();
	this->playerBlue->init(false);

	this->gamefield = new Gamefield();
	//this->gamefield.init();

	RendererImpl::instance().init(ConfigReader::instance().getTechnicalConf()->getWindowSizeX(), ConfigReader::instance().getTechnicalConf()->getWindowSizeY());
	this->activePlayer = playerRed;
	this->gameRunning = true;
	gameLoop();
}


void Game::gameLoop() {
	while (gameRunning) {
		startPhase();
		switchActivePlayer();
	}
	quit();
}
void Game::startPhase() {
	this->activePlayer->copyUnitsToQueue();
	for (GAMPHASES::GAMEPHASE phase : GAMPHASES::All) {
		this->activePlayer->setCurrentPhase(phase);
		while (!activePlayer->getUnitQueue().empty()) {
			updateGame();
		}
	}

}

void Game::updateGame() {
	//this->gamefield.update();
	RendererImpl::instance().updateTimer();
}
void Game::quit() {
}
void Game::switchActivePlayer() {
	if (this->activePlayer->getColor()) {
		this->activePlayer = playerRed;
	}
	else {
		this->activePlayer = playerBlue;
	}
}