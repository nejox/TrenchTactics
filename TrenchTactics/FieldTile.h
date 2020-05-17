#pragma once
#include "Tile.h"
#include "Unit.h"


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
};