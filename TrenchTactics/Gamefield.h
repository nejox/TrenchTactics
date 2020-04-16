#pragma once
#include "FieldTile.h"
#include "PlayerTile.h"
#include "MenuTile.h"


/// <summary>
/// Gamefield class for generating and holding the playingfield
/// </summary>
class Gamefield {
private:
	static const int defaultXSizeField = 18;
	static const int defaultYSizeField = 12;

	MenuTile menuBar[22][2];
	PlayerTile hqTilePlayerA[2][2];
	PlayerTile hqTilePlayerB[2][2];
	FieldTile field[defaultXSizeField][defaultYSizeField];
	FieldTile spawnA[2][4][2];
	FieldTile spawnB[2][4][2];
public:
	void setMenuBar(MenuTile *menuBar) {
		this->menuBar[22][2] = *menuBar;
	}
	MenuTile getMenuBar() {
		return this->menuBar[22][2];
	}
	void setHqTilePlayerA(PlayerTile *hqTilePlayer) {
		this->hqTilePlayerA[2][2] = *hqTilePlayer;
	}
	PlayerTile getHqTilePlayerA() {
		return this->hqTilePlayerA[2][2];
	}
	void setHqTilePlayerB(PlayerTile *hqTilePlayer) {
		this->hqTilePlayerB[2][2] = *hqTilePlayer;
	}
	PlayerTile getHqTilePlayerB() {
		return this->hqTilePlayerB[2][2];
	}
	void setField(FieldTile *field) {
		this->field[defaultXSizeField][defaultYSizeField] = *field;
	}
	FieldTile getField() {
		return this->field[defaultXSizeField][defaultYSizeField];
	}
	void setSpawnA(FieldTile *spawnA) {
		this->spawnA[2][4][2] = *spawnA;
	}
	FieldTile getSpawnA() {
		return this->spawnA[2][4][2];
	}
	void setSpawnB(FieldTile *spawnB) {
		this->spawnB[2][4][2] = *spawnB;
	}
	FieldTile getSpawnB() {
		return this->spawnB[2][4][2];
	}
	void resetGameField();
	Gamefield();
	~Gamefield();
};