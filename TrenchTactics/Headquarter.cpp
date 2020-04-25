#include "Headquarter.h"



void Headquarter::changeHP(int damage)
{
	m_currentHP -= damage;

	if (this->getCurrentHP() <= 250 && this->getCurrentHP() > 0)
	{
		this->setDamaged(true);
	}

	if (this->getCurrentHP() <= 0)
	{
		GameEndEvent* gameEndEvent = new GameEndEvent(this->getColorRed());
	}
}


