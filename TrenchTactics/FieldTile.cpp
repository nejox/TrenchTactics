#include "FieldTile.h"

/**
 * remove the unit on a field tile
 * also rerenders the empty tile afterwards
 *
 */
void FieldTile::removeUnit()
{
	this->unit = nullptr;
	if (this->getTerrain() == TERRAINTYPE::SPAWNTERRAIN) {
		this->getSprite()->render();
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
		this->unit->getSprite().get()->render();
	}

}

