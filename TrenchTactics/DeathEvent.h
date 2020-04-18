
#pragma once
#include "Event.h"
#include "Unit.h"

/// <summary>
/// DeathEvent class for implementing the specialised event
/// </summary>
class DeathEvent :
	public Event
{
public:
	DeathEvent(Unit* DeathUnit) {
		this->DeathUnit = DeathUnit;
		
	}
	Unit* getDeathUnit() {
		return this->DeathUnit;
	}

private:
	Unit* DeathUnit;
};