#pragma once

class BalanceConf {
private:
	int hqHP;
	int trenchIncomeFactor;
	int maxAmountUnits;
	int startingGold;
	int rerollCost;
public:
	int getHqHP();
	int getTrenchIncomeFactor();
	int getMaxAmountUnits();
	int getStartingGold();
	int getRerollCost();
};