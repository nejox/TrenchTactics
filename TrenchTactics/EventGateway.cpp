#include "EventGateway.h"



EventGateway::EventGateway() {
}

EventGateway::~EventGateway() {
}

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
 * and executes the attack with the specified units
 * afterwards pops the attacking unit from the queue of the active player
 *
 * \param event provided event from eventbus, in this case mouseclickevent
 */
void EventGateway::handleAttackEvent(MouseClickEvent* event) {
	if (checkEventInField(event)) {
		std::shared_ptr<Unit>  unitToBeAttacked = Gamefield::instance().getField().get()->at(event->getX()).at(event->getY()).get()->getUnit();
		std::shared_ptr<Unit> unitAttacking = this->activePlayer->getUnitQueue().front();
		if (checkRange(unitAttacking->getRange(), 0, 0, event->getX(), event->getY())) {
			unitAttacking->attack(unitToBeAttacked);
			this->activePlayer->getUnitQueue().pop();
		}
	}
}

/**
 * Function that handles move events
 * Takes mouse event checks if action is ok within the units rules
 * creates a moveevent publishes it and pops the unit from the queue
 *
 * \param event provided event from eventbus, in this case mouseclickevent
 */
void EventGateway::handleMoveEvent(MouseClickEvent* event) {
	if (checkEventInField(event)) {
		std::shared_ptr<Unit> unitToBeMoved = this->activePlayer->getUnitQueue().front();
		std::shared_ptr<FieldTile> tileToMoveTo = Gamefield::instance().getField().get()->at(event->getX() / 64).at(event->getY() / 64);

		tileToMoveTo.get()->setUnit(unitToBeMoved);
		unitToBeMoved.get()->update();
		//if (tileToMoveTo->getUnit() == NULL) {
		//MoveEvent* moveEvent = new MoveEvent(unitToBeMoved, event->getX(), event->getY());
		//EventBus::instance().publish(moveEvent);
		//this->activePlayer->getUnitQueue().pop();
		//}
	}
}

/**
 * Function that handles buy events
 * Gets the unit id from the clicked button and creates a unit if possible and spawns it
 * then moves player in to the next phase
 * \param event provided event from eventbus, in this case mouseclickevent
 */
void EventGateway::handleBuyEvent(MouseClickEvent* event) {
	if ((this->activePlayer->getSupply() + 1) > ConfigReader::instance().getBalanceConf()->getMaxAmountUnits()) {
		this->activePlayer->setBuying(false);
	}
	else {
		int yButton = event->getY() - ConfigReader::instance().getMapConf()->getSizeY();

		//std::shared_ptr<MenuTile> tile = Gamefield::instance().getMenuBar().get()->at(event->getX()).at(yButton);
		//if (tile != NULL) {
		//	std::shared_ptr<Unit> purchasedUnit = std::make_shared<Unit>(Unit::UnitType(tile->getButton().getType()), this->activePlayer->getColor());
		//	Gamefield::instance().spawnUnitInSpawn(purchasedUnit, this->activePlayer->getColor());
		//	this->activePlayer->setBuying(false);
		//}

		std::shared_ptr<Unit> purchasedUnit = std::make_shared<Unit>(Unit::GUNNER, false);
		//purchasedUnit->update();
		Gamefield::instance().spawnUnitInSpawn(purchasedUnit, false);

	}

}

/**
 * Check wether a mouseclickevent is in the field or not
 *
 * \param event mouseclickevent to be checked
 * \return event in field or not
 */
bool EventGateway::checkEventInField(MouseClickEvent* event) {
	if (event->getX() < 2 || event->getY() > ConfigReader::instance().getMapConf()->getSizeX() + 2) {
		return false;
	}
	if (event->getY() < 0 || event->getY() > ConfigReader::instance().getMapConf()->getSizeY()) {
		return false;
	}
	return true;
}

/**
 * TODO: implement
 *
 * checks wether unit is in range
 *
 * \param range range of the attacking unit
 * \param originX attacking unit x position
 * \param originY attacking unit y position
 * \param targetX unit that will be attacked unit x position
 * \param targetY unit that will be attacked unit y position
 * \return
 */
bool EventGateway::checkRange(int range, int originX, int originY, int targetX, int targetY) {
	return true;
}