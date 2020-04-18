#include "EventGateway.h"


EventGateway::EventGateway() {

}

void EventGateway::init() {
	//void (handleEventPointer)(MouseClickEvent);
	//handleEventPointer = &this->handleEvent;
	//EventBus::instance().subscribe<EventGateway, MouseClickEvent>(EventGateway::instance(), handleEventPointer);
}
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


void EventGateway::handleAttackEvent(MouseClickEvent* event) {
	UnitBase* unitToBeAttacked = NULL;
	//Unit* unitToBeAttacked = gamefield.getField().getTile(event->getX(), event->getY()).getUnit();
	//if (checkTileInField() && unitToBeAttacked != NULL) {
		// publish attack command to tile
	AttackEvent* attackEvent = new AttackEvent(unitToBeAttacked, this->activePlayer->getUnitQueue().front());
	//EventBus::instance().publish();
	this->activePlayer->getUnitQueue().pop();
	//}
}

void EventGateway::handleMoveEvent(MouseClickEvent* event) {

	Tile* tileToMoveTo = NULL;
	UnitBase* unitToBeMoved = this->activePlayer->getUnitQueue().front();
	//Tile * tileToMoveTo = gamefield.getField().getTile(event->getX(), event->getY());
	//if (checkTileInField() && tileToMoveTo->getUnit() == NULL && tileToMoveTo->getMarked()) {
		// publish event to move a unit (give it a pointer reference) from a tile to another tile
	//}
	MoveEvent* moveEvent = new MoveEvent(unitToBeMoved, event->getX(), event->getY());
	//EventBus::instance().publish();
	this->activePlayer->getUnitQueue().pop();
}

void EventGateway::handleBuyEvent(MouseClickEvent* event) {
	if (this->activePlayer->getColor()) {
		//	Tile* spawnTile = this->gamefield.getSpawnA();
	}
	else {
		//	Tile* spawnTile = this->gamefield.getSpawnB();
	}
	// checkEventHitButton(event);
	//int unitId = getUnitIdFromButton(event->getX(), event->getY());
	//UnitBase* purchasedUnit = new UnitBase();
	//BuyEvent* buyEvent = new BuyEvent(purchasedUnit);
	//EventBus::instance().publish(spawnTile, buyEvent);
	//this->activePlayer->addUnit(unit);
	this->activePlayer->setBuying(false);
}