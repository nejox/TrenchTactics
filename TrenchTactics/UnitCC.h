#pragma once
#include "UnitBase.h"


class UnitCC : public UnitBase
{
private:
	static const int s_cost = 60;
	static const int s_spawnRate = 30;



public:

	/// <summary>
	/// Instantiates a CC Unit with all base stats necessary
	/// </summary>
	//TO DO: wenn config da, werte aus config holen 
	UnitCC() : UnitBase(130, 100, 3, 8, 4, 1,"hier pfad zum standing", "hier pfad zum shooting", "hier pfad zum running") { }
	
	~UnitCC() { }

	//TODO: put this in base class or where it belongs, virtual static not possible
	static int UnitCC::getCost()
	{
		return s_cost;
	}

	static int UnitCC::getSpawnRate()
	{
		return s_spawnRate;
	}

	
	




};