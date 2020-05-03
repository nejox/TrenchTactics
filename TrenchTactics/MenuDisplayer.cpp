#include "MenuDisplayer.h"

void MenuDisplayer::showPlayerStats(Player* activePlayer)
{
	moneyToken->render();

	money->load((const char*) activePlayer->getMoney());
	money->render();

	unitCountToken->render();

	unitCount->load((const char*) activePlayer->getUnitArray().size());
	unitCount->render();
}

void MenuDisplayer::showUnitStats(Unit* unit)
{
	unitHP->load((const char*)(unit->getCurrentHP() + " / " + unit->getHp()));
	unitHP->render();
}
