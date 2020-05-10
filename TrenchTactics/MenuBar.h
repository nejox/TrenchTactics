#pragma once
#include "SpriteText.h"
#include "Sprite.hpp"
#include "Player.h"
#include "MenuTile.h"

/**
* 
*/
class MenuBar
{
public:

	MenuBar(const MenuBar&) = delete; 
	MenuBar& operator=(const MenuBar&) = delete;
	MenuBar(MenuBar&&) = delete;
	MenuBar& operator=(MenuBar&&) = delete;
	~MenuBar() {}

	static auto& instance() {
		static MenuBar menuBar;
		return menuBar;
	}


	/**
*set up Menubarbackground
*Initializes a MenuBar instance with fully configurated moneyToken unitCountTOken incomeToken phaseText
*initializes money, income, unitCount, activePhaseToken activePhaseText, activePlayer and sets positions
*initializes unit stats HP, AP, DMG
*/
	void init()
	{

		menuBarBackGround = make_shared<vector<vector<std::shared_ptr<MenuTile>>>>();
		setSizeMenuBar();
		initiateMenuTiles();

		moneyToken = make_shared<Sprite>();
		moneyToken->load("../Data/Sprites/Token/MONEY_TOKEN.bmp");
		moneyToken->setPos(27, 12 * 64 + 32);

		incomeToken = make_shared<Sprite>();
		incomeToken->load("../Data/Sprites/Token/INCOME_TOKEN.bmp");
		incomeToken->setPos(27, 13 * 64 + 32);

		unitCountToken = make_shared<Sprite>();
		unitCountToken->load("../Data/Sprites/Token/UNIT_COUNTER.bmp");
		unitCountToken->setPos((64 * 19 + 20), (12 * 64 + 32));

		activePlayerFlag = make_shared<Sprite>();
		activePlayerFlag->setPos(9 * 64 + 37, 12 * 64 + 11);

		activePhaseToken = make_shared<Sprite>();
		activePhaseToken->setPos((64 * 19 + 20), (13 * 64 + 32));

		activePhaseText = make_shared<SpriteText>(22);
		activePhaseText->setPos((64 * 20 + 20), (13 * 64 + 32));

		phaseText = make_shared<SpriteText>(22);
		phaseText->setPos((64 * 20 + 20), (13 * 64 + 50));
		phaseText->load("PHASE");

		money = make_shared<SpriteText>(40);
		money->setPos((64 + 27), (12 * 64 + 9 + 32));

		income = make_shared<SpriteText>(40);
		income->setPos((64 + 27), (13 * 64 + 9 + 32));

		unitCount = make_shared<SpriteText>(40);
		unitCount->setPos((64 * 20 + 20), (12 * 64 + 9 + 32));

		unitHP = make_shared<SpriteText>(25);
		unitHP->setPos((64 * 9 + 40), (64 * 13));

		unitAP = make_shared<SpriteText>(25);
		unitAP->setPos((64 * 9 + 40), (64 * 13 + 32));

		unitDMG = make_shared<SpriteText>(25);
		unitDMG->setPos((64 * 9 + 40), (64 * 14));
	}

	void updateMenuBar(GAMEPHASES::GAMEPHASE phase, shared_ptr<Player> activePlayer)
	{
		this->resetMenuBar();
		this->updateButtons(phase);
		this->updateTokens(activePlayer);
		this->updatePlayerStats(activePlayer);
	}

	void resetMenuBar();

	/**
	*renders the active players stats
	*Overloaded funtion
	*/
	void updatePlayerStats(shared_ptr<Player> activePlayer)
	{
		showPlayerStats(activePlayer);
	}	
	void showPlayerStats(shared_ptr<Player> activePlayer);
	
	/**
	*renders the active players stats and the currently active Units HP
	*Overloaded funtion
	*/
	void updateUnitStats( shared_ptr<Unit> unit)
	{
		resetUnitStats();
		showUnitStats(unit);
	}

	void resetUnitStats();
	void showUnitStats(shared_ptr<Unit>unit);

	void setSizeMenuBar();
	void initiateMenuTiles();
	std::shared_ptr<MenuTile> getMenuTileFromXY(int posX, int posY);

	void displayTokens(shared_ptr<Player> activePlayer);

	void updateTokens(shared_ptr<Player> activePlayer)
	{
		this->displayTokens(activePlayer);
	}

	SpriteButton* getRandomUnitButtonSprite(int rndNumber);
	void displayButtons(GAMEPHASES::GAMEPHASE phase);
	void deleteButtons();

	void updateButtons(GAMEPHASES::GAMEPHASE phase)
	{
		this->deleteButtons();
		this->displayButtons(phase);
	}

	std::shared_ptr<vector<vector<std::shared_ptr<MenuTile>>>> getMenuBarBackGround()
	{
		return this->menuBarBackGround;
	}


private:
	std::shared_ptr<vector<vector<std::shared_ptr<MenuTile>>>> menuBarBackGround;
	std::shared_ptr<Sprite> activePlayerFlag;
	std::shared_ptr<Sprite> activePhaseToken;
	std::shared_ptr<SpriteText> activePhaseText;
	std::shared_ptr<SpriteText> phaseText;
	std::shared_ptr<Sprite> moneyToken;
	std::shared_ptr<Sprite> incomeToken;
	std::shared_ptr<SpriteText> money;
	std::shared_ptr<SpriteText> income;
	std::shared_ptr<Sprite> unitCountToken;
	std::shared_ptr<SpriteText> unitCount;
	std::shared_ptr<SpriteText> unitHP;
	std::shared_ptr<SpriteText> unitAP;
	std::shared_ptr<SpriteText> unitDMG;

	MenuBar() {};
};
