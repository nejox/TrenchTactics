#include "UnitBase.h"


void UnitBase::attack(UnitBase* target)
{
	//TO DO: hier vielleicht shooting animation rendern 
	target->changeHP(m_damage);
	updateAP(m_attackAP);
}

void UnitBase::attack(HQ* target)
{
	//TO DO: hier vielleicht shooting animation rendern 
	target->changeHP(m_damage);
	updateAP(m_attackAP);
}

void UnitBase::changeHP(int damage)
{
	m_currentHP -= damage;
}

void UnitBase::resetAP()
{
	m_currentAP = m_maxAP;
}


void UnitBase::updateAP(int cost)
{
	m_currentAP -= cost;
}

void UnitBase::move()
{
	//TO DO
	updateAP(m_moveAP);
}

