#pragma once
#include "Headquarter.h"
#include "Sprite.hpp"
#include "UnitConf.h"
#include "ConfigReader.h"
#include "EventBus.h"
#include "Event.h"
#include "SpriteUnit.h"

/// <summary>
/// Baseclass for units
/// </summary>
class Unit: std::enable_shared_from_this<Unit>
{
public:

	enum UnitType {
		CC,
		GUNNER,
		GRENADE
	};

	enum UnitState {
		STANDING,
		SHOOTING,
		RUNNING
	};



	Unit(UnitType unittype, bool colorRed) {

		m_colorRed = colorRed;
		m_state = STANDING;

		m_hp = ConfigReader::instance().getUnitConf(unittype)->getHp();
		m_currentHP = ConfigReader::instance().getUnitConf(unittype)->getHp();
		m_range = ConfigReader::instance().getUnitConf(unittype)->getRange();
		m_cost = ConfigReader::instance().getUnitConf(unittype)->getCost();
		m_ap = ConfigReader::instance().getUnitConf(unittype)->getAp();
		m_currentAP = ConfigReader::instance().getUnitConf(unittype)->getAp();
		m_dmg = ConfigReader::instance().getUnitConf(unittype)->getDmg();
		m_apCostAttack = ConfigReader::instance().getUnitConf(unittype)->getApCostAttack();
		m_apCostMove = ConfigReader::instance().getUnitConf(unittype)->getApCostMove();
		m_apCostTrench = ConfigReader::instance().getUnitConf(unittype)->getApCostTrench();
		m_spawnProbability = ConfigReader::instance().getUnitConf(unittype)->getSpawnProbability();
		m_name = ConfigReader::instance().getUnitConf(unittype)->getName();

		if (colorRed) {
			 m_spriteFilePathStanding = ConfigReader::instance().getUnitConf(unittype)->getSpriteFilePathStandingRed();
			 m_spriteFilePathShooting = ConfigReader::instance().getUnitConf(unittype)->getSpriteFilePathShootingRed();
			 m_spriteFilePathRunning = ConfigReader::instance().getUnitConf(unittype)->getSpriteFilePathRunningRed();
		}
		else {
			m_spriteFilePathStanding = ConfigReader::instance().getUnitConf(unittype)->getSpriteFilePathStandingBlue();
			m_spriteFilePathShooting = ConfigReader::instance().getUnitConf(unittype)->getSpriteFilePathShootingBlue();
			m_spriteFilePathRunning = ConfigReader::instance().getUnitConf(unittype)->getSpriteFilePathRunningBlue();
		}

		spriteUnit = make_shared<SpriteUnit>();

	}

private:
	Unit() = delete;

	UnitState m_state;
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
	std::shared_ptr<SpriteUnit>spriteUnit;

public:


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

	/// <summary>
	/// renders unit dependent on current state
	/// </summary>
	void render() {
		if (this->m_state == STANDING)
		{
			spriteUnit->setAnimation(m_spriteFilePathStanding);
		}

		if (this->m_state == SHOOTING)
		{
			spriteUnit->setAnimation(m_spriteFilePathShooting);
		}

		if (this->m_state == RUNNING)
		{
			spriteUnit->setAnimation(m_spriteFilePathRunning);
		}

		spriteUnit->render();
	}

	std::shared_ptr<Unit> getptr() {
		return shared_from_this();
	}

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

	int getState()
	{
		return this->m_state;
	}

	void setState(Unit::UnitState state)
	{
		this->m_state = state;
	}


};