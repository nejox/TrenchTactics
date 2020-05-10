#pragma once
#include "Tile.h"
#include "Headquarter.h"

/// <summary>
/// PlayerTile class for postition of headquarter
/// </summary>
class PlayerTile : public Tile {
private:
	std::shared_ptr<Headquarter> headquarter;
	std::shared_ptr<SpriteHQ> spriteHq;
public:
	void setHeadquarter(std::shared_ptr<Headquarter> headquarter) {
		this->headquarter = headquarter;
	}
	std::shared_ptr<Headquarter> getHeadquarter() {
		return this->headquarter;
	}
	void setSpriteHq(std::shared_ptr<SpriteHQ> spriteHq) {
		this->spriteHq = spriteHq;
	}

	std::shared_ptr<SpriteHQ> getSpriteHq() {
		return this->spriteHq;
	}

	PlayerTile() {};
	~PlayerTile() {};
	
};