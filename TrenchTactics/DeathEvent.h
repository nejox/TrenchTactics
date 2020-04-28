
#include "Event.h"
#include "Unit.h"

/// <summary>
/// DeathEvent class for implementing the specialised event
/// </summary>
class DeathEvent :
	public Event
{
public:
	DeathEvent(std::shared_ptr<Unit> DeathUnit) {
		this->DeathUnit = DeathUnit;
		
	}
	std::shared_ptr<Unit> getKilledUnit() {
		return this->DeathUnit;
	}

private:
	std::shared_ptr<Unit> DeathUnit;
};