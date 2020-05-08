#include "FieldTile.h"

/**
 * remove the unit on a field tile
 * also rerenders the empty tile afterwards
 *
 */
void FieldTile::removeUnit()
{
	this->unit = nullptr;
	refreshTile();

}

/**
 *
 * refresh Tile
 *
 */
void FieldTile::refreshTile() {
	if (this->getTerrain() == TERRAINTYPE::SPAWNTERRAIN) {
		int x = (this->getPosX() / 64) % 2 * 64;
		int y = (this->getPosY() / 64) % 2 * 64;
		this->getSprite()->render(x, y);
	}
	else {
		this->getSprite()->render();
	}
}

/**
 * function to attach a unit to fieldtile
 * updates the sprite position with the position of the field tile and renders it
 *
 * \param unit
 */
void FieldTile::setUnit(std::shared_ptr<Unit> unit)
{
	if (unit) {
		unit.get()->getSprite().get()->setPos(this->getPosX(), this->getPosY());
		this->unit = unit;
	}

}

