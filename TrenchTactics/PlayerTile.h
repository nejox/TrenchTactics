#pragma once
#include "Tile.h"
#include "Headquarter.h"

/// <summary>
/// PlayerTile class for postition of headquarter
/// </summary>
class PlayerTile : public Tile {
private:
	Headquarter* headquarter;
public:
	void setHeadquarter(Headquarter* headquarter) {
		this->headquarter = headquarter;
	}
	Headquarter* getHeadquarter() {
		return this->headquarter;
	}
	handleEvent();
	PlayerTile();
	~PlayerTile();
	
};