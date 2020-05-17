#pragma once
#include <string>


/**
 * Unit Configuration data container with all values concerning the available units
 * Provides all getters and setters as well
 * Provided by the ConfigReader
 */
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

	std::string spriteFilePathStandingActiveRed;
	std::string spriteFilePathStandingNeutralRed;
	std::string spriteFilePathShootingRed;
	std::string spriteFilePathRunningRed;

	std::string spriteFilePathStandingActiveBlue;
	std::string spriteFilePathStandingNeutralBlue;
	std::string spriteFilePathShootingBlue;
	std::string spriteFilePathRunningBlue;


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
	void setSpriteFilePathStandingActiveRed(std::string spriteFilePathStandingActiveRed) {
		this->spriteFilePathStandingActiveRed = spriteFilePathStandingActiveRed;
	}
	std::string getSpriteFilePathStandingActiveRed() {
		return this->spriteFilePathStandingActiveRed;
	}
	void setSpriteFilePathStandingNeutralRed(std::string spriteFilePathStandingNeutralRed) {
		this->spriteFilePathStandingNeutralRed = spriteFilePathStandingNeutralRed;
	}
	std::string getSpriteFilePathStandingNeutralRed() {
		return this->spriteFilePathStandingNeutralRed;
	}
	void setSpriteFilePathShootingRed(std::string spriteFilePathShootingRed) {
		this->spriteFilePathShootingRed = spriteFilePathShootingRed;
	}
	std::string getSpriteFilePathShootingRed() {
		return this->spriteFilePathShootingRed;
	}
	void setSpriteFilePathRunningRed(std::string spriteFilePathRunningRed) {
		this->spriteFilePathRunningRed = spriteFilePathRunningRed;
	}
	std::string getSpriteFilePathRunningRed() {
		return this->spriteFilePathRunningRed;
	}
	void setSpriteFilePathStandingActiveBlue(std::string spriteFilePathStandingActiveBlue) {
		this->spriteFilePathStandingActiveBlue = spriteFilePathStandingActiveBlue;
	}
	std::string getSpriteFilePathStandingActiveBlue() {
		return this->spriteFilePathStandingActiveBlue;
	}
	void setSpriteFilePathStandingNeutralBlue(std::string spriteFilePathStandingNeutralBlue) {
		this->spriteFilePathStandingNeutralBlue = spriteFilePathStandingNeutralBlue;
	}
	std::string getSpriteFilePathStandingNeutralBlue() {
		return this->spriteFilePathStandingNeutralBlue;
	}
	void setSpriteFilePathShootingBlue(std::string spriteFilePathShootingBlue) {
		this->spriteFilePathShootingBlue = spriteFilePathShootingBlue;
	}
	std::string getSpriteFilePathShootingBlue() {
		return this->spriteFilePathShootingBlue;
	}
	void setSpriteFilePathRunningBlue(std::string spriteFilePathRunningBlue) {
		this->spriteFilePathRunningBlue = spriteFilePathRunningBlue;
	}
	std::string getSpriteFilePathRunningBlue() {
		return this->spriteFilePathRunningBlue;
	}

};