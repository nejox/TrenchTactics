#include "MouseClickEvent.h"

/**
 * specialised constructor to create the MouseClickEvent object.
 *
 * \param x the x-coordinate of the mouse click
 * \param y the y-coordinate of the mouse click
 */
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
