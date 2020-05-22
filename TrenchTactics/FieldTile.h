#pragma once
#include "Tile.h"
#include "Unit.h"
#include "Corpse.h"


/**
 * FieldTile class for holding Units and Terraintype .
 */
class FieldTile : public Tile {

public:
	/**
	 * Different possible terraintypes.
	 */
	enum TERRAINTYPE {
		MUD,
		CLAY,
		STONE,
		SPAWNTERRAIN
	};

private:
	std::shared_ptr<Unit> unit;
	TERRAINTYPE terrain;
	std::shared_ptr<Corpse> corpse;

public:

	FieldTile() {};

	FieldTile(TERRAINTYPE terrain) {
		this->terrain = terrain;
	}

	~FieldTile() {};

	void removeUnit();
	void refreshTile();

	void setUnit(std::shared_ptr<Unit> unit);

	std::shared_ptr<Unit> getUnit() {
		return this->unit;
	}
	void setTerrain(TERRAINTYPE terrain) {
		this->terrain = terrain;
	}
	TERRAINTYPE getTerrain() {
		return this->terrain;
	}

	std::shared_ptr<Corpse> getCorpse() {
		return this->corpse;
	}

	bool hasCopse();

	/**
	*adds a copse to the corpse vector
	* \param x y coordinates of the copse
	*/
	void addCorpse();

	void removeCorpse();

};