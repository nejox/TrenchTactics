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

/**
 * Function that provides the possibilty to switch to the next unit in the queue of the active player
 *
 */
void EventGateway::handleNextUnit()
{
	const std::shared_ptr<Unit> unit = this->activePlayer->getUnitQueue().front();
	this->activePlayer->demarkActiveUnit();

	this->activePlayer->popUnit();
	this->activePlayer->queueUnit(unit);

	this->activePlayer->markActiveUnit();


}

/**
 * Function that provides the possibilty to switch to the previous unit in the queue of the active player
 *
 */
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

	/*Gamefield::instance().deselectAndUnmarkAllTiles();
	Gamefield::instance().selectAndMarkeTilesByUnit(this->activePlayer->getUnitQueue().front(), this->currentPhase, this->activePlayer->getColor());*/
}

/**
 * Handle click of endturn button
 * Publishes a new EndTurnEvent and empties the queue of the active player
 *
 */
void EventGateway::handleEndTurn() {
	this->activePlayer->demarkActiveUnit();
	this->activePlayer->emptyQueue();
	this->activePlayer->setBuying(false);
	EventBus::instance().publish(new EndTurnEvent());
}

/**
 * Handle click of next phase button
 * demarks active unit and empties the queue to skip to the next turn
 *
 */
void EventGateway::handleNextPhase() {
	if (this->currentPhase == GAMEPHASES::BUY) {
		this->activePlayer->setBuying(false);
	}
	else {
		this->activePlayer->demarkActiveUnit();
		// empty the queue of the active player to get to the next phase
		this->activePlayer->emptyQueue();
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
	// check wether a skip phase button was clicked, 
	// TODO: other buttons
	if (checkButtonClicked(event)) {
		int type = MenuBar::instance().getMenuTileFromXY(event->getX(), event->getY())->getButton()->getType();

		if (type == 31) {

			handleNextPhase();
		}
		// end turn
		else if (type == 30) {
			handleEndTurn();
		}
		//previous Unit
		else if (type == 10) {
			handlePrevUnit();
		}
		//next unit
		else if (type == 11) {
			handleNextUnit();
		}
		return;
	}
	if (checkEventInField(event)) {

		if (Gamefield::instance().getFieldTileFromXY(event->getX(), event->getY())->getUnit()) {
			std::shared_ptr<Unit>  unitToBeAttacked = Gamefield::instance().getFieldTileFromXY(event->getX(), event->getY())->getUnit();
			std::shared_ptr<Unit> unitAttacking = this->activePlayer->getUnitQueue().front();

			if (checkRange(Gamefield::instance().findTileByUnit(unitToBeAttacked)) && unitAttacking->getCurrentAP() >= unitAttacking->getApCostAttack()) {
				unitAttacking->attack(unitToBeAttacked);
				this->activePlayer->popUnit();

				this->activePlayer->markActiveUnit();

			}
		}
	}
	//HQ attacked
	else if (checkEventOnHQ(event)) {
		//wip
		std::shared_ptr<Unit> unitAttacking = this->activePlayer->getUnitQueue().front();
		std::shared_ptr<PlayerTile> tile;
		if (unitAttacking->getColorRed()) {
			tile = Gamefield::instance().getHqTilePlayerBlue();
		}
		else {
			tile = Gamefield::instance().getHqTilePlayerRed();
		}
		if (checkRange(tile) && unitAttacking->getCurrentAP() >= unitAttacking->getApCostAttack()) {
			std::shared_ptr < Headquarter> hq = tile->getHeadquarter();
			unitAttacking->attack(hq);

			this->activePlayer->popUnit();
			this->activePlayer->markActiveUnit();
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

		int type = MenuBar::instance().getMenuTileFromXY(event->getX(), event->getY())->getButton()->getType();

		if (type == 31) {
			handleNextPhase();
		}
		// end turn
		else if (type == 30) {
			handleEndTurn();
		}
		//previous Unit Button
		else if (type == 10) {
			handlePrevUnit();
		}
		//next unit Button
		else if (type == 11) {
			handleNextUnit();
		}
		return;
	}
	if (checkEventInField(event)) {
		// get unit that will be moved from the front of the queue
		std::shared_ptr<Unit> unitToBeMoved = this->activePlayer->getUnitQueue().front();
		// get target field based on the event
		std::shared_ptr<FieldTile> tileToMoveTo = Gamefield::instance().getFieldTileFromXY(event->getX(), event->getY());

		if (!tileToMoveTo->getUnit() && checkRange(tileToMoveTo)) {
			//compute the cost of the movement
			int cost = computeApCost(Gamefield::instance().findTileByUnit(unitToBeMoved), tileToMoveTo);
			//subtract the cost from the unit ap
			unitToBeMoved->reduceAp(cost);

			//if copse is on tile to move to, add reward
			if (tileToMoveTo->hasCopse())
			{
				tileToMoveTo->removeCorpse();
				this->activePlayer->updateMoney(10); //TO DO: Reward from config
				MenuBar::instance().refreshMenuBar(this->activePlayer);
			}

			// find current tile of the unit to overwrite the sprite and remove the unit
			Gamefield::instance().findTileByUnit(unitToBeMoved).get()->removeUnit();

			// attach unit to new tile 
			tileToMoveTo.get()->setUnit(unitToBeMoved);
			// delete the moved unit from the queue
			this->activePlayer->demarkActiveUnit();
			this->activePlayer->popUnit();
			unitToBeMoved->setState(STATES::UNITSTATE::STANDING_NEUTRAL);
			this->activePlayer->markActiveUnit();
		}
	}
	/*Gamefield::instance().deselectAndUnmarkAllTiles();
	if(!this->activePlayer->getUnitQueue().empty())
		Gamefield::instance().selectAndMarkeTilesByUnit(this->activePlayer->getUnitQueue().front(), GAMEPHASES::MOVE, this->activePlayer->getColor());*/
}

/**
 * Function that handles buy events
 * Gets the unit id from the clicked button and creates a unit if possible and spawns it
 * then moves player in to the next phase
 * \param event provided event from eventbus, in this case mouseclickevent
 */
void EventGateway::handleBuyEvent(MouseClickEvent* event) {
	// check wether a player is even allowed to buy a unit based on their supply and money  TO DO: vielleicht woanders hin die condition, wenn sie hier steht muss man erst klicken dass die buyphase geskippt wird
	if ((this->activePlayer->getUnitArray().size() + 1) > ConfigReader::instance().getBalanceConf()->getMaxAmountUnits() ||
		(
			this->activePlayer->getMoney() < ConfigReader::instance().getUnitConf(0)->getCost() &&
			this->activePlayer->getMoney() < ConfigReader::instance().getUnitConf(1)->getCost() &&
			this->activePlayer->getMoney() < ConfigReader::instance().getUnitConf(2)->getCost()
			))
	{
		this->activePlayer->setBuying(false);
		Logger::instance().log(LOGLEVEL::INFO, "not enough supply or money to purchase unit");

	}
	else
	{

		// make sure a button was clicked
		if (!checkButtonClicked(event)) {
			Logger::instance().log(LOGLEVEL::INFO, "didnt click a button");
			return;
		}

		// get the button type to decide what to do
		int type = MenuBar::instance().getMenuTileFromXY(event->getX(), event->getY())->getButton()->getType();

		//spawn unit if type is a unit type
		if (type >= 0 && type <= 2) {

			//check if player can afford the unit
			if (activePlayer->getMoney() >= ConfigReader::instance().getUnitConf(type)->getCost()) {

				//render over button
				MenuBar::instance().getMenuTileFromXY(event->getX(), event->getY())->removeButtonDisplay();
				//toggle buttonstate
				MenuBar::instance().getMenuTileFromXY(event->getX(), event->getY())->getButton()->push();
				//render button 
				MenuBar::instance().getMenuTileFromXY(event->getX(), event->getY())->getButton()->update();

			}
		}

		//add an additional unit button
		if (type == 23)
		{
			if (activePlayer->getMoney() >= 5) {
				this->activePlayer->updateMoney(-5);
				MenuBar::instance().getMenuTileFromXY(event->getX(), event->getY())->removeButtonDisplay();
				MenuBar::instance().getMenuTileFromXY(event->getX(), event->getY())->getButton()->setType((Button::BUTTONTYPE)(std::rand() % 3));
				MenuBar::instance().getMenuTileFromXY(event->getX(), event->getY())->getButton()->update();
				MenuBar::instance().refreshMenuBar(this->activePlayer);
			}
		}

		//confirm purchase of unit
		else if (type == 20)
		{

			int cost = 0;
			//iterate over all unit buttons, summarize all pressed buttons cost
			for (int i = 7; i <= 11; i = i++) {
				//if it isnt empty
				if (MenuBar::instance().getMenuBar().get()->at(i).at(1).get()->getButton() != nullptr) {
					//if it is pressed
					if (MenuBar::instance().getMenuBar().get()->at(i).at(1).get()->getButton()->getState() == true)
					{
						cost = cost + (ConfigReader::instance().getUnitConf(MenuBar::instance().getMenuBar().get()->at(i).at(1).get()->getButton()->getType())->getCost());
					}
				}
			}

			//check if player can afford all his purchases
			if (cost <= activePlayer->getMoney()) {
				//iterate over all unitbuttons
				for (int i = 7; i <= 11; i = i++) {
					//if it isnt empty
					if (MenuBar::instance().getMenuBar().get()->at(i).at(1).get()->getButton() != nullptr) {
						//if it is pressed
						if (MenuBar::instance().getMenuBar().get()->at(i).at(1).get()->getButton()->getState() == true)
						{
							// create new unit that will be purchased
							purchasedUnit = std::make_shared<Unit>(static_cast<TYPES::UnitType>(MenuBar::instance().getMenuBar().get()->at(i).at(1).get()->getButton()->getType()), this->activePlayer->getColor());
							// spawn unit
							Gamefield::instance().spawnUnitInSpawn(purchasedUnit, this->activePlayer->getColor());
							// add unit to vector of the player
							this->activePlayer->addUnit(purchasedUnit);
							//update players money
							this->activePlayer->updateMoney(-(purchasedUnit->getCost()));
						}
					}
				}
				//MenuBar::instance().updateMenuBar(GAMEPHASES::BUY, activePlayer); überflüssig?
				this->activePlayer->setBuying(false);
			}

			//if player cant afford, deactivate all Buttons
			else
			{
				MenuBar::instance().resetAllButtonsToNeutral();
			}

		}

		//Reroll Units
		else if (type == 22)
		{
			this->activePlayer->updateMoney(-10);
			MenuBar::instance().updateMenuBar(GAMEPHASES::BUY, this->activePlayer);
		}

		//cancel purchase of unit
		else if (type == 21)
		{
			
				MenuBar::instance().resetAllButtonsToNeutral();
			
		}
		// react to next phase
		else if (type == 31) {
			this->activePlayer->setBuying(false);

		}
		// end turn
		else if (type == 30) {
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
	if (!MenuBar::instance().getMenuTileFromXY(event->getX(), event->getY()).get() || !MenuBar::instance().getMenuTileFromXY(event->getX(), event->getY())->getButton().get()) {
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
	if ((event->getX() <= (fieldX + 2 * 64)) || (event->getX() >= fieldX + 4 * 64)) {
		return false;
	}
	int fieldY = (ConfigReader::instance().getMapConf()->getSizeY() - 2) * 64;
	if (event->getY() <= (fieldY / 2) || event->getY() >= (fieldY / 2) + 2 * 64) {
		return false;
	}

	return true;
}

/**
 * checks wether unit is in range
 *
 * \param range range of the attacking unit
 * \param originX attacking unit x position
 * \param originY attacking unit y position
 * \param targetX unit that will be attacked unit x position
 * \param targetY unit that will be attacked unit y position
 * \return
 */

bool EventGateway::checkRange(shared_ptr<Tile> targetTile) {
	return targetTile->getMarked();
}

/**
* computes the amount of tiles a unit has to pass to get from start to end, order of end and start does not matter
* \param start from which tile 
* \param end to which tile
* \return integer value of the added differences of the X and Y positions of start and end
*/
int EventGateway::computeApCost(shared_ptr<Tile> start, shared_ptr<Tile> end)
{
	return abs((end->getPosX() - start->getPosX()) / 64) + abs((end->getPosY() - start->getPosY()) / 64);
}