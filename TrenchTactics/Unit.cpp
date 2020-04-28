#include "Unit.h"
#include "DeathEvent.h"


/**
 *
 *
 * \param target
 */
void Unit::attack(std::shared_ptr<Unit> target)
{
	//this->setState(SHOOTING);
	target->changeHP(m_dmg);
	if (target->getCurrentHP() <= 0)
	{
		DeathEvent* deathEvent = new DeathEvent(target);
	}

	updateAP(m_apCostAttack);

}

/**
 *
 *
 * \param target
 */
void Unit::attack(Headquarter* target)
{
	//this->setState(SHOOTING);
	target->changeHP(m_dmg);
	updateAP(m_apCostAttack);
}

/**
 *
 *
 * \param damage
 */
void Unit::changeHP(int damage)
{
	m_currentHP -= damage;

	if (this->getCurrentHP() <= 0)
	{
		DeathEvent* deathEvent = new DeathEvent(this->getptr());
	}
}

/**
 *
 *
 */
void Unit::resetAP()
{
	m_currentAP = m_ap;
}

void Unit::update(STATES::UNITSTATE state)
{
	m_sprite->render(state);
}


/**
 *
 *
 * \param cost
 */
void Unit::updateAP(int cost)
{
	m_currentAP -= cost;
}

/**
 *
 *
 */
void Unit::move()
{
	//this->setState(RUNNING);
	//TO DO
	updateAP(m_apCostMove);
}

