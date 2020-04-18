#pragma once
#include "Headquarter.h"
#include "UnitBase.h"
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
	void deleteUnit(UnitBase* unit) {
		std::vector<UnitBase*>::iterator position = std::find(this->unitArray.begin(), this->unitArray.end(), unit);
		if (position != this->unitArray.end()) {// == myVector.end() means the element was not found
			this->unitArray.erase(position);
		}

	}
};

