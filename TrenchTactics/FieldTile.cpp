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
 *including corpse and trench
 */
void FieldTile::refreshTile() {

	if (this->getTerrain() == TERRAINTYPE::SPAWNTERRAIN) {
		int x = (this->getPosX() / 64) % 2 * 64;
		int y = (this->getPosY() / 64) % 2 * 64;
		this->getSprite()->render(x, y);
		if (this->getMarked()) {
			this->getMarker()->render();
		}
	}
	else {
		this->getSprite()->render();
		
		//if it has a trenchsprite
		if (!(this->trenchSprites->empty()))
		{

			//iterate over map
			std::map<int, Sprite*>::iterator itr = trenchSprites->begin();
			while (itr != trenchSprites->end()) {
				//itr second is the sprite, itr first is the framenumber to render
				itr->second->render((itr->first * 64), 0);
				itr++;

			}
		}

		if (this->getMarked()) {
			this->getMarker()->render();
		}


		if (this->corpse != nullptr) {
			this->corpse->render();
		}
	}
}

/**
 * function to reset the fieldtile back to initial state
 *
 */
void FieldTile::resetTile()
{
	if (this->corpse != nullptr) {
		this->corpse = nullptr;
	}
	if (this->trench) {
		this->trench = false;
		this->trenchSprites->clear();
	}
	refreshTile();

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
		//TODO
		if (unit->getState() != STATES::UNITSTATE::RUNNING) {
			unit.get()->getSprite().get()->setPos(this->getPosX(), this->getPosY());
			unit.get()->getSpriteHealthBar().get()->setPos(this->getPosX(), this->getPosY());
		}

		this->unit = unit;
	}

}

bool FieldTile::hasCopse()
{
	if (this->corpse == nullptr) return false;
	else return true;
}

void FieldTile::addCorpse()
{
	this->corpse = make_shared<Corpse>(this->getPosX(), this->getPosY());
	refreshTile();
}

void FieldTile::removeCorpse()
{
	this->corpse = nullptr;
	refreshTile();
}

