#pragma once
#include "Event.h"
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

