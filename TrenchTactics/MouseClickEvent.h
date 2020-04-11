#pragma once
#include "Event.h"

/// <summary>
/// MouseClickEvent class for implementing the specialised event
/// </summary>
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

