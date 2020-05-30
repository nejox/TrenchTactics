#pragma once

/**
 * Map configuration data container with all getters and setters
 */
class MapConf {
private:
	int seed;
	int sizeX;
	int sizeY;
	std::string corpseSprite;

public:
	void setSeed(int seed) {
		this->seed = seed;
	}
	int getSeed() {
		return this->seed;
	}
	void setSizeX(int sizeX) {
		this->sizeX = sizeX;
	}
	int getSizeX() {
		return this->sizeX;
	}
	void setSizeY(int sizeY) {
		this->sizeY = sizeY;
	}
	int getSizeY() {
		return this->sizeY;
	}
	void setCorpseSprite(std::string corpseSprite) {
		this->corpseSprite = corpseSprite;
	}
	std::string getCorpseSprite() {
		return this->corpseSprite;
	}
};