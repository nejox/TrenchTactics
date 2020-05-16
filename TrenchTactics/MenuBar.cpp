#include "MenuBar.h"


void MenuBar::resetMenuBar()
{

//is this a workaround? is this just fantasy?
//tut erstmal was es soll, bisschen billige lösung, wird noch bisschen straffer gemacht aber reicht erstmal so

for (int x = 0; x < 3; x++)
{
	for (int y = 0; y < 3; y++)
	{
		this->menuBar.get()->at(x).at(y).get()->getSprite()->render(x * 64, y * 64);
	}
}

for (int x = 19; x < 22; x++)
{
	for (int y = 0; y < 3; y++)
	{
		this->menuBar.get()->at(x).at(y).get()->getSprite()->render(x * 64, y * 64);
	}
}
}
/**
* Displays Players current money, income and number of units 
*/
void MenuBar::showPlayerStats(shared_ptr<Player> activePlayer)
{

	money->load(std::to_string(activePlayer->getMoney()));
	money->render();

	income->load("+" + std::to_string(activePlayer->computeInterest())); 
	income->render();

	if (activePlayer->getUnitArray().empty())
	{
		unitCount->load((std::to_string(0)) + " / " + (std::to_string(ConfigReader::instance().getBalanceConf()->getMaxAmountUnits())));  
		unitCount->render();
	}

	else
	{
		unitCount->load(to_string((activePlayer->getUnitArray().size())) + " / " + (std::to_string(ConfigReader::instance().getBalanceConf()->getMaxAmountUnits())));
		unitCount->render();
	}

	
}


//is this a workaround? is this just fantasy?
//tut erstmal was es soll, bisschen billige lösung, wird noch bisschen straffer gemacht aber reicht erstmal so
void MenuBar::resetUnitStats()
{
	for (int x = 9; x < 13; x++)
	{
		for (int y = 1; y < 3; y++)
		{
				this->menuBar.get()->at(x).at(y).get()->getSprite()->render(x * 64, y * 64);
			
		}
	}
}


/**
* Displays units currentHp/MaxHp
*/
void MenuBar::showUnitStats(shared_ptr<Unit> unit)
{
	std::string hp = "HP: ";
	std::string slash = " / ";
	std::string ap = "AP: ";
	std::string dmg = "DMG: ";

	unitHP->load(hp + std::to_string(unit->getCurrentHP()) + slash + std::to_string(unit->getHp()));
	unitHP->render();

	unitAP->load(ap + std::to_string(unit->getCurrentAP()) + slash + std::to_string(unit->getAp()));
	unitAP->render();

	unitDMG->load(dmg + std::to_string(unit->getDmg()));
	unitDMG->render();
}




/**
 * get a menu tile based on a pixel position x and y
 * returns nullptr when not valid
 *
 * \param posX
 * \param posY
 * \return
 */


std::shared_ptr<MenuTile> MenuBar::getMenuTileFromXY(int posX, int posY) {
	//changing position from pixels to tiles
	posY = posY / 64 - 12;
	posX = posX / 64;

	if (posX > 21 || posX < 0) {
		return nullptr;
	}
	else if (posY > 3 || posY < 0) {
		return nullptr;
	}
	else {
		return this->getMenuBar().get()->at(posX).at(posY);
	}

}


/**
 * display necessary buttons based on phase.
 *
 * \param current gamephase
 */
void MenuBar::initButtons(GAMEPHASES::GAMEPHASE phase) {
	if (phase == GAMEPHASES::BUY) {


		for (int i = 0; i < 3; i++) {
			int rnd = std::rand() % 3;

			if (i == 0) {
				std::shared_ptr<Button> button1 = std::make_shared<Button>((Button::BUTTONTYPE)rnd);
				this->getMenuBar().get()->at(7).at(1).get()->setButton(button1);
			}
			else if (i == 1) {
				std::shared_ptr<Button> button2 = std::make_shared<Button>((Button::BUTTONTYPE)rnd);
				this->getMenuBar().get()->at(8).at(1).get()->setButton(button2);
			}
			else if (i == 2) {
				std::shared_ptr<Button> button3 = std::make_shared<Button>((Button::BUTTONTYPE)rnd);
				this->getMenuBar().get()->at(9).at(1).get()->setButton(button3);
			}

		}

		std::shared_ptr<Button> button4 = std::make_shared<Button>(Button::ADDUNIT);
		this->getMenuBar().get()->at(10).at(1).get()->setButton(button4);

		std::shared_ptr<Button> button5 = std::make_shared<Button>(Button::ADDUNIT);
		this->getMenuBar().get()->at(11).at(1).get()->setButton(button5);

		std::shared_ptr<Button> confirmButton = std::make_shared<Button>(Button::CONFIRM);
		this->getMenuBar().get()->at(13).at(1).get()->setButton(confirmButton);

		
		std::shared_ptr<Button> cancelButton = std::make_shared<Button>(Button::CANCEL);
		this->getMenuBar().get()->at(14).at(1).get()->setButton(cancelButton);
		

		std::shared_ptr<Button> rerollButton = std::make_shared<Button>(Button::REROLL);
		this->getMenuBar().get()->at(12).at(1).get()->setButton(rerollButton);


	}
	else if (phase == GAMEPHASES::MOVE || phase == GAMEPHASES::ATTACK)
	{
		//display buttons for next and previous unit
		std::shared_ptr<Button> previousUnitButton = std::make_shared<Button>(Button::PREVIOUSUNIT);
		std::shared_ptr<Button> nextUnitButton = std::make_shared<Button>(Button::NEXTUNIT);
	
		this->getMenuBar().get()->at(4).at(1).get()->setButton(previousUnitButton);
		this->getMenuBar().get()->at(5).at(1).get()->setButton(nextUnitButton);
	}

	//always display end phase and end turn buttons
	std::shared_ptr<Button> nextPhaseButton = std::make_shared<Button>(Button::NEXTPHASE);
	std::shared_ptr<Button> buttonEndTurn = std::make_shared<Button>(Button::ENDTURN);

	this->getMenuBar().get()->at(16).at(1).get()->setButton(nextPhaseButton);
	this->getMenuBar().get()->at(17).at(1).get()->setButton(buttonEndTurn);
}

/**
 *
 */
void MenuBar::deleteButtons() {
	for (int i = 4; i < 15; i = i++) {
		this->getMenuBar().get()->at(i).at(1).get()->removeButton();
	}
}

void MenuBar::deleteAllButtonDisplays() {
	for (int i = 4; i < 15; i = i++) {
		this->getMenuBar().get()->at(i).at(1).get()->removeButtonDisplay();
	}
}


void MenuBar::refreshAllButtonDisplays()
{
	deleteAllButtonDisplays();

	for (int i = 4; i < 15; i = i++) {
		if (getMenuBar().get()->at(i).at(1).get()->getButton() != nullptr) {
			getMenuBar().get()->at(i).at(1).get()->getButton()->update();
		}
	}
}

void MenuBar::resetAllButtonDisplays()
{
	deleteAllButtonDisplays();

	for (int i = 4; i < 15; i = i++) {
		if (getMenuBar().get()->at(i).at(1).get()->getButton() != nullptr) {
			getMenuBar().get()->at(i).at(1).get()->getButton()->setPressed(false);
			getMenuBar().get()->at(i).at(1).get()->getButton()->update();
		}
	}
}



void MenuBar::displayTokens(shared_ptr<Player> activePlayer)
{
	if (activePlayer->getColor())
	{
		activePlayerFlag->load("../Data/Sprites/Token/R_FLAG_SMOL.bmp");
	}
	else
	{
		activePlayerFlag->load("../Data/Sprites/Token/B_FLAG_SMOL.bmp");
	}

	if (activePlayer->getCurrentPhase() == GAMEPHASES::BUY)
	{
		activePhaseToken->load("../Data/Sprites/Token/BUYPHASE_TOKEN.bmp");
		activePhaseText->load("BUY");
	}
	else if (activePlayer->getCurrentPhase() == GAMEPHASES::MOVE)
	{
		activePhaseToken->load("../Data/Sprites/Token/MOVEPHASE_TOKEN.bmp");
		activePhaseText->load("MOVE");
		
	}
	else
	{
		activePhaseToken->load("../Data/Sprites/Token/ATTACKPHASE_TOKEN.bmp");
		activePhaseText->load("ATTACK");
		
	}
		activePlayerFlag->render();
		activePhaseToken->render();
		activePhaseText->render();
		phaseText->render();
	
}


/**
 * Function to set up the MenuTiles at gamestart.
 *
 */
void MenuBar::initiateMenuTiles()
{
	for (vector<vector<std::shared_ptr<MenuTile>>>::iterator xIter = this->menuBar->begin(); xIter != this->menuBar->end(); ++xIter) {
		for (vector<std::shared_ptr<MenuTile>>::iterator yIter = xIter->begin(); yIter != xIter->end(); ++yIter) {

			// create MenuTile as shared pointer 
			std::shared_ptr<MenuTile> tmpMenuTilePointer = std::make_shared<MenuTile>();

			// create Sprite and load menuBar file with all individual sprites
			Sprite* terrainSprite = new Sprite();
			terrainSprite->load("../Data/Sprites/Token/MENUE_BAR.bmp");

			// set pos where sprite shall be renderd
			terrainSprite->setPos((xIter - this->menuBar->begin()) * 64, (yIter - xIter->begin()) * 64 + 12 * 64);
			tmpMenuTilePointer->setSprite(terrainSprite);
			tmpMenuTilePointer->setPos((xIter - this->menuBar->begin()) * 64, (yIter - xIter->begin()) * 64 + 12 * 64);

			// tell render function to only render the specific 64*64 slice of whole menu
			tmpMenuTilePointer->getSprite()->render((xIter - this->menuBar->begin()) * 64, (yIter - xIter->begin()) * 64);
			*yIter = tmpMenuTilePointer;
		}
	}
}

/**
 * Sets the size of the menubar at the gamestart.
 *
 */
void MenuBar::setSizeMenuBar()
{
	this->menuBar->resize(22);

	for (vector<vector<shared_ptr<MenuTile>>>::iterator menuCol = this->menuBar->begin(); menuCol != this->menuBar->end(); ++menuCol)
	{
		menuCol->resize(3);
	}

}
