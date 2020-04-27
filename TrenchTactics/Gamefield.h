#pragma once
#include "FieldTile.h"
#include "PlayerTile.h"
#include "MenuTile.h"
#include "MouseClickEvent.h"
#include "RendererImpl.h"
#include "MapConf.h"
#include "stdlib.h"
#include <vector>
#include "Gamephases.h"

/**
 * Gamefield class for generating and holding the playingfield
 */
class Gamefield {
private:
	static const int defaultXSizeField = 18;
	static const int defaultYSizeField = 12;

	std::shared_ptr<vector<vector<std::shared_ptr<MenuTile>>>> menuBar;
	std::shared_ptr<vector<vector<std::shared_ptr<PlayerTile>>>> headquarterTilePlayerBlue;
	std::shared_ptr<vector<vector<std::shared_ptr<PlayerTile>>>> headquarterTilePlayerRed;
	std::shared_ptr<vector<vector<std::shared_ptr<FieldTile>>>> playingfield;
	std::shared_ptr<vector<vector<std::shared_ptr<FieldTile>>>> spawnBlue;
	std::shared_ptr<vector<vector<std::shared_ptr<FieldTile>>>> spawnRed;

	Gamefield();

	void setAllFieldSizes();
	void setSizePlayerTilesBlue();
	void setSizePlayerTilesRed();
	void setSizeMenuBar();
	void setSizePlayingField();
	void setSizeSpawnBlue();
	void setSizeSpawnRed();

	void initiatePlayerTilesBlue();
	void initiatePlayerTilesRed();
	void initiateMenuTiles();
	void initiateSpawnTilesBlue();
	void initiateSpawnTilesRed();
	void initiatePlayingFieldTiles();

public:
	~Gamefield();

	std::shared_ptr<Tile> getTilePointerAt(int x, int y);

	Gamefield(const Gamefield&) = delete;
	Gamefield& operator=(const Gamefield&) = delete;
	Gamefield(Gamefield&&) = delete;
	Gamefield& operator=(Gamefield&&) = delete;

	static auto& instance() {
		static Gamefield gamefield;
		return gamefield;
	}

	void resetGameField();

	int spawnUnitInSpawn(std::shared_ptr<Unit> unit, bool redPlayerActive);

	bool fieldTileIsFree(int x, int y, vector<vector<std::shared_ptr<FieldTile>>> activeSpawn);

	void init(int FieldWidth, int FieldHeight, int Seed);

	std::shared_ptr<FieldTile> findTileForUnit(std::shared_ptr<Unit> pUnit);

	void displayButtons(GAMEPHASES::GAMEPHASE phase);


	void setMenuBar(std::shared_ptr<vector<vector <std::shared_ptr<MenuTile>>>> menuBar) {
		this->menuBar = menuBar;
	}
	std::shared_ptr<vector<vector<std::shared_ptr<MenuTile>>>> getMenuBar() {
		return this->menuBar;
	}
	void setHqTilePlayerBlue(std::shared_ptr<vector<vector<std::shared_ptr<PlayerTile>>>> hqTilePlayer) {
		this->headquarterTilePlayerBlue = hqTilePlayer;
	}
	std::shared_ptr<vector<vector<std::shared_ptr<PlayerTile>>>> getHqTilePlayerBlue() {
		return this->headquarterTilePlayerBlue;
	}
	void setHqTilePlayerRed(std::shared_ptr<vector<vector<std::shared_ptr<PlayerTile>>>> hqTilePlayer) {
		this->headquarterTilePlayerRed = hqTilePlayer;
	}
	std::shared_ptr<vector<vector<std::shared_ptr<PlayerTile>>>> getHqTilePlayerRed() {
		return this->headquarterTilePlayerRed;
	}
	void setField(std::shared_ptr<vector<vector<std::shared_ptr<FieldTile>>>> field) {
		this->playingfield = field;
	}
	std::shared_ptr<vector<vector<std::shared_ptr<FieldTile>>>> getField() {
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

};