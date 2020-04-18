#pragma once
#include <string>


/// <summary>
/// Unit configeration data container with all getters and setters
/// </summary>
class UnitConf {
private:

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


	void setId(int id) {
		this->id = id;
	}
	int getId() {
		return this->id;
	}
	void setHp(int hp) {
		this->hp = hp;
	}
	int getHp() {
		return this->hp;
	}
	void setRange(int range) {
		this->range = range;
	}
	int getRange() {
		return this->range;
	}
	void setCost(int cost) {
		this->cost = cost;
	}
	int getCost() {
		return this->cost;
	}
	void setAp(int ap) {
		this->ap = ap;
	}
	int getAp() {
		return this->ap;
	}
	void setDmg(int dmg) {
		this->dmg = dmg;
	}
	int getDmg() {
		return this->dmg;
	}
	void setApCostAttack(int apCostAttack)
	{
		this->apCostAttack = apCostAttack;
	}
	int getApCostAttack() {
		return this->apCostAttack;
	}
	void setApCostMove(int apCostMove)
	{
		this->apCostMove = apCostMove;
	}
	int getApCostMove() {
		return this->apCostMove;
	}
	void setApCostTrench(int apCostTrench)
	{
		this->apCostTrench = apCostTrench;
	}
	int getApCostTrench() {
		return this->apCostTrench;
	}
	void setSpawnProbability(int spawnProbability) {
		this->spawnProbability = spawnProbability;
	}
	int getSpawnProbability() {
		return this->spawnProbability;
	}
	void setName(std::string name) {
		this->name = name;
	}
	std::string getName() {
		return this->name;
	}
	void setSpriteFilePath(std::string spriteFilePath) {
		this->spriteFilePath = spriteFilePath;
	}
	std::string getSpriteFilePath() {
		return this->spriteFilePath;
	}
};