#pragma once
#include "UnitBase.h"

class UnitGunner : public UnitBase
{
private:

	static const int s_cost = 50;
	static const int s_spawnRate = 40;
public:
	/// <summary>
	/// Instantiates a Gunner Unit with all base stats necessary
	/// </summary>
	UnitGunner() : UnitBase(100, 80, 6, 6, 3, 1, "hier pfad zum standing", "hier pfad zum shooting", "hier pfad zum running"){ }

	~UnitGunner(){ }

	//TODO: put this in base class, virtual static not possible
	static int UnitGunner::getCost()
	{
		return s_cost;
	}

	static int UnitGunner::getSpawnRate()
	{
		return s_spawnRate;
	}


};