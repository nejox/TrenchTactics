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



/**
 * Base unit class that holds all information concerning a unit like health, cost or all spritefilepaths.
 */
class Unit : public std::enable_shared_from_this<Unit>
{
public:

	/**
	 * Initializes Unit type with all values from config.
	 *
	 * \param unittype the type of unit that will be created
	 * \param colorRed specifies which player is the owner of the new unit and selects the right sprites based on this bool
	 */
	Unit(TYPES::UnitType unittype, bool colorRed);

private:
	Unit() = delete;

	int m_ID;
	int m_colorRed;
	int m_hp;
	int m_currentHP;
	int m_range;
	int m_cost;
	int m_ap;
	int m_currentAP;
	int m_dmg;
	int m_apCostAttack;
	int m_movementRange;
	int m_apCostTrench;
	int m_apCostMove;
	int m_spawnProbability;
	int m_level;
	std::string m_name;
	std::shared_ptr<SpriteUnit>m_sprite;
	std::shared_ptr<SpriteHealthBar>m_spriteHealthBar;
	STATES::UNITSTATE m_state;

public:


	~Unit() {};


	bool changeHP(int damage);
	void attack(std::shared_ptr<Unit> target, bool cover);
	void attack(std::shared_ptr< Headquarter> target);
	void move();
	void updateAP(int cost);
	void resetAP();

	/**
	*changes the stats with a level up
	*/
	void levelUp();

	/**
	 * renders unit dependent on given state.
	 *
	 * \param state
	 */
	void update(STATES::UNITSTATE state);

	/**
	 * renders unit dependent on current state.
	 *
	 */
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

	int getLevel()
	{
		return this->m_level;
	}

	void setLevel(int level)
	{
		m_level = level;
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

	void reduceAp(int cost) {
		this->m_currentAP -= cost;
	}

	int getDmg()
	{
		return this->m_dmg;
	}

	int getCost()
	{
		return this->m_cost;
	}

	int getMovementRange()
	{
		return this->m_movementRange;
	}

	int getID()
	{
		return this->m_ID;
	}

	int getApCostTrench() {
		return this->m_apCostTrench;
	}

	int getApCostMove() {
		return this->m_apCostMove;
	}


};