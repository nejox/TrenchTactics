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
		std::shared_ptr<Unit>  unitToBeAttacked = Gamefield::instance().getPlayingfield().get()->at(event->getX()).at(event->getY()).get()->getUnit();
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
		std::shared_ptr<FieldTile> tileToMoveTo = Gamefield::instance().getFieldTileFromXY(event->getX(), event->getY());

		Gamefield::instance().findeTileByUnit(unitToBeMoved).get()->removeUnit();

		tileToMoveTo.get()->setUnit(unitToBeMoved);
		this->activePlayer->getUnitQueue().pop();
		//unitToBeMoved.get()->update(STATES::RUNNING);

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
		Logger::instance().log(LOGLEVEL::INFO, "not enough supply to purchase unit");
	}
	else {
		if (!Gamefield::instance().getMenuTileFromXY(event->getX(), event->getY()).get() || !Gamefield::instance().getMenuTileFromXY(event->getX(), event->getY()).get()->getButton().get()) {
			Logger::instance().log(LOGLEVEL::INFO, "didnt click a button");
			return;
		}
		int unitType = Gamefield::instance().getMenuTileFromXY(event->getX(), event->getY()).get()->getButton().get()->getType();
		if (unitType != -1) {
			std::shared_ptr<Unit> purchasedUnit = std::make_shared<Unit>(static_cast<TYPES::UnitType>(unitType), false);
			Gamefield::instance().spawnUnitInSpawn(purchasedUnit, this->activePlayer.get()->getColor());
			this->activePlayer.get()->addUnit(purchasedUnit);
			this->activePlayer->setBuying(false);
			this->currentPhase = GAMEPHASES::MOVE;
		}
	}
	Gamefield::instance().deleteButtons(GAMEPHASES::BUY);

}

/**
 * Check wether a mouseclickevent is in the field or not
 *
 * \param event mouseclickevent to be checked
 * \return event in field or not
 */
bool EventGateway::checkEventInField(MouseClickEvent* event) {
	if (event->getX() <= (2 * 64) || event->getX() >= (ConfigReader::instance().getMapConf()->getSizeX() * 64 + 2 * 64)) {
		return false;
	}
	if (event->getY() <= 0 || event->getY() >= ConfigReader::instance().getMapConf()->getSizeY() * 64) {
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