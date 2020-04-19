#pragma once
#include "Event.h"

/// <summary>
/// MouseClickEvent class for implementing the specialised event
/// </summary>
class BuyEvent :
	public Event
{
public:
	BuyEvent(Unit* unit) {
		this->unit = unit;
	}
	Unit* getPurchasedUnit() {
		return this->unit;
	}

private:
	Unit* unit;
};


