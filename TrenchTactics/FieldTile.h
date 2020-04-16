#pragma once
#include "Tile.h"
#include "Unit.h"

/// <summary>
/// FieldTile class for holding Units and Terraintyp
/// </summary>
class FieldTile : public Tile {
enum terrainTyp {
	mud,
	clay,
	stone,
	spawn
	}
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
	void setTerrain(terrainTyp terrain) {
		this->terrain = terrain;
	}
	terrainTyp getTerrain() {
		return this->terrain;
	}
	void handleEvent();
	FieldTile(terrainType terrain);
	~FieldTile();
};