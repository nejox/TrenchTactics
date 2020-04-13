#pragma once
#include "UnitBase.h"

class UnitGunner : public UnitBase
{
public:

	static const int cost = 50;
	static const int spawnRate = 40;

	/// <summary>
	/// Instantiates a Gunner Unit with all base stats necessary
	/// </summary>
	UnitGunner() : UnitBase(100, 80, 6, 6, 3, 1){ }

	~UnitGunner(){ }

	//TODO: put this in base class, virtual static not possible
	static int UnitGunner::getCost()
	{
		return cost;
	}

	static int UnitGunner::getSpawnRate()
	{
		return spawnRate;
	}


};