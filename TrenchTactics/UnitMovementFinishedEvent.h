#pragma once
#include "Event.h"

/**
 * UnitMovementFinishedEvent class that provides a specialized event that gets raised when a Unit reached its destination after moving.
 */
class UnitMovementFinishedEvent :
    public Event
{
public:
    UnitMovementFinishedEvent(std::shared_ptr<Unit> movingUnit) {
    this->unit = movingUnit;

}
    std::shared_ptr<Unit> getMovingUnit() {
        return this->unit;
    }
private:
    std::shared_ptr<Unit> unit;
};

