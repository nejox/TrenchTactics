#pragma once
#include "FieldTile.h"
#include "PlayerTile.h"
#include "MenuTile.h"
#include "MouseClickEvent.h"
#include "RendererImpl.h"
#include "MapConf.h"
#include "stdlib.h"
#include <vector>
#include <ctime>
#include "Gamephases.h"
#include "SpriteMarker.h"
#include "MenuBar.h"


/**
 * Gamefield class for generating and holding the playingfield
 */
class Gamefield {
private:
	static const int defaultXSizeField = 18;
	static const int defaultYSizeField = 12;

	std::shared_ptr<PlayerTile> headquarterTilePlayerBlue;
	std::shared_ptr<PlayerTile> headquarterTilePlayerRed;
	std::shared_ptr<vector<vector<std::shared_ptr<FieldTile>>>> playingfield;
	std::shared_ptr<vector<vector<std::shared_ptr<FieldTile>>>> spawnBlue;
	std::shared_ptr<vector<vector<std::shared_ptr<FieldTile>>>> spawnRed;

	Gamefield();

	void setAllFieldSizes();
	
	void setSizePlayingField();
	void setSizeSpawnBlue();
	void setSizeSpawnRed();

	void initiatePlayerTilesBlue();
	void initiatePlayerTilesRed();
	
	void initiateSpawnTilesBlue();
	void initiateSpawnTilesRed();
	void initiatePlayingFieldTiles();

	std::shared_ptr<FieldTile> getSpawnFieldRed(int posX, int posY);
	std::shared_ptr<FieldTile> getSpawnFieldBlue(int posX, int posY);

	Sprite* getRandomSpawnTileSprite(int rndNumber, bool colorRed);

	std::shared_ptr<FieldTile> createFieldTile(int posX, int posY, FieldTile::TERRAINTYPE type);


public:
	~Gamefield();

	std::shared_ptr<Tile> getTilePointerAt(int xPos, int yPos);

	Gamefield(const Gamefield&) = delete;
	Gamefield& operator=(const Gamefield&) = delete;
	Gamefield(Gamefield&&) = delete;
	Gamefield& operator=(Gamefield&&) = delete;

	static auto& instance() {
		static Gamefield gamefield;
		return gamefield;
	}

	int spawnUnitInSpawn(std::shared_ptr<Unit> unit, bool redPlayerActive);

	bool fieldTileIsFree(int x, int y, std::shared_ptr<vector<vector<std::shared_ptr<FieldTile>>>> activeSpawn);

	void init(int FieldWidth, int FieldHeight, int Seed);

	std::shared_ptr<FieldTile> findTileByUnit(std::shared_ptr<Unit> pUnit);

	std::shared_ptr<FieldTile> getFieldTileFromXY(int posX, int posY);
	std::shared_ptr<FieldTile> getSpawnTileFromXY(bool colorRed, int posX, int posY);
	std::shared_ptr<PlayerTile> getPlayerTileFromXY(int posX, int posY);

	void setHqTilePlayerBlue(std::shared_ptr<PlayerTile> hqTilePlayer) {
		this->headquarterTilePlayerBlue = hqTilePlayer;
	}
	std::shared_ptr<PlayerTile> getHqTilePlayerBlue() {
		return this->headquarterTilePlayerBlue;
	}
	void setHqTilePlayerRed(std::shared_ptr<PlayerTile> hqTilePlayer) {
		this->headquarterTilePlayerRed = hqTilePlayer;
	}
	std::shared_ptr<PlayerTile> getHqTilePlayerRed() {
		return this->headquarterTilePlayerRed;
	}
	void setPlayingfield(std::shared_ptr<vector<vector<std::shared_ptr<FieldTile>>>> field) {
		this->playingfield = field;
	}
	std::shared_ptr<vector<vector<std::shared_ptr<FieldTile>>>> getPlayingfield() {
		return this->playingfield;
	}
	void setSpawnBlue(std::shared_ptr<vector<vector<std::shared_ptr<FieldTile>>>> spawnBlue) {
		this->spawnBlue = spawnBlue;
	}
	std::shared_ptr<vector<vector<std::shared_ptr<FieldTile>>>> getSpawnBlue() {
		return this->spawnBlue;
	}
	void setSpawnRed(std::shared_ptr<vector<vector<std::shared_ptr<FieldTile>>>> spawnRed) {
		this->spawnRed = spawnRed;
	}
	std::shared_ptr<vector<vector<std::shared_ptr<FieldTile>>>> getSpawnRed() {
		return this->spawnRed;
	}

	void selectAndMarkeTilesByUnit(shared_ptr<Unit> pUnit, GAMEPHASES::GAMEPHASE gamephase, bool redPlayerActiv);

	void deselectAndUnmarkAllTiles();

	bool checkUnitHasEnemysAround(shared_ptr<Unit> pUnit, bool colorRed);
};