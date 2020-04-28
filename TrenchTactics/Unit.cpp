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

<<<<<<< HEAD
void Unit::update(STATES::UNITSTATE state)
{
	m_sprite->render(state);
}


=======
>>>>>>> 7a28419fc7cc51e325b866aeb0d6f6993a2c3b5f
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

