#pragma once
#include "Event.h"

/// <summary>
/// MouseClickEvent class for implementing the specialised event
/// </summary>
class BuyEvent :
	public Event
{
public:
	BuyEvent(UnitBase* unit) {
		this->unit = unit;
	}
	UnitBase* getPurchasedUnit() {
		return this->unit;
	}

private:
	UnitBase* unit;
};


