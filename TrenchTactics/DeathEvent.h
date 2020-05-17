
#include "Event.h"
#include "Unit.h"

/**
 * DeathEvent that gets triggerd when a unit dies
 * Has the dying unit as a parameter
 */
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