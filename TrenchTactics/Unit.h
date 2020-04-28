#pragma once
#include "Headquarter.h"
#include "Sprite.hpp"
#include "UnitConf.h"
#include "ConfigReader.h"
#include "EventBus.h"
#include "Event.h"
#include "SpriteUnit.h"
#include "Timer.hpp"

/// <summary>
/// Baseclass for units
/// </summary>
class Unit : std::enable_shared_from_this<Unit>
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


	/// <summary>
	/// Initializes Unit type with all values from config
	/// </summary>
	/// <param name="unittype"></param>
	/// <param name="colorRed"></param>
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
			m_spriteStanding = std::make_shared<SpriteUnit>(ConfigReader::instance().getUnitConf(unittype)->getSpriteFilePathStandingNeutralRed());
			m_spriteShooting = std::make_shared<SpriteUnit>(ConfigReader::instance().getUnitConf(unittype)->getSpriteFilePathShootingRed());
			m_spriteRunning = std::make_shared<SpriteUnit>(ConfigReader::instance().getUnitConf(unittype)->getSpriteFilePathRunningRed());
		}
		else {
			m_spriteStanding = std::make_shared<SpriteUnit>(ConfigReader::instance().getUnitConf(unittype)->getSpriteFilePathStandingNeutralBlue());
			m_spriteShooting = std::make_shared<SpriteUnit>(ConfigReader::instance().getUnitConf(unittype)->getSpriteFilePathShootingBlue());
			m_spriteRunning = std::make_shared<SpriteUnit>(ConfigReader::instance().getUnitConf(unittype)->getSpriteFilePathRunningBlue());
		}



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
	std::shared_ptr<SpriteUnit>m_spriteStanding;
	std::shared_ptr<SpriteUnit>m_spriteShooting;
	std::shared_ptr<SpriteUnit>m_spriteRunning;

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
	/// 
	void update() {

		if (this->m_state == SHOOTING)
		{
			//TO DO: den kram in die spriteUnit klasse schmeißen
			if (this->m_spriteShooting->getCurrentPhase() == 2 * (this->m_spriteShooting->getNumFrames()))
			{
				this->setState(STANDING);
				m_spriteShooting->setCurrentPhase(0);
			}
			else
			{
				m_spriteStanding->render();
			}

		}

		if (this->m_state == RUNNING)
		{
			m_spriteStanding->render();
		}

		if (this->m_state == STANDING)
		{
			m_spriteStanding->render();
		}

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