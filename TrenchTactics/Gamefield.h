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

	vector<vector <MenuTile*>> menuBar;
	vector<vector <PlayerTile*>> hqTilePlayerBlue;
	vector<vector <PlayerTile*>> hqTilePlayerRed;
	vector<vector <FieldTile*>> field;
	vector<vector <FieldTile*>> spawnBlue;
	vector<vector <FieldTile*>> spawnRed;

	Gamefield();


public:
	void setMenuBar(vector<vector <MenuTile*>> menuBar) {
		this->menuBar = menuBar;
	}
	vector<vector <MenuTile*>> getMenuBar() {
		return this->menuBar;
	}
	void setHqTilePlayerBlue(vector < vector < PlayerTile*>> hqTilePlayer) {
		this->hqTilePlayerBlue = hqTilePlayer;
	}
	vector < vector < PlayerTile*>> getHqTilePlayerBlue() {
		return this->hqTilePlayerBlue;
	}
	void setHqTilePlayerRed(vector < vector <PlayerTile*>> hqTilePlayer) {
		this->hqTilePlayerRed = hqTilePlayer;
	}
	vector < vector < PlayerTile*>> getHqTilePlayerRed() {
		return this->hqTilePlayerRed;
	}
	void setField(vector < vector < FieldTile*>> field) {
		this->field = field;
	}
	vector < vector < FieldTile*>> getField() {
		return this->field;
	}
	void setSpawnBlue(vector < vector < FieldTile*>> spawnBlue) {
		this->spawnBlue = spawnBlue;
	}
	vector < vector < FieldTile*>> getSpawnBlue() {
		return this->spawnBlue;
	}
	void setSpawnRed(vector < vector < FieldTile*>> spawnRed) {
		this->spawnRed = spawnRed;
	}
	vector < vector < FieldTile*>> getSpawnRed() {
		return this->spawnRed;
	}


	void resetGameField();
	~Gamefield();
	// void assignEventToTile(MouseClickEvent event); -----noch noetig?

	Tile* Gamefield::getTilePointerAt(int x, int y);

	Gamefield(const Gamefield&) = delete;
	Gamefield& operator=(const Gamefield&) = delete;
	Gamefield(Gamefield&&) = delete;
	Gamefield& operator=(Gamefield&&) = delete;

	static auto& instance() {
		static Gamefield gamefield;
		return gamefield;
	}

	int spawnUnitInSpawn(UnitBase* unit, bool redPlayerActive);
	bool spawnTileIsFree(int x, int y, vector<vector<FieldTile*>> activeSpawn);

	void Init(int FieldWidth, int FieldHeight, int Seed);
	void initiatePlayerTiles(vector<vector<PlayerTile*>> hqTilePlayerX);
	void initiateMenuTiles(vector<vector<MenuTile*>> menuBar);
	void initiateSpawnTiles(vector<vector<FieldTile*>> spawn);
	void initiatePlayingFieldTiles(vector<vector<FieldTile*>> playingField);
};