#pragma once
#include "FieldTile.h"
#include "PlayerTile.h"
#inlcude "MenuTile.h"

/// <summary>
/// Gamefield class for generating and holding the playingfield
/// </summary>
class Gamefield {
private:
	MenuTile*[][] menuBar;
	PlayerTile*[][] hqTilePlayerA;
	PlayerTile*[][] hqTilePlayerB;
	FieldTile*[][] field;
	FieldTile*[][][] spawnA;
	FieldTile*[][][] spawnB;
public:
	void setMenuBar(MenuTile*[][] menuBar) {
		this->menuBar = menuBar;
	}
	MenuTile*[][] getMenuBar() {
		return this->menuBar;
	}
	void setHqTilePlayerA(PlayerTile*[][] hqTilePlayer) {
		this->hqTilePlayerA = hqTilePlayer;
	}
	PlayerTile*[][] getHqTilePlayerA() {
		return this->hqTilePlayerA;
	}
	void setHqTilePlayerB(PlayerTile*[][] hqTilePlayer) {
		this->hqTilePlayerB = hqTilePlayer;
	}
	PlayerTile*[][] getHqTilePlayerB() {
		return this->hqTilePlayerB;
	}
	void setField(FieldTile*[][] field) {
		this->field = field;
	}
	FieldTile*[][] getField() {
		return this->field;
	}
	void setSpawnA(FieldTile*[][][] spawnA) {
		this->spawnA = spawnA;
	}
	FieldTile*[][][] getSpawnA() {
		return this->spawnA;
	}
	void setSpawnB(FieldTile*[][][] spawnB) {
		this->spawnB = spawnB;
	}
	FieldTile*[][][] getSpawnB() {
		return this->spawnB;
	}
	void resetGameField();
	Gamefield();
	~Gamefield();
};