#include "EventGateway.h"


/**
 * init function that subscribs to mouse events
 *
 */
void EventGateway::init() {
	EventBus::instance().subscribe(this, &EventGateway::handleEvent);
}

/**
 * takes the mouseclick event and forwards it to the specific handler function
 * based on the current gamephase
 *
 * \param event mouseclickevent with position of the event
 */
void EventGateway::handleEvent(MouseClickEvent* event) {
	if (this->currentPhase == GAMEPHASES::ATTACK) {
		this->handleAttackEvent(event);
	}
	else if (this->currentPhase == GAMEPHASES::BUY) {
		this->handleBuyEvent(event);
	}
	else if (this->currentPhase == GAMEPHASES::MOVE) {
		this->handleMoveEvent(event);
	}
}

/**
 * handle attackevent
 * gets the target unit and the attackin unit
 * checks range of the attacking unit
 * and
 *
 * \param event
 */
void EventGateway::handleAttackEvent(MouseClickEvent* event) {
	if (checkEventInField(event)) {
		std::shared_ptr<Unit> unitToBeAttacked = Gamefield::instance().getField()[event->getX()][event->getY()]->getUnit();
		std::shared_ptr<Unit> unitAttacking = this->activePlayer->getUnitQueue().front();
		if (checkRange(unitAttacking->getRange(), 0, 0, event->getX(), event->getY())) {
			unitAttacking->attack(unitToBeAttacked);
			this->activePlayer->getUnitQueue().pop();
		}
	}
}

void EventGateway::handleMoveEvent(MouseClickEvent* event) {
	if (checkEventInField(event)) {
		std::shared_ptr<Unit> unitToBeMoved = this->activePlayer->getUnitQueue().front();
		std::shared_ptr<FieldTile> tileToMoveTo = Gamefield::instance().getField()[event->getX()][event->getY()];
		if (tileToMoveTo->getUnit() == NULL) {
			MoveEvent* moveEvent = new MoveEvent(unitToBeMoved, event->getX(), event->getY());
			EventBus::instance().publish(moveEvent);
			this->activePlayer->getUnitQueue().pop();
		}
	}
}

void EventGateway::handleBuyEvent(MouseClickEvent* event) {
	if ((this->activePlayer->getSupply() + 1) > ConfigReader::instance().getBalanceConf()->getMaxAmountUnits()) {
		this->activePlayer->setBuying(false);
	}
	else {
		int yButton = event->getY() - ConfigReader::instance().getMapConf()->getSizeY();
		std::shared_ptr<MenuTile> tile = Gamefield::instance().getMenuBar()[event->getX()][yButton];
		if (tile != NULL) {
			std::shared_ptr<Unit> purchasedUnit = std::make_shared<Unit>(Unit::UnitType(tile->getButton().getType()), this->activePlayer->getColor());
			Gamefield::instance().spawnUnitInSpawn(purchasedUnit, this->activePlayer->getColor());
			this->activePlayer->setBuying(false);
		}
	}

}

bool EventGateway::checkEventInField(MouseClickEvent* event) {
	if (event->getX() < 2 || event->getY() > ConfigReader::instance().getMapConf()->getSizeX() + 2) {
		return false;
	}
	if (event->getY() < 0 || event->getY() > ConfigReader::instance().getMapConf()->getSizeY()) {
		return false;
	}
	return true;
}

bool EventGateway::checkRange(int range, int originX, int originY, int targetX, int targetY) {
	return true;
}