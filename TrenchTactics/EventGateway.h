#pragma once
#include "EventBus.h"
#include "MouseClickEvent.h"
#include "Unit.h"
#include "MoveEvent.h"
#include "ConfigReader.h"
#include "IEventManager.h"
#include "Gamephases.h"
#include "Player.h"
#include "FieldTile.h"
#include "MenuTile.h"
#include "Gamefield.h"
#include "Logger.hpp"


/**
 * EventGateway class which does most of the heavy lifting with event forwarding and controlling
 * Takes all events, makes loigcal checks and forwards the action to the specific handler
 */
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

	void setActivePlayer(std::shared_ptr<Player> player) {
		this->activePlayer = player;
	}

private:
	EventGateway();
	~EventGateway();
	GAMEPHASES::GAMEPHASE currentPhase;
	std::shared_ptr<Player> activePlayer;

	void handleNextUnit();
	void handlePrevUnit();
	void handleEndTurn();
	void handleNextPhase();

	void handleAttackEvent(MouseClickEvent* event);
	void handleMoveEvent(MouseClickEvent* event);
	void handleBuyEvent(MouseClickEvent* event);
	bool checkButtonClicked(MouseClickEvent* event);
	bool checkEventInField(MouseClickEvent* event);

	bool checkRange(shared_ptr<Tile> targetTile);

	bool checkEventOnHQ(MouseClickEvent* event);

	std::shared_ptr<Unit> purchasedUnit = nullptr;
};