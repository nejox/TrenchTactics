#include "Player.h"


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
void Player::computeInterest() {
	this->money += 30 + 0.15 * this->money;

}

/**
 * update player by computing the interest as well as updating current supply
 *
 */
void Player::updatePlayer() {
	computeInterest();
	//this->supply = this->unitArray.size();
}

/**
 * Initialize player unit queue to cycle through each of them
 *
 */
void Player::copyUnitsToQueue() {
	for (std::shared_ptr<Unit> unit : this->unitArray) {
		this->unitQueue.push(unit);
	}
}

/**
 * marks the active Unit = the first one in the queue
 *
 */
void Player::markActiveUnit()
{
    //mark the first unit to be moved as active 
    if (!unitQueue.empty()) {
        this->unitQueue.front()->setState(STATES::UNITSTATE::STANDING);
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
        this->unitQueue.front()->setState(STATES::UNITSTATE::STANDING_NEUTRAL);
    }
}

/**
 * Delete unit from player after its death
 * Searching the player list to find the corresponding unit
 * \param deathEvent event holding unit to be deleted
 */
void Player::deleteUnit(DeathEvent* deathEvent) {
	std::vector<std::shared_ptr<Unit>>::iterator position = std::find(this->unitArray.begin(), this->unitArray.end(), deathEvent->getKilledUnit());
	if (position != this->unitArray.end()) {// == myVector.end() means the element was not found
		this->unitArray.erase(position);
	}

}