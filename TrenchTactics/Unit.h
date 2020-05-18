#pragma once
#include "Headquarter.h"
#include "Sprite.hpp"
#include "UnitConf.h"
#include "ConfigReader.h"
#include "EventBus.h"
#include "Event.h"
#include "SpriteUnit.h"
#include "SpriteHealthBar.h"
#include "UnitTypes.h"



/// <summary>
/// Baseclass for units
/// </summary>
class Unit : public std::enable_shared_from_this<Unit>
{
public:

	/// <summary>
	/// Initializes Unit type with all values from config
	/// </summary>
	/// <param name="unittype"></param>
	/// <param name="colorRed"></param>
	Unit(TYPES::UnitType unittype, bool colorRed) {

		m_colorRed = colorRed;

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
		m_sprite = make_shared<SpriteUnit>(colorRed, unittype);
		m_spriteHealthBar = make_shared<SpriteHealthBar>(colorRed);
		m_state = STATES::UNITSTATE::STANDING_NEUTRAL;

	}

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
	std::shared_ptr<SpriteUnit>m_sprite;
	std::shared_ptr<SpriteHealthBar>m_spriteHealthBar;
	STATES::UNITSTATE m_state;

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
	void attack(std::shared_ptr< Headquarter> target);
	void move();
	void updateAP(int cost);
	void resetAP();

	/// <summary>
	/// renders unit dependent on given state
	/// </summary>
	/// 
	void update(STATES::UNITSTATE state);

	/// <summary>
	/// renders unit dependent on current state
	/// </summary>
	/// 
	void update();

	std::shared_ptr<Unit> getptr() {
		return shared_from_this();
	}

	void setState(STATES::UNITSTATE state);
	STATES::UNITSTATE getState();

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

	std::shared_ptr<SpriteUnit> getSprite() {
		return m_sprite;
	}

	std::shared_ptr<SpriteHealthBar> getSpriteHealthBar() {
		return m_spriteHealthBar;
	}

	void setSprite(std::shared_ptr<SpriteUnit> sprite) {
		m_sprite = sprite;
	}

	std::string getName()
	{
		return this->m_name;
	}

	int getHp() {
		return this->m_hp;
	}

	int getApCostAttack() {
		return this->m_apCostAttack;
	}
	int getAp() {
		return this->m_ap;
	}

	int getDmg()
	{
		return this->m_dmg;
	}

	int getCost()
	{
		return this->m_cost;
	}
};