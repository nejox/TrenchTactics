#pragma once
#include "Tile.h"
#include "Headquarter.h"

/**
 * PlayerTile class for postition of headquarter, healthbar and sprites/
 */
class PlayerTile : public Tile {
private:
	std::shared_ptr<Headquarter> headquarter;
public:
	void setHeadquarter(std::shared_ptr<Headquarter> headquarter) {
		this->headquarter = headquarter;
	}
	std::shared_ptr<Headquarter> getHeadquarter() {
		return this->headquarter;
	}

	PlayerTile() {};
	~PlayerTile() {};

};