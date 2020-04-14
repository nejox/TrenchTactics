#pragma once

/// <summary>
/// Balance configeration data container with all getters and setters
/// </summary>
class BalanceConf {
private:
	int hqHP;
	int trenchIncomeFactor;
	int maxAmountUnits;
	int startingGold;
	int rerollCost;
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
};