#include "Headquarter.h"
#include "EventBus.h"


void Headquarter::changeHP(int damage)
{
	m_currentHP -= damage;

	if (this->getCurrentHP() <= 250 && this->getCurrentHP() > 0)
	{
		this->setDamaged(true);
	}

	if (this->getCurrentHP() <= 0)
	{
		EventBus::instance().publish(new GameEndEvent(this->getColorRed()));
	}
}


