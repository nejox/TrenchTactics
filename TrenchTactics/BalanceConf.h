#pragma once

/**
 * Base class for balnce configuration of the game
 * Used to hold data and provide it to other instances
 * Provides all necessary getters and setters
 * Provided by ConfigReader
 */
class BalanceConf {
private:
	int hqHP;
	int trenchIncomeFactor;
	int maxAmountUnits;
	int startingGold;
	int rerollCost;
	int additionalUnitRollCost;
public:
	void setHqHp(int hqHP) {
		this->hqHP = hqHP;
	}
	int getHqHP() {
		return this->hqHP;
	}
	void setTrenchIncomeFactoR(int trenchIncomeFactor) {
		this->trenchIncomeFactor = trenchIncomeFactor;
	}
	int getTrenchIncomeFactor() {
		return this->trenchIncomeFactor;
	}
	void setMaxAmountUnits(int maxAmountUnits) {
		this->maxAmountUnits = maxAmountUnits;
	}
	int getMaxAmountUnits() {
		return this->maxAmountUnits;
	}
	void setStartingGold(int startingGold) {
		this->startingGold = startingGold;
	}
	int getStartingGold() {
		return this->startingGold;
	}
	void setRerollCost(int rerollCost) {
		this->rerollCost = rerollCost;
	}
	int getRerollCost() {
		return this->rerollCost;
	}
	void setAdditionalUnitRollCost(int additionalUnitRollCost) {
		this->additionalUnitRollCost = additionalUnitRollCost;
	}
	int getAdditionalUnitRollCost() {
		return this->additionalUnitRollCost;
	}
};