#pragma once
#include "HQ.h"

/// <summary>
/// Baseclass for units
/// </summary>
class UnitBase
{
	
protected: 
	//can´t be instantiated
	UnitBase();

	UnitBase(int maxHP, int damage, int weaponRange, int maxAP, int attackAP, int moveAP) :
		m_maxHP{maxHP} ,
		m_currentHP{ maxHP },
		m_damage{damage},
		m_weaponRange{weaponRange},
		m_maxAP{maxAP},
		m_currentAP{maxAP},
		m_attackAP{attackAP},
		m_moveAP{moveAP} { }

	// no const values in case of exp-system
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
	void attack(HQ* target);
	void move();
	void updateAP(int cost);
	void resetAP();

	int getCurrentHP();
	void setCurrentHP(int currentHP);

	int getCurrentAP();
	void setCurrentAP(int currentAP);






};
