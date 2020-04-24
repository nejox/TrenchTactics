#include "Unit.h"
#include "DeathEvent.h"


void Unit::attack(std::shared_ptr<Unit> target)
{
	target->changeHP(m_dmg);
	if (target->getCurrentHP() <= 0)
	{
		DeathEvent* deathEvent = new DeathEvent(target);
	}

	updateAP(m_apCostAttack);
}

void Unit::attack(Headquarter* target)
{
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
	//TO DO
	updateAP(m_apCostMove);
}

