#include "MouseClickEvent.h"

MouseClickEvent::MouseClickEvent(int x, int y)
{
	this->x = x;
	this->y = y;
}

int MouseClickEvent::getX()
{
	return this->x;
}

int MouseClickEvent::getY()
{
	return this->y;
}
