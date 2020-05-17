
#pragma once
#include "Event.h"

/**
 * Deathevent class which gets raised when one player dies, meaning the life of one headquarter is below or equal to zero.
 */
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