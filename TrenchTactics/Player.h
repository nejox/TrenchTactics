#pragma once
#include "Headquarter.h"
#include "UnitBase.h"
#include <vector>
#include <queue>

class Player
{
private:
	bool colorRed;
	Headquarter* headquarter;
	std::vector<UnitBase*> unitArray;
	std::queue<UnitBase*> unitQueue;
	int money;
	int interest;
	int supply;
	GAMPHASES::GAMEPHASE currentPhase;
public:
	void init(bool colorRed);
	void computeInterest();
	void updatePlayer();
	void copyUnitsToQueue();
	void addUnit();
	std::vector<UnitBase*> getUnitArray() {
		return this->unitArray;
	}
	std::queue<UnitBase*> getUnitQueue() {
		return this->unitQueue;
	}
	bool getColor() {
		return this->colorRed;
	}
	void setCurrentPhase(GAMPHASES::GAMEPHASE phase) {
		this->currentPhase = phase;
	}
};

