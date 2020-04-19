#include "Player.h"

void Player::init(bool colorRed) {
	this->colorRed = colorRed;
	this->money = ConfigReader::instance().getBalanceConf()->getStartingGold();
	EventBus::instance().subscribe(this, &Player::deleteUnit);
}

int Player::computeInterest() {
	this->money += 30 + 0.15 * this->money;

}
void Player::updatePlayer() {
	this->money += computeInterest();
	this->supply = this->unitArray.size();
}
void Player::copyUnitsToQueue() {
	for (Unit* unit : this->unitArray) {
		this->unitQueue.push(unit);
	}
}

void Player::deleteUnit(DeathEvent* deathEvent) {
	std::vector<Unit*>::iterator position = std::find(this->unitArray.begin(), this->unitArray.end(), deathEvent->getKilledUnit());
	if (position != this->unitArray.end()) {// == myVector.end() means the element was not found
		this->unitArray.erase(position);
	}

}