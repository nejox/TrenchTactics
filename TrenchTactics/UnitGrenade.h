#pragma once
#include "UnitBase.h"

class UnitGrenade : public UnitBase
{

private:
	static const int s_cost = 60;
	static const int s_spawnRate = 30;

public:
	/// <summary>
	/// Instantiates a Grenade Unit with all base stats necessary
	/// </summary>
	UnitGrenade() : UnitBase(80, 50, 9, 5, 3, 1, "hier pfad zum standing", "hier pfad zum shooting", "hier pfad zum running"){ }

	~UnitGrenade(){ }

	//TODO: put this in base class or where it belongs, virtual static not possible
	static int UnitGrenade::getCost()
	{
		return s_cost;
	}

	static int UnitGrenade::getSpawnRate()
	{
		return s_spawnRate;
	}


};