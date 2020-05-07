#include "MenuBar.h"

/**
* Displays Players current money and number of units 
*/
void MenuBar::showPlayerStats(shared_ptr<Player> activePlayer)
{
	moneyToken->render();

	money->load(std::to_string(activePlayer->getMoney()));
	money->render();

	unitCountToken->render();

	unitCount->load((std::to_string(activePlayer->getUnitArray().size())));
	unitCount->render();
}
/**
* Displays units currentHp/MaxHp
*/
void MenuBar::showUnitStats(shared_ptr<Unit> unit)
{
	unitHP->load((const char*)(unit->getCurrentHP() + " / " + unit->getHp()));
	unitHP->render();
}
