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

	int m_colorRed;
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
	std::string m_spriteFilePathStanding;
	std::string m_spriteFilePathShooting;
	std::string m_spriteFilePathRunning;

public:

	enum UnitType {
		CC,
		GUNNER,
		GRENADE
	};



	Unit(UnitType unittype, bool colorRed) {

		std::shared_ptr<UnitConf> uc = ConfigReader::instance().getUnitConf(unittype);
		m_colorRed = colorRed;

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

		if (colorRed) {
			 m_spriteFilePathStanding = uc->getSpriteFilePathStandingRed();
			 m_spriteFilePathShooting = uc->getSpriteFilePathShootingRed();
			 m_spriteFilePathRunning = uc->getSpriteFilePathRunningRed();
		}
		else {
			m_spriteFilePathStanding = uc->getSpriteFilePathStandingBlue();
			m_spriteFilePathShooting = uc->getSpriteFilePathShootingBlue();
			m_spriteFilePathRunning = uc->getSpriteFilePathRunningBlue();
		}

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
	void attack(std::shared_ptr<Unit> target);
	void attack(Headquarter* target);
	void move();
	void updateAP(int cost);
	void resetAP();

	int getCurrentHP()
	{
		return this->m_currentHP;
	}

	void setCurrentHP(int currentHP)
	{
		m_currentHP = currentHP;
	}

	int getCurrentAP()
	{
		return this->m_currentAP;
	}

	void setCurrentAP(int currentAP)
	{
		m_currentAP = currentAP;
	}

	bool getColorRed()
	{
		return m_colorRed;
	}

	void setColorRed(bool colorRed)
	{
		this->m_colorRed = colorRed;
	}
	int getRange() {
		return this->m_range;
	}


};