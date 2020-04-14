#pragma once
#include <string>

class UnitConf {
private:
	UnitConf();
	int id;
	int hp;
	int range;
	int cost;
	int ap;
	int dmg;
	int apCostAttack;
	int apCostMove;
	int apCostTrench;
	int spawnProbability;
	std::string name;
	std::string spriteFilePath;

public:
	int getId() {
		return this->id;
	}
	int getHp() {
		return this->hp;
	}
	int getRange() {
		return this->range;
	}
	int getCost() {
		return this->cost;
	}
	int getAp() {
		return this->ap;
	}
	int getDmg() {
		return this->dmg;
	}
	int getApCostAttack() {
		return this->apCostAttack;
	}
	int getApCostMove() {
		return this->apCostMove;
	}
	int getApCostTrench() {
		return this->apCostTrench;
	}
	int getSpawnProbability() {
		return this->spawnProbability;
	}
	std::string getName() {
		return this->name;
	}
	std::string getSpriteFilePath() {
		return this->spriteFilePath;
	}
};