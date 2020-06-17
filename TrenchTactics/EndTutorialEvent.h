#pragma once
#include "Event.h"

/**
 * StartTutorialEvent class that provides a specialized event that gets raised when start tutorial in the menu is pressed.
 */
class EndTutorialEvent : public Event
{

public:
    EndTutorialEvent(int sX, int eX, int sY, int eY);
    int getStartX() {
        return startX;
    }
    int getEndX() {
        return endX;
    }
    int getStartY() {
        return startY;
    }
    int getEndY() {
        return endY;
    }
private:
    int startX;
    int endX;
    int startY;
    int endY;
};
