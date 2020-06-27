#pragma once
#include "Headquarter.h"
#include "Unit.h"
#include "DeathEvent.h"
#include "EventBus.h"
#include "Gamephases.h"
#include "Gamefield.h"
#include "ConfigReader.h"
#include <vector>
#include <queue>
#include <algorithm>
#include "UnitMovementFinishedEvent.h"

/**
 * Player main class - holds most of the informations
 * controlls units of player as well as money and supply of a player
 */
class Player
{
private:
	bool colorRed;
	bool buying;
	std::shared_ptr<Headquarter> headquarter;
	// list holds all units of a player 
	std::vector<std::shared_ptr<Unit>> unitArray;
	// queue holds all units in a phase to be able to process them one after another
	std::queue<std::shared_ptr<Unit>> unitQueue;
	int money;
	int supply;
	GAMEPHASES::GAMEPHASE currentPhase;
public:
	Player();
	void init(bool colorRed);
	int computeIncome();
	void updatePlayer();
	void copyUnitsToQueue();
	void demarkActiveUnit();
	void markActiveUnit();
	void resetPlayer();
	bool checkPlayerCanBuyUnits();
	void handleUnitMovement(UnitMovementFinishedEvent* event);

	/**
	 * empties the unitQueue of the player.
	 *
	 */
	void emptyQueue() {
		while (!this->unitQueue.empty()) {
			this->popUnit();
		}
	}

	void requeueUnit();

	/**
	 * wrapper function to pop a unit in the queue.
	 * don't ask me why we need this but we do
	 * Sets defaultState for units
	 * updates unit to show the new state immediately
	 */
	void popUnit(); 

	/**
	 * Add unit to the queue.
	 * sets defaulltState for units
	 * \param unit that will be added
	 */
	void queueUnit(std::shared_ptr<Unit> unit);
	/**
	* checks if unit is in Queue
	* \param unitToFind unit to find in queue
	* \return true if the queue contains the unit or false if not
	*/
	bool unitInQueue(std::shared_ptr<Unit> unitToFind);

	/**
	 * add unit to the list of units of a player.
	 *
	 * \param unit
	 */
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

	/**
	 * update the money with the given amount.
	 * cuts values greater than 9999
	 *
	 * \param amount the amount of money you want to add to the players bank
	 */
	void updateMoney(int amount);

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

	void resetApForAllUnits();
};
