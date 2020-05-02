#pragma once
#include "Tile.h"
#include "Unit.h"


/// <summary>
/// FieldTile class for holding Units and Terraintyp
/// </summary>
class FieldTile : public Tile {

public:
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