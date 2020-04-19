#pragma once
#include "GameLoop.h"
#include "EventBus.h"
#include "MouseClickEvent.h"
#include "Unit.h"
#include "MoveEvent.h"
#include "BuyEvent.h"
#include "ConfigReader.h"
#include "IEventManager.h"

class EventGateway
{
public:
	EventGateway(const EventGateway&) = delete;
	EventGateway& operator=(const EventGateway&) = delete;
	EventGateway(EventGateway&&) = delete;
	EventGateway& operator=(EventGateway&&) = delete;

	static auto& instance() {
		static EventGateway eventGateway;
		return eventGateway;
	}

	void init();
	void handleEvent(MouseClickEvent* event);

	void setCurrentPhase(GAMEPHASES::GAMEPHASE phase) {
		this->currentPhase = phase;
	}

	void setActivePlayer(Player* player) {
		this->activePlayer = player;
	}

private:
	EventGateway();
	GAMEPHASES::GAMEPHASE currentPhase;
	Player* activePlayer;

	void handleAttackEvent(MouseClickEvent* event);
	void handleMoveEvent(MouseClickEvent* event);
	void handleBuyEvent(MouseClickEvent* event);
	bool checkEventInField(MouseClickEvent* event);
	bool checkRange(int range, int originX, int originY, int targetX, int targetY);

};
