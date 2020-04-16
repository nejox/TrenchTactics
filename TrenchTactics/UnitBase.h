#pragma once
#include "Headquarter.h"
#include "Sprite.hpp"

/// <summary>
/// Baseclass for units
/// </summary>
class UnitBase
{

protected:
	//can´t be instantiated
	UnitBase() = delete;

	UnitBase(int maxHP, int damage, int weaponRange, int maxAP, int attackAP, int moveAP, std::string standingPath, std::string shootingPath, std::string runningPath) :
		m_maxHP{ maxHP },
		m_currentHP{ maxHP },
		m_damage{ damage },
		m_weaponRange{ weaponRange },
		m_maxAP{ maxAP },
		m_currentAP{ maxAP },
		m_attackAP{ attackAP },
		m_moveAP{ moveAP },
		pstanding{ new CSprite() },
		pshooting{ new CSprite() },
		prunning{ new CSprite() }
	{
		//TO DO: problem: verschiedene Spieler, muss lösung her an dieser stelle verschiedene sprites zu laden
		//TO DO2: Load ist falsche funktion, kann keine animierten sprites laden, mit anderen besprechen ob die wieder rein soll
		//TO DO3: irgendwie sieht das mit der methode im kostruktor auch nicht aus, alternativen überdenken
		pstanding->Load(standingPath);
		pshooting->Load(shootingPath);
		prunning->Load(runningPath);
	}

	// no const values in case of exp-system
	//TO DO: drüber nachdenken ob CSprite nicht const gemacht werden sollte oder ob an anderer stelle nicht besser
	CSprite* pstanding;
	CSprite* pshooting;
	CSprite* prunning;
	int m_maxHP;
	int m_currentHP;
	int m_damage;
	int m_weaponRange;
	int m_maxAP;
	int m_currentAP;
	int m_attackAP;
	int m_moveAP;
	//rect sprite;

public:
	virtual ~UnitBase() {};


	void changeHP(int damage);
	void attack(UnitBase* target);
	void attack(Headquarter* target);
	void move();
	void updateAP(int cost);
	void resetAP();

	int UnitBase::getCurrentHP()
	{
		return m_currentHP;
	}

	void UnitBase::setCurrentHP(int currentHP)
	{
		m_currentHP = currentHP;
	}

	int UnitBase::getCurrentAP()
	{
		return m_currentAP;
	}

	void UnitBase::setCurrentAP(int currentAP)
	{
		m_currentAP = currentAP;
	}






};