#include "Unit.h"


void Unit::attack(Unit* target)
{
	//TO DO: hier vielleicht shooting animation rendern 
	target->changeHP(m_dmg);
	updateAP(m_apCostAttack);
}

void Unit::attack(Headquarter* target)
{
	//TO DO: hier vielleicht shooting animation rendern 
	target->changeHP(m_dmg);
	updateAP(m_apCostAttack);
}

void Unit::changeHP(int damage)
{
	m_currentHP -= damage;
}

void Unit::resetAP()
{
	m_currentAP = m_ap;
}


void Unit::updateAP(int cost)
{
	m_currentAP -= cost;
}

void Unit::move()
{
	//TO DO
	updateAP(m_apCostMove);
}

