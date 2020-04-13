#pragma once
#include "UnitBase.h"

class UnitGrenade : public UnitBase
{
public:

	static const int cost = 60;
	static const int spawnRate = 30;

	/// <summary>
	/// Instantiates a Grenade Unit with all base stats necessary
	/// </summary>
	UnitGrenade() : UnitBase(80, 50, 9, 5, 3, 1){ }

	~UnitGrenade(){ }

	//TODO: put this in base class, virtual static not possible
	static int UnitGrenade::getCost()
	{
		return cost;
	}

	static int UnitGrenade::getSpawnRate()
	{
		return spawnRate;
	}


};