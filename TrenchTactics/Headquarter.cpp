#include "Headquarter.h"
#include "EventBus.h"


/**
 * change hp of the headquarter and update its current state based on the curren health.
 * If health at or below zero raises GameEndEvent.
 *
 * \param damage the amount of damage dealt to the headquarter
 */
void Headquarter::changeHP(int damage)
{
	m_currentHP -= damage;

	if (this->getCurrentHP() <= 250 && this->getCurrentHP() > 0)
	{
		this->setDamaged(true);
		this->m_spriteHQ->render(this->getDamaged());
	}

	if (this->getCurrentHP() <= 0)
	{
		EventBus::instance().publish(new GameEndEvent(this->getColorRed()));
	}
}


