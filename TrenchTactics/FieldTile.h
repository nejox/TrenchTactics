#pragma once
#include "Tile.h"
#include "Unit.h"


/// <summary>
/// FieldTile class for holding Units and Terraintyp
/// </summary>
class FieldTile : public Tile {

public:
	enum terrainType {
		mud,
		clay,
		stone,
		spawnterrain
	};

private:
	Unit* unit;
	terrainType terrain;
public:
	
	void setUnit(Unit* unit) {
		this->unit = unit;
	}
	Unit* getUnit() {
		return this->unit;
	}
	void setTerrain(terrainType terrain) {
		this->terrain = terrain;
	}
	terrainType getTerrain() {
		return this->terrain;
	}

	FieldTile(terrainType terrain) {
		this->terrain = terrain;
	};

	~FieldTile() {};
};