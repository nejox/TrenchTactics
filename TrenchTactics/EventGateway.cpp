#include "EventGateway.h"
#include "EndTurnEvent.h"


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
	if (this->currentPhase == GAMEPHASES::BUY) {
		this->handleBuyEvent(event);
	}
	else if (this->currentPhase == GAMEPHASES::MOVE) {
		this->handleMoveEvent(event);
	}
	else if (this->currentPhase == GAMEPHASES::ATTACK) {
		this->handleAttackEvent(event);
	}
}

void EventGateway::handleNextUnit()
{
	const std::shared_ptr<Unit> unit = this->activePlayer->getUnitQueue().front();
	this->activePlayer->demarkActiveUnit();

	this->activePlayer->popUnit();
	this->activePlayer->queueUnit(unit);

	this->activePlayer->markActiveUnit();
}

void EventGateway::handlePrevUnit()
{
	const std::shared_ptr<Unit> unit = this->activePlayer->getUnitQueue().back();
	this->activePlayer->demarkActiveUnit();

	std::shared_ptr<Unit> tmp = nullptr;
	tmp = this->activePlayer->getUnitQueue().front();
	while (tmp != unit) {
		this->activePlayer->popUnit();
		this->activePlayer->queueUnit(tmp);
		tmp = this->activePlayer->getUnitQueue().front();
	}

	this->activePlayer->markActiveUnit();
}

void EventGateway::handleEndTurn() {
	this->activePlayer->demarkActiveUnit();
	this->activePlayer->emptyQueue();
	this->activePlayer->setBuying(false);
	EventBus::instance().publish(new EndTurnEvent());
}

void EventGateway::handleNextPhase() {
	this->activePlayer->demarkActiveUnit();
	// empty the queue of the active player to get to the next phase
	this->activePlayer->emptyQueue();
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
	// check wether a skip phase button was clicked, 
	// TODO: other buttons
	if (checkButtonClicked(event)) {
		//render click
		Gamefield::instance().getMenuTileFromXY(event->getX(), event->getY())->getButton()->update(STATES::BUTTONSTATE::PRESSED);
		int type = Gamefield::instance().getMenuTileFromXY(event->getX(), event->getY())->getButton()->getType();
		if (type == 50) {

			handleNextPhase();
		}
		// end turn
		else if (type == 31) {
			handleEndTurn();
		}
		//previous Unit
		else if (type == 10) {
			handlePrevUnit();
		}
		//next unit
		else if (type == 20) {
			handleNextUnit();
		}
		return;
	}
	if (checkEventInField(event)) {

		if (Gamefield::instance().getFieldTileFromXY(event->getX(), event->getY())->getUnit()) {
			std::shared_ptr<Unit>  unitToBeAttacked = Gamefield::instance().getFieldTileFromXY(event->getX(), event->getY())->getUnit();
			std::shared_ptr<Unit> unitAttacking = this->activePlayer->getUnitQueue().front();

			if (unitToBeAttacked->getColorRed() != unitAttacking->getColorRed()) {

				if (checkRange(unitAttacking->getRange(), unitAttacking->getSprite()->getX(), unitAttacking->getSprite()->getY(), event->getX(), event->getY())) {
					unitAttacking->attack(unitToBeAttacked);
					this->activePlayer->popUnit();
					this->activePlayer->markActiveUnit();
				}
			}
		}

	}
	//HQ attacked
	else if (checkEventOnHQ(event)) {
		//wip
		if (Gamefield::instance().getFieldTileFromXY(event->getX(), event->getY())->getUnit()) {
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
	// see above
	if (checkButtonClicked(event)) {

		int type = Gamefield::instance().getMenuTileFromXY(event->getX(), event->getY())->getButton()->getType();
		if (type == 50) {
			handleNextPhase();
		}
		// end turn
		else if (type == 31) {
			handleEndTurn();
		}
		//previous Unit Button
		else if (type == 10) {
			handlePrevUnit();
		}
		//next unit Button
		else if (type == 20) {
			handleNextUnit();
		}
		return;
	}
	if (checkEventInField(event)) {
		// get unit that will be moved from the front of the queue
		std::shared_ptr<Unit> unitToBeMoved = this->activePlayer->getUnitQueue().front();
		// get target field based on the event
		std::shared_ptr<FieldTile> tileToMoveTo = Gamefield::instance().getFieldTileFromXY(event->getX(), event->getY());
		if (!tileToMoveTo->getUnit()) {
			// find current tile of the unit to overwrite the sprite and remove the unit
			Gamefield::instance().findeTileByUnit(unitToBeMoved).get()->removeUnit();

			// attach unit to new tile 
			tileToMoveTo.get()->setUnit(unitToBeMoved);
			// delete the moved unit from the queue
			this->activePlayer->popUnit();
			unitToBeMoved->setState(STATES::UNITSTATE::STANDING_NEUTRAL);
			this->activePlayer->markActiveUnit();
		}
	}
}

/**
 * Function that handles buy events
 * Gets the unit id from the clicked button and creates a unit if possible and spawns it
 * then moves player in to the next phase
 * \param event provided event from eventbus, in this case mouseclickevent
 */
void EventGateway::handleBuyEvent(MouseClickEvent* event) {
	// check wether a player is even allowed to buy a unit based on their supply
	if ((this->activePlayer->getSupply() + 1) > ConfigReader::instance().getBalanceConf()->getMaxAmountUnits()) {
		this->activePlayer->setBuying(false);
		Logger::instance().log(LOGLEVEL::INFO, "not enough supply to purchase unit");
	}
	else {
		// make sure a button was clicked
		if (!checkButtonClicked(event)) {
			Logger::instance().log(LOGLEVEL::INFO, "didnt click a button");
			return;
		}
		Gamefield::instance().getMenuTileFromXY(event->getX(), event->getY())->getButton()->update(STATES::BUTTONSTATE::PRESSED);
		// get the button type to decide what to do
		int type = Gamefield::instance().getMenuTileFromXY(event->getX(), event->getY())->getButton()->getType();
		//spawn unit if type is a unit type
		if (type >= 0 && type <= 2) {
			// create new unit that will be spawned
			std::shared_ptr<Unit> purchasedUnit = std::make_shared<Unit>(static_cast<TYPES::UnitType>(type), this->activePlayer->getColor());
			// spawn unit
			Gamefield::instance().spawnUnitInSpawn(purchasedUnit, this->activePlayer->getColor());
			// add unit to vector of the player
			this->activePlayer->addUnit(purchasedUnit);
			// remove player from buying phase
			this->activePlayer->setBuying(false);
		}
		// react to next phase
		else if (type == 50) {
			this->activePlayer->setBuying(false);
		}
		// end turn
		else if (type == 31) {
			handleEndTurn();
		}
	}


}

/**
 * Check wether a button was clicked by checking if a menutile was clicked and if menutile even has a button is returned from gamefield
 *
 * \param event
 * \return
 */
bool EventGateway::checkButtonClicked(MouseClickEvent* event) {
	if (!Gamefield::instance().getMenuTileFromXY(event->getX(), event->getY()).get() || !Gamefield::instance().getMenuTileFromXY(event->getX(), event->getY())->getButton().get()) {
		return false;
	}
	else {
		return true;
	}
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
 * Check wether a mouseclickevent is on the HQ or not
 *
 * \param event mouseclickevent to be checked
 * \return event in field or not
 */
bool EventGateway::checkEventOnHQ(MouseClickEvent* event) {
	int fieldX = ConfigReader::instance().getMapConf()->getSizeX() * 64;
	if ((event->getX() <= (fieldX + 2 * 64)) || (event->getX() >= fieldX+4*64)) {
		return false;
	}
	int fieldY = (ConfigReader::instance().getMapConf()->getSizeY() - 2) * 64;
	if (event->getY() <= (fieldY/2) || event->getY() >= (fieldY/2)+2 * 64) {
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

	int x = targetX - originX;
	int y = targetY - originY;
	x = x / 64;
	y = y / 64;
	int result = x + y;

	if (range >= result) {
		return true;
	}
	else {
		return false;
	}
}