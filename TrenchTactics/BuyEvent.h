#pragma once
#include "Event.h"

/// <summary>
/// MouseClickEvent class for implementing the specialised event
/// </summary>
class BuyEvent :
	public Event
{
public:
	BuyEvent(int unitType) {
		this->unitType = unitType;
	}
	int getPurchasedUnit() {
		return this->unitType;
	}

private:
	int unitType;
};


