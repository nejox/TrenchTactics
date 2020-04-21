#pragma once
#include "Event.h"
#include "UnitBase.h"

/// <summary>
/// MoveEvent class for implementing the specialised event
/// </summary>
class MoveEvent :
	public Event
{
public:
	MoveEvent(UnitBase* unitToBeMoved, int x, int y) {
		this->unitToBeMoved = unitToBeMoved;
		this->x = x;
		this->y = y;
	}
	UnitBase* getUnit() {
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
	UnitBase* unitToBeMoved;
};

