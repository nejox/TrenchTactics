#pragma once
#include "Tile.h"
#include "UnitBase.h"


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
	UnitBase* unit;
	terrainType terrain;
public:
	
	void setUnit(UnitBase* unit) {
		this->unit = unit;
	}
	UnitBase* getUnit() {
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