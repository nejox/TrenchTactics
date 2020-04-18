#pragma once
#include "Event.h"
#include "UnitBase.h"

/// <summary>
/// MoveEvent class for implementing the specialised event
/// </summary>
class AttackEvent :
	public Event
{
public:
	AttackEvent(UnitBase* unitToBeAttacked, UnitBase* attackingUnit) {
		this->unitToBeAttacked = unitToBeAttacked;
		this->attackingUnit = attackingUnit;
	}
	UnitBase* getUnitToBeAttacked() {
		return this->unitToBeAttacked;
	}
	UnitBase* getAttackingUnit() {
		return this->attackingUnit;
	}

private:
	UnitBase* unitToBeAttacked;
	UnitBase* attackingUnit;
};
