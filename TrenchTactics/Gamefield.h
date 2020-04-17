#pragma once
#include "FieldTile.h"
#include "PlayerTile.h"
#include "MenuTile.h"
#include <vector>

/// <summary>
/// Gamefield class for generating and holding the playingfield
/// </summary>
class Gamefield {
private:
	static const int defaultXSizeField = 18;
	static const int defaultYSizeField = 12;

	vector<vector <MenuTile*>> menuBar;
	vector<vector <PlayerTile*>> hqTilePlayerA;
	vector<vector <PlayerTile*>> hqTilePlayerB;
	vector<vector <FieldTile*>> field;
	vector<vector <FieldTile*>> spawnA;
	vector<vector <FieldTile*>> spawnB;
public:
	void setMenuBar(vector<vector <MenuTile*>> menuBar) {
		this->menuBar = menuBar;
	}
	vector<vector <MenuTile*>> getMenuBar() {
		return this->menuBar;
	}
	void setHqTilePlayerA(vector < vector < PlayerTile*>> hqTilePlayer) {
		this->hqTilePlayerA = hqTilePlayer;
	}
	vector < vector < PlayerTile*>> getHqTilePlayerA() {
		return this->hqTilePlayerA;
	}
	void setHqTilePlayerB(vector < vector <PlayerTile*>> hqTilePlayer) {
		this->hqTilePlayerB = hqTilePlayer;
	}
	vector < vector < PlayerTile*>> getHqTilePlayerB() {
		return this->hqTilePlayerB;
	}
	void setField(vector < vector < FieldTile*>> field) {
		this->field = field;
	}
	vector < vector < FieldTile*>> getField() {
		return this->field;
	}
	void setSpawnA(vector < vector < FieldTile*>> spawnA) {
		this->spawnA = spawnA;
	}
	vector < vector < FieldTile*>> getSpawnA() {
		return this->spawnA;
	}
	void setSpawnB(vector < vector < FieldTile*>> spawnB) {
		this->spawnB = spawnB;
	}
	vector < vector < FieldTile*>> getSpawnB() {
		return this->spawnB;
	}
	void resetGameField();
	Gamefield();
	~Gamefield();
};