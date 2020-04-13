#include "UnitBase.h"


void UnitBase::attack(UnitBase* target)
{
	target->changeHP(m_damage);
	updateAP(m_attackAP);
}

void UnitBase::attack(HQ* target)
{
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