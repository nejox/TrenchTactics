#pragma once
#include "Headquarter.h"
#include "Sprite.hpp"
#include "UnitConf.h"
#include "ConfigReader.h"
#include "EventBus.h"
#include "Event.h"

/// <summary>
/// Baseclass for units
/// </summary>
class Unit
{
private:
	Unit() = delete;

	int m_hp;
	int m_currentHP;
	int m_range;
	int m_cost;
	int m_ap;
	int m_currentAP;
	int m_dmg;
	int m_apCostAttack;
	int m_apCostMove;
	int m_apCostTrench;
	int m_spawnProbability;
	std::string m_name;
	std::string m_spriteFilePath;

public:

	enum UnitType {
		CC = 0,
		GUNNER = 1,
		GRENADE = 2
	};
	

	Unit(UnitType unittype) {

		UnitConf* uc = ConfigReader::instance().getUnitConf(unittype);
		
		m_hp = uc->getHp();
		m_currentHP = uc->getHp();
		m_range = uc->getRange();
		m_cost = uc->getCost();
		m_ap = uc->getAp();
		m_currentAP = uc->getAp();
		m_dmg = uc->getDmg();
		m_apCostAttack = uc->getApCostAttack();
		m_apCostMove = uc->getApCostMove();
		m_apCostTrench = uc->getApCostTrench();
		m_spawnProbability = uc->getSpawnProbability();
		m_name = uc->getName();

		//if(EventBus::instance().activePlayer->getColour()) m_spriteFilePath = uc->getSpriteFilePathRed();
		//else m_spriteFilePath = uc->getSpriteFilePathBlue();
	}

	
	
	 ~Unit() {};
	 /*
	 TO DO: checken ob ich den kram brauch wenn ich nur auf ein singleton zeige
	 Unit(const Unit&);
	 Unit& operator=(const Unit&);
	 Unit(Unit&&);
	 Unit& operator=(Unit&&);
	 */

	void changeHP(int damage);
	void attack(Unit* target);
	void attack(Headquarter* target);
	void move();
	void updateAP(int cost);
	void resetAP();

	int Unit::getCurrentHP()
	{
		return this->m_currentHP;
	}

	void Unit::setCurrentHP(int currentHP)
	{
		m_currentHP = currentHP;
	}

	int Unit::getCurrentAP()
	{
		return this->m_currentAP;
	}

	void Unit::setCurrentAP(int currentAP)
	{
		m_currentAP = currentAP;
	}

	std::string Unit::getSpriteFilePath()
	{
		return m_spriteFilePath;
	}
	


};
