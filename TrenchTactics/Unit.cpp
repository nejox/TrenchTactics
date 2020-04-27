#include "Unit.h"
#include "DeathEvent.h"
#include "Timer.hpp"


void Unit::attack(std::shared_ptr<Unit> target)
{
	this->setState(SHOOTING);
	target->changeHP(m_dmg);
	if (target->getCurrentHP() <= 0)
	{
		DeathEvent* deathEvent = new DeathEvent(target);
	}

	updateAP(m_apCostAttack);
	
}

void Unit::attack(Headquarter* target)
{
	this->setState(SHOOTING);
	target->changeHP(m_dmg);
	updateAP(m_apCostAttack);
}

void Unit::changeHP(int damage)
{
	m_currentHP -= damage;

	if (this->getCurrentHP() <= 0)
	{
		DeathEvent* deathEvent = new DeathEvent(this->getptr());
	}
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
	this->setState(RUNNING);
	//TO DO
	updateAP(m_apCostMove);
}

