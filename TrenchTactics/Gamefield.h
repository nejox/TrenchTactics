#pragma once
#include "FieldTile.h"
#include "PlayerTile.h"
#include "MenuTile.h"
#include "MouseClickEvent.h"
#include "stdlib.h"
#include <vector>

/// <summary>
/// Gamefield class for generating and holding the playingfield
/// </summary>
class Gamefield {
private:
	static const int defaultXSizeField = 18;
	static const int defaultYSizeField = 12;

	vector<vector <std::shared_ptr<MenuTile>>> menuBar;
	vector<vector <std::shared_ptr<PlayerTile>>> headquarterTilePlayerBlue;
	vector<vector <std::shared_ptr<PlayerTile>>> headquarterTilePlayerRed;
	vector<vector <std::shared_ptr<FieldTile>>> playingfield;
	vector<vector <std::shared_ptr<FieldTile>>> spawnBlue;
	vector<vector <std::shared_ptr<FieldTile>>> spawnRed;

	Gamefield();


public:
	void setMenuBar(vector<vector <std::shared_ptr<MenuTile>>> menuBar) {
		this->menuBar = menuBar;
	}
	vector<vector <std::shared_ptr<MenuTile>>> getMenuBar() {
		return this->menuBar;
	}
	void setHqTilePlayerBlue(vector < vector <std::shared_ptr< PlayerTile>>> hqTilePlayer) {
		this->headquarterTilePlayerBlue = hqTilePlayer;
	}
	vector < vector < std::shared_ptr<PlayerTile>>> getHqTilePlayerBlue() {
		return this->headquarterTilePlayerBlue;
	}
	void setHqTilePlayerRed(vector < vector <std::shared_ptr <PlayerTile>>> hqTilePlayer) {
		this->headquarterTilePlayerRed = hqTilePlayer;
	}
	vector < vector < std::shared_ptr<PlayerTile>>> getHqTilePlayerRed() {
		return this->headquarterTilePlayerRed;
	}
	void setField(vector < vector < std::shared_ptr<FieldTile>>> field) {
		this->playingfield = field;
	}
	vector < vector < std::shared_ptr<FieldTile>>> getField() {
		return this->playingfield;
	}
	void setSpawnBlue(vector < vector < std::shared_ptr<FieldTile>>> spawnBlue) {
		this->spawnBlue = spawnBlue;
	}
	vector < vector < std::shared_ptr<FieldTile>>> getSpawnBlue() {
		return this->spawnBlue;
	}
	void setSpawnRed(vector < vector < std::shared_ptr<FieldTile>>> spawnRed) {
		this->spawnRed = spawnRed;
	}
	vector < vector < std::shared_ptr<FieldTile>>> getSpawnRed() {
		return this->spawnRed;
	}


	void resetGameField();
	~Gamefield();
	// void assignEventToTile(MouseClickEvent event); -----noch noetig?

	std::shared_ptr < Tile> Gamefield::getTilePointerAt(int x, int y);

	Gamefield(const Gamefield&) = delete;
	Gamefield& operator=(const Gamefield&) = delete;
	Gamefield(Gamefield&&) = delete;
	Gamefield& operator=(Gamefield&&) = delete;

	static auto& instance() {
		static Gamefield gamefield;
		return gamefield;
	}

	int spawnUnitInSpawn(std::shared_ptr<UnitBase> unit, bool redPlayerActive);
	bool fieldTileIsFree(int x, int y, vector<vector<std::shared_ptr<FieldTile>>> activeSpawn);

	void Init(int FieldWidth, int FieldHeight, int Seed);

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

	std::shared_ptr<FieldTile> findTileForUnit(std::shared_ptr<UnitBase> pUnit);
};