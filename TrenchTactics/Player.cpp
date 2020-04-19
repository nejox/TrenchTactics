#include "Player.h"

void Player::init(bool colorRed) {
	this->colorRed = colorRed;
	this->money = ConfigReader::instance().getBalanceConf()->getStartingGold();
	// subscribe tp deletion of units aka killing them
	//EventBus::instance().subscribe()
}
int Player::computeInterest() {
	int income = this->money / 10;
	this->money += income;
	this->money += 3;

	//Income(m, t) = m(0.05t) / (0.85 + 0.055t) + 25;
}
void Player::updatePlayer() {
	this->money += computeInterest();
	this->supply = this->unitArray.size();
}
void Player::copyUnitsToQueue() {
	for (UnitBase* unit : this->unitArray) {
		this->unitQueue.push(unit);
	}
}

void Player::deleteUnit(UnitBase* unit) {
	std::vector<UnitBase*>::iterator position = std::find(this->unitArray.begin(), this->unitArray.end(), unit);
	if (position != this->unitArray.end()) {// == myVector.end() means the element was not found
		this->unitArray.erase(position);
	}

}