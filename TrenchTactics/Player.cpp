#include "Player.h"
#include "Gamefield.h"




Player::Player() {
	this->supply = 0;
	this->money = 0;
	this->buying = false;
}



/**
 * Init player with starting money as well as subscription to delete unit events
 *
 * \param colorRed set the color of the player(red if true)
 */
void Player::init(bool colorRed) {
	this->colorRed = colorRed;
	this->money = ConfigReader::instance().getBalanceConf()->getStartingGold();
	//this->unitArray = std::vector<std::shared_ptr<Unit>>();
	EventBus::instance().subscribe(this, &Player::deleteUnit);
	EventBus::instance().subscribe(this, &Player::handleUnitMovement);
}

/**
 * computes the income from a simple formula
 *  based on the current position of occupied trenches
 *  every occupied trench adds its x distance from the HQ / 100 to the interestfactor
 *	100 + interestfactor * leftover money is the new income
 */
int Player::computeIncome() {

	//modifier which sums up all trenchpositions / 100 as a modifier
	float trenchCount = 0.0f;

	//iterate over unitArray and for every unit check if it is in a trench
	for (std::shared_ptr<Unit> unit : unitArray)
	{
		shared_ptr<FieldTile> tmp = Gamefield::instance().findTileByUnit(unit);

		if (tmp->hasTrench())
		{
			//check which player and add the position of the trench/100 to trenchcount
			if (this->colorRed) {
				trenchCount += abs(21.0f - (tmp->getPosX() / 64.0f)) / 100.0f;
			}

			else {
				trenchCount += ((tmp->getPosX() / 64.0f) / 100.0f);
			}
		}
	}

	return (100 + (int)(trenchCount * this->money));
}


/**
 * update player by computing the interest as well as updating current supply
 *
 */
void Player::updatePlayer() {
	this->updateMoney(computeIncome());
	//this->supply = this->unitArray.size();
}

/**
 * Initialize player unit queue to cycle through each of them
 *
 */
void Player::copyUnitsToQueue() {
	if (this->unitArray.size() > 0) {
		int i = this->unitArray.size() - 1;
		for (int j = i; j >= 0; j--) {
			if (this->getCurrentPhase() == GAMEPHASES::GAMEPHASE::ATTACK) {
				if ((this->unitArray[j]->getCurrentAP() >= this->unitArray[j]->getApCostAttack()
					&& Gamefield::instance().checkUnitHasEnemysAround(this->unitArray[j], this->getColor()))
					|| (this->unitArray[j]->getCurrentAP() >= this->unitArray[j]->getApCostTrench()
						&& !Gamefield::instance().findTileByUnit(this->unitArray[j])->hasTrench())) {
					this->queueUnit(this->unitArray[j]);
				}
			}
			else {
				this->queueUnit(this->unitArray[j]);
			}

		}
	}

	/*for (std::shared_ptr<Unit> unit : this->unitArray) {
		this->unitQueue.push(unit);
	}*/
}

/**
 * marks the active Unit = the first one in the queue
 *
 */
void Player::markActiveUnit()
{
	Gamefield::instance().deselectAndUnmarkAllTiles();
	//mark the first unit to be moved as active 
	if (!unitQueue.empty()) {
		if (this->unitQueue.front()->getState() != STATES::RUNNING) {
			this->unitQueue.front()->setState(STATES::UNITSTATE::STANDING);
		}
		MenuBar::instance().updateUnitStats(this->getUnitQueue().front());
		Gamefield::instance().selectAndMarkeTilesByUnit(this->unitQueue.front(), this->currentPhase, this->getColor());
	}
}

void Player::requeueUnit() {
	shared_ptr<Unit> tmp = this->unitQueue.front();
	//no new state here
	this->unitQueue.pop();
	//but here, so we stay in standing neutral,bright and shiny
	this->queueUnit(tmp);

}

/**
 * wrapper function to pop a unit in the queue.
 * don't ask me why we need this but we do
 * Sets defaultState for units
 * updates unit to show the new state immediately
 */
void Player::popUnit() {
	if (this->unitQueue.front()->getState() != STATES::RUNNING) {
		this->unitQueue.front()->setState(STATES::STANDING_DARK);
		this->unitQueue.front()->update();
	}
	this->unitQueue.pop();
}

/**
 * Add unit to the queue.
 * sets defaulltState for units
 * \param unit that will be added
 */
void Player::queueUnit(std::shared_ptr<Unit> unit) {
	this->unitQueue.push(unit);
	if (unit->getState() != STATES::RUNNING) {
		unit->setState(STATES::STANDING_NEUTRAL); 
		unit->update();
	}
}

/**
 * resets the whole player to inital state
 *
 */
void Player::resetPlayer()
{
	this->money = ConfigReader::instance().getBalanceConf()->getStartingGold();
	this->unitArray.clear();
	this->buying = false;
	//the c++ way to clear the queue...
	std::queue<std::shared_ptr<Unit>>().swap(unitQueue);
}

/**
 * retrurns if player can buy units
 *
 */
bool Player::checkPlayerCanBuyUnits()
{
	for (int i = 0; i < 3; i++) {
		std::shared_ptr<UnitConf> unit = ConfigReader::instance().getUnitConf(i);
		if (this->getMoney() >= unit->getCost()) {
			return true;
		}
	}

	return false;
}

/**
 * handles unit movement
 *
 */
void Player::handleUnitMovement(UnitMovementFinishedEvent* event)
{
	if (!this->unitQueue.empty()) {
		if (this->unitQueue.front() == event->getMovingUnit()) {
			event->getMovingUnit()->setState(STATES::STANDING);
			cout << "standing" << endl;
		}
		//the next 2 conditions check in which state to set the unit, because queueUnit keeps skipping them
		else if (event->getMovingUnit()->getCurrentAP() >= event->getMovingUnit()->getApCostAttack()
			|| event->getMovingUnit()->getCurrentAP() >= event->getMovingUnit()->getApCostTrench()) {
			event->getMovingUnit()->setState(STATES::STANDING_NEUTRAL); 
			cout << "neutral" << endl;
		}
		else {
			event->getMovingUnit()->setState(STATES::STANDING_DARK);
			cout << "dark" << endl;
		}
	}

}

/**
 * demarks the active Unit = the first one in the queue
 *
 */
void Player::demarkActiveUnit()
{
	//mark the first unit to be moved as neutral
	if (!unitQueue.empty()) {

		if (this->unitQueue.front()->getState() != STATES::RUNNING) {
			this->unitQueue.front()->setState(STATES::STANDING_DARK);
		}
		MenuBar::instance().resetUnitStats();
	}
	Gamefield::instance().deselectAndUnmarkAllTiles();
}

void Player::updateMoney(int amount)

{
	this->money += amount;
	if (this->money > 9999)
	{
		this->money = 9999;
	}

	else if (this->money < 0) {
		this->money = 0;
	}
}

/**
 * Delete unit from player after its death
 * Searching the player list to find the corresponding unit
 * \param deathEvent event holding unit to be deleted
 */
void Player::deleteUnit(DeathEvent* deathEvent) {


	//if unit belongs to player
	if (this->colorRed == deathEvent->getKilledUnit()->getColorRed()) {

		//if unit is placed anywhere
		if (Gamefield::instance().findTileByUnit(deathEvent->getKilledUnit()).get()) {

			// if no corpse on the field adds corpse with coordinates of death unit 
			if (!(Gamefield::instance().findTileByUnit(deathEvent->getKilledUnit())->hasCopse())) {
				Gamefield::instance().findTileByUnit(deathEvent->getKilledUnit())->addCorpse();
			}

			Gamefield::instance().findTileByUnit(deathEvent->getKilledUnit()).get()->removeUnit();


		}
		std::vector<std::shared_ptr<Unit>>::iterator position = std::find(this->unitArray.begin(), this->unitArray.end(), deathEvent->getKilledUnit());

		if (unitArray.size() > 1) {
			if (position != this->unitArray.end()) { // == myVector.end() means the element was not found
				this->unitArray.erase(position);
			}
		}
		else {
			this->unitArray.erase(unitArray.begin());
		}
	}

}