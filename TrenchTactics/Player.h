#pragma once
#include "Headquarter.h"
#include "Unit.h"
#include "DeathEvent.h"
#include "EventBus.h"
#include "Gamephases.h"
#include "ConfigReader.h"
#include <vector>
#include <queue>
#include <algorithm>

/**
 * Player main class - holds most of the informations
 * controlls units of player as well as money and supply of a player
 */
class Player
{
private:
	bool colorRed;
	bool buying;
	Headquarter* headquarter;
	std::vector<std::shared_ptr<Unit>> unitArray;
	std::queue<std::shared_ptr<Unit>> unitQueue;
	int money;
	int supply;
	GAMEPHASES::GAMEPHASE currentPhase;
public:
	Player();
	void init(bool colorRed);
	void computeInterest();
	void updatePlayer();
	void copyUnitsToQueue();
	void demarkActiveUnit();
	void markActiveUnit();
	void emptyQueue() {
		while (!this->unitQueue.empty()) {
			this->unitQueue.pop();
		}
	}
	void popUnit() {
		this->unitQueue.pop();
	}
	void queueUnit(std::shared_ptr<Unit> unit) {
		this->unitQueue.push(unit);
	}
	void addUnit(std::shared_ptr<Unit> unit) {
		this->unitArray.push_back(unit);
	}
	std::vector<std::shared_ptr<Unit>> getUnitArray() {
		return this->unitArray;
	}
	std::queue<std::shared_ptr<Unit>> getUnitQueue() {
		return this->unitQueue;
	}
	int getSupply() {
		return this->supply;
	}
	int getMoney() {
		return this->money;
	}
	bool getColor() {
		return this->colorRed;
	}
	void setCurrentPhase(GAMEPHASES::GAMEPHASE phase) {
		this->currentPhase = phase;
	}
	GAMEPHASES::GAMEPHASE getCurrentPhase() {
		return this->currentPhase;
	}
	void setBuying(bool buyStatus) {
		this->buying = buyStatus;
	}
	bool getBuying() {
		return this->buying;
	}
	void deleteUnit(DeathEvent* deathEvent);
};
