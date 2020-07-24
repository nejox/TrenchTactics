#pragma once
#include "Event.h"

/**
 * MouseClickEvent class that gets raised on mouse click containing the position of the mouse click in pixel value.
 */
class MouseClickEvent :
	public Event
{
public:
	MouseClickEvent(int x, int y);
	int getX();
	int getY();

private:
	int x;
	int y;
};

