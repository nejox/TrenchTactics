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
}

/**
 * add the interest to a players money
 * based on a simple formular
 * base income plus 15% of the current money of the player
 *
 */
int Player::computeInterest() {
	return (100 + 0.15 * this->money);
}


/**
 * update player by computing the interest as well as updating current supply
 *
 */
void Player::updatePlayer() {
	this->updateMoney(computeInterest());
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
				if (this->unitArray[j]->getCurrentAP() >= this->unitArray[j]->getApCostAttack() && Gamefield::instance().checkUnitHasEnemysAround(this->unitArray[j],this->getColor())) {
					this->unitQueue.push(this->unitArray[j]);
				}
			}
			else {
				this->unitQueue.push(this->unitArray[j]);
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
		this->unitQueue.front()->setState(STATES::UNITSTATE::STANDING);
		MenuBar::instance().updateUnitStats(this->getUnitQueue().front());
		Gamefield::instance().selectAndMarkeTilesByUnit(this->unitQueue.front(), this->currentPhase, this->getColor());
	}
}

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
 * demarks the active Unit = the first one in the queue
 *
 */
void Player::demarkActiveUnit()
{
	//mark the first unit to be moved as neutral
	if (!unitQueue.empty()) {
		this->unitQueue.front()->setState(STATES::UNITSTATE::STANDING_NEUTRAL);
		MenuBar::instance().resetUnitStats();
	}
	Gamefield::instance().deselectAndUnmarkAllTiles();
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