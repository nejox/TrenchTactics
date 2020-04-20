#pragma once

/**
 * Map configeration data container with all getters and setters
 */
class MapConf {
private:
	int seed;
	int sizeX;
	int sizeY;
	std::string headquarterSpriteBlue;
	std::string headquarterSpriteRed;
	std::string spawnTileSprite;
	std::vector<std::string> terrainSpriteList;
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
	void setHeadquarterSpriteBlue(std::string headquarterSpriteBlue) {
		this->headquarterSpriteBlue = headquarterSpriteBlue;
	}
	std::string getHeadquarterSpriteBlue() {
		return this->headquarterSpriteBlue;
	}
	void setHeadquarterSpriteRed(std::string headquarterSpriteRed) {
		this->headquarterSpriteRed = headquarterSpriteRed;
	}
	std::string getHeadquarterSpriteRed() {
		return this->headquarterSpriteRed;
	}
	void setTerrainSpriteList(std::vector<std::string> terrainSpriteList) {
		this->terrainSpriteList = terrainSpriteList;
	}
	std::vector<std::string> getTerrainSpriteList() {
		return this->terrainSpriteList;
	}
	void setSpawnTileSprite(std::string spawnTileSprite) {
		this->spawnTileSprite = spawnTileSprite;
	}
	std::string getSpawnTileSprite() {
		return this->spawnTileSprite;
	}
};