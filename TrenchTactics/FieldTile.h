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
	std::shared_ptr<UnitBase> unit;
	terrainType terrain;
public:
	
	void setUnit(std::shared_ptr<UnitBase> unit) {
		this->unit = unit;
	}
	std::shared_ptr<UnitBase> getUnit() {
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