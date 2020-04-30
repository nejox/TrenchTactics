#include "FieldTile.h"

void FieldTile::removeUnit()
{
	this->unit = NULL;
	this->getSprite()->render();
}

void FieldTile::setUnit(std::shared_ptr<Unit> unit)
{
	unit.get()->getSprite().get()->setPos(this->getPosX() * 64, this->getPosY() * 64);
	this->unit = unit;
}

