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

	bool trench;
	std::shared_ptr<std::map<int, std::shared_ptr<Sprite>>> trenchSprites;
	


public:

	FieldTile() {
		this->trenchSprites = std::make_shared<std::map<int, std::shared_ptr<Sprite>>>();
		this->trench = false;
		this->unit = nullptr;
	};

	FieldTile(TERRAINTYPE terrain) {
		this->terrain = terrain;
		this->trenchSprites = std::make_shared<std::map<int, std::shared_ptr<Sprite>>>();
		this->trench = false;
		this->unit = nullptr;
	}

	~FieldTile() {};

	void removeUnit();
	void refreshTile();
	void resetTile();

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

	void setTrench(bool trench) {
		if (this->getTerrain() != TERRAINTYPE::SPAWNTERRAIN) {
			this->trench = trench;
		}
	}

	bool hasTrench(){
		return this->trench;
	}

	std::shared_ptr<std::map<int, std::shared_ptr<Sprite>>> getTrenchSprites()
	{
		return this->trenchSprites;
	}

	void addTrenchSprite(int rect, std::shared_ptr<Sprite> sprite)
	{
		if (this->getTerrain() != TERRAINTYPE::SPAWNTERRAIN) {
			this->trenchSprites->insert(std::pair<int, std::shared_ptr<Sprite>>(rect, sprite));
			refreshTile();
		}
	}

	bool hasCopse();

	/**
	*adds a copse to the corpse vector
	* \param x y coordinates of the copse
	*/
	void addCorpse();

	void removeCorpse();

};