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
	std::map<int, Sprite*> trenchSprites;
	


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

	void setTrench(bool trench) {
		this->trench = trench;
	}


	bool hasTrench(){
		return this->trench;
	}

	std::map<int, Sprite*> getTrenchSprites()
	{
		return this->trenchSprites;
	}

	void addTrenchSprite(int rect, Sprite* sprite)
	{
		this->trenchSprites.insert(pair<int,Sprite*>(rect, sprite));
	}

	bool hasCopse();

	/**
	*adds a copse to the corpse vector
	* \param x y coordinates of the copse
	*/
	void addCorpse();

	void removeCorpse();

};