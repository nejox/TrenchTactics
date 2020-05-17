#pragma once
#include "Event.h"
#include "Unit.h"

/**
 * MoveEvent class that provides a specialized event that gets raised when a unit gets moved.
 * Contains the unit that will be moved as well as its destination
 */
class MoveEvent :
	public Event
{
public:
	MoveEvent(std::shared_ptr<Unit> unitToBeMoved, int x, int y) {
		this->unitToBeMoved = unitToBeMoved;
		this->x = x;
		this->y = y;
	}
	std::shared_ptr<Unit> getUnit() {
		return this->unitToBeMoved;
	}
	int getX() {
		return this->x;
	}
	int getY() {
		return this->y;
	}

private:
	int x;
	int y;
	std::shared_ptr<Unit> unitToBeMoved;
};

