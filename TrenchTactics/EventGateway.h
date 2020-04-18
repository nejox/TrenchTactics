#pragma once
#include "GameLoop.h"
#include "EventBus.h"
#include "MouseClickEvent.h"
#include "UnitBase.h"
#include "MoveEvent.h"
#include "AttackEvent.h"
#include "BuyEvent.h"

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

	void setCurrentPhase(GAMPHASES::GAMEPHASE phase) {
		this->currentPhase = phase;
	}
	void setGamefield(Gamefield gamefield) {
		this->gamefield = gamefield;
	}
	void setActivePlayer(Player* player) {
		this->activePlayer = player;
	}

private:
	EventGateway();
	Gamefield gamefield;
	GAMPHASES::GAMEPHASE currentPhase;
	Player* activePlayer;

	void handleAttackEvent(MouseClickEvent* event);
	void handleMoveEvent(MouseClickEvent* event);
	void handleBuyEvent(MouseClickEvent* event);

};
