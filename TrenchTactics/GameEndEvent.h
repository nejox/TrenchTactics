
#pragma once
#include "Event.h"
#include "Player.h"
#include "EventGateWay.h"

/// <summary>
/// DeathEvent class for implementing the specialised event
/// </summary>
class GameEndEvent :
	public Event
{
public:
	GameEndEvent() {
		this->Winner = EventGateWay::instance().getActivePlayer();
	}

	Player* getWinner() {
		return this->Winner;
	}

private:
	Player* Winner;
};