#include "Unit.h"
#include "DeathEvent.h"

/**
 *
 *
 * \param target
 */
void Unit::attack(std::shared_ptr<Unit> target)
{
    this->m_state = STATES::UNITSTATE::SHOOTING;
	target->changeHP(m_dmg);

	updateAP(m_apCostAttack);

}

/**
 *
 *
 * \param target
 */
void Unit::attack(std::shared_ptr<Headquarter> target)
{
    this->m_state = STATES::UNITSTATE::SHOOTING;
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

	if (m_currentHP <= 0)
	{
	    EventBus::instance().publish( new DeathEvent(this->getptr()));
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

void Unit::update() {
    m_state = m_sprite->render(m_state);
}

void Unit::setState(STATES::UNITSTATE state)
{
    this->m_state = state;
}

STATES::UNITSTATE Unit::getState()
{
    return this->m_state;
}

void Unit::update(STATES::UNITSTATE state)
{
    m_state = m_sprite->render(state);
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

