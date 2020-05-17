#pragma once
#include <string>
#include <vector>

/**
 * Tile Configuration data container containing all tiles with their respective sprite file paths
 * Provides all getters and setters as well
 * Provided by the ConfigReader
 */
class TileConf {
private:
	std::string headquarterSpriteBlue;
	std::string headquarterSpriteRed;
	std::string reachableMarkerSprite;
	std::string nextUnitButtonSprite;
	std::string previousUnitButtonSprite;
	std::string unitCounterSprite;
	std::string moneyTokenSprite;
	std::string nextPhaseButtonSprite;
	std::string endTurnButtonSprite;
	std::vector<std::string> spawnTileSpriteListBlue;
	std::vector<std::string> spawnTileSpriteListRed;
	std::vector<std::string> terrainSpriteList;
public:
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
	void setReachableMarkerSprite(std::string reachableMarkerSprite) {
		this->reachableMarkerSprite = reachableMarkerSprite;
	}
	std::string getReachableMarkerSprite() {
		return this->reachableMarkerSprite;
	}
	void setNextUnitButtonSprite(std::string nextUnitButtonSprite) {
		this->nextUnitButtonSprite = nextUnitButtonSprite;
	}
	std::string getNextUnitButtonSprite() {
		return this->nextUnitButtonSprite;
	}
	void setPreviousUnitButtonSprite(std::string previousUnitButtonSprite) {
		this->previousUnitButtonSprite = previousUnitButtonSprite;
	}
	std::string getPreviousUnitButtonSprite() {
		return this->previousUnitButtonSprite;
	}
	void setUnitCounterSprite(std::string unitCounterSprite) {
		this->unitCounterSprite = unitCounterSprite;
	}
	std::string getUnitCounterSprite() {
		return this->unitCounterSprite;
	}
	void setMoneyTokenSprite(std::string moneyTokenSprite) {
		this->moneyTokenSprite = moneyTokenSprite;
	}
	std::string getMoneyTokenSprite() {
		return this->moneyTokenSprite;
	}
	void setNextPhaseButtonSprite(std::string nextPhaseButtonSprite) {
		this->nextPhaseButtonSprite = nextPhaseButtonSprite;
	}
	std::string getNextPhaseButtonSprite() {
		return this->nextPhaseButtonSprite;
	}
	void setEndTurnButtonSprite(std::string endTurnButtonSprite) {
		this->endTurnButtonSprite = endTurnButtonSprite;
	}
	std::string getEndTurnButtonSprite() {
		return this->endTurnButtonSprite;
	}
	void setTerrainSpriteList(std::vector<std::string> terrainSpriteList) {
		this->terrainSpriteList = terrainSpriteList;
	}
	std::vector<std::string> getTerrainSpriteList() {
		return this->terrainSpriteList;
	}
	void setSpawnTileSpriteListBlue(std::vector<std::string> spawnTileSpriteListBlue) {
		this->spawnTileSpriteListBlue = spawnTileSpriteListBlue;
	}
	void setSpawnTileSpriteListRed(std::vector<std::string> spawnTileSpriteListRed) {
		this->spawnTileSpriteListRed = spawnTileSpriteListRed;
	}

	std::vector<std::string> getSpawnTileSpriteList(bool colorRed) {
		if (colorRed) {
			return this->spawnTileSpriteListBlue;
		}
		else {
			return this->spawnTileSpriteListBlue;
		}
	}

};