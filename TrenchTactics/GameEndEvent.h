
#pragma once
#include "Event.h"


/// <summary>
/// DeathEvent class for implementing the specialised event
/// </summary>
class GameEndEvent :
	public Event
{
public:
	GameEndEvent(bool colorRed) {
		this->Winner = colorRed;
	}

	bool getWinner() {
		return this->Winner;
	}

private:
	bool Winner;
};