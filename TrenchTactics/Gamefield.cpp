#include "Gamefield.h"


void asignEventToTile(MouseClickEvent event) {
	if ((12 <= event.getY <= 14) && (0 <= event.getX <= 21))
		Gamefield::getMenuBar[event.getX][event.getY - 12]->handleEvent(event);

	if ((2 <= event.getX <= 19) && (0 <= event.getY <= 11))
		Gamefield::getField[event.getX - 2][event.getY]->handleEvent(event);

	if ((0 <= event.getX <= 1) && (5 <= event.getY <= 6))
		Gamefield::getHqTilePlayerA[event.getX][event.getY - 5]->handleEvent(event);

	if ((20 <= event.getX <= 21) && (5 <= event.getY <= 6))
		Gamefield::getHqTilePlayerB[event.getX-20][event.getY - 5]->handleEvent(event);

	if ((0 <= event.getX <= 1) && (0 <= event.getY <= 4))
		Gamefield::getSpawnA[event.getX][event.getY]->handleEvent(event);

	if ((0 <= event.getX <= 1) && (7 <= event.getY <= 11))
		Gamefield::getSpawnA[event.getX][event.getY - 2]->handleEvent(event);

	if ((20 <= event.getX <= 21) && (0 <= event.getY <= 4))
		Gamefield::getSpawnA[event.getX-20][event.getY]->handleEvent(event);

	if ((20 <= event.getX <= 21) && (7 <= event.getY <= 11))
		Gamefield::getSpawnA[event.getX-20][event.getY - 2]->handleEvent(event);

}