#include "Player.h"

void Player::init(bool colorRed) {
	this->colorRed = colorRed;
}
int Player::computeInterest() {
}
void Player::updatePlayer() {
	this->money = +computeInterest();
	this->supply = this->unitArray.size();
}
void Player::copyUnitsToQueue() {
	for (UnitBase* unit : this->unitArray) {
		this->unitQueue.push(unit);
	}
}