#include "MouseClickEvent.h"

/// <summary>
/// specialised constructor to create the MouseClickEvent object
/// </summary>
/// <param name="x">the x-coordinate of the mouse click</param>
/// <param name="y">the y-coordinate of the mouse click</param>
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
