#pragma once
#include "Headquarter.h"
#include "UnitBase.h"
#include "EventBus.h"
#include "GameLoop.h"
#include "ConfigReader.h"
#include <vector>
#include <queue>
#include <algorithm>

class Player
{
private:
	bool colorRed;
	bool buying;
	Headquarter* headquarter;
	std::vector<UnitBase*> unitArray;
	std::queue<UnitBase*> unitQueue;
	int money;
	int interest;
	int supply;
	GAMEPHASES::GAMEPHASE currentPhase;
public:
	void init(bool colorRed);
	int computeInterest();
	void updatePlayer();
	void copyUnitsToQueue();
	void deleteUnit(UnitBase* unit);
	void addUnit(UnitBase* unit) {
		this->unitArray.push_back(unit);
	}
	std::vector<UnitBase*> getUnitArray() {
		return this->unitArray;
	}
	std::queue<UnitBase*> getUnitQueue() {
		return this->unitQueue;
	}
	int getSupply() {
		return this->supply;
	}
	bool getColor() {
		return this->colorRed;
	}
	void setCurrentPhase(GAMEPHASES::GAMEPHASE phase) {
		this->currentPhase = phase;
	}
	GAMEPHASES::GAMEPHASE getCurrentPhase() {
		return this->currentPhase;
	}
	void setBuying(bool buyStatus) {
		this->buying = buyStatus;
	}
	bool getBuying() {
		return this->buying;
	}
	void deleteUnit(UnitBase* unit);
};

