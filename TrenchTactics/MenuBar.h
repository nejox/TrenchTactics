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
*Initializes a MenuBar instance with fully initialized moneyToken unitCountTOken incomeToken
*initializes money, income, unitCount, activePhase and sets positions
*
*/
	void init()
	{

		menuBarBackGround = make_shared<vector<vector<std::shared_ptr<MenuTile>>>>();
		setSizeMenuBar();
		initiateMenuTiles();
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
		deletePlayerStats();
		showPlayerStats(activePlayer);
	}	
	void showPlayerStats(shared_ptr<Player> activePlayer);
	void deletePlayerStats();
	
	/**
	*renders the active players stats and the currently active Units HP
	*Overloaded funtion
	*/
	void updateUnitStats( shared_ptr<Unit> unit)
	{
		deleteUnitStats();
		showUnitStats(unit);
	}
	void showUnitStats(shared_ptr<Unit>unit);
	void deleteUnitStats();

	void setSizeMenuBar();
	void initiateMenuTiles();
	std::shared_ptr<MenuTile> getMenuTileFromXY(int posX, int posY);

	void displayTokens(shared_ptr<Player> activePlayer);
	void deleteTokens();

	void updateTokens(shared_ptr<Player> activePlayer)
	{
		this->deleteTokens();
		this->displayTokens(activePlayer);
	}

	void displaySkipRoundButton();
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
	std::shared_ptr<Sprite> moneyToken;
	std::shared_ptr<Sprite> incomeToken;
	std::shared_ptr<SpriteText> money;
	std::shared_ptr<SpriteText> income;
	std::shared_ptr<Sprite> unitCountToken;
	std::shared_ptr<SpriteText> unitCount;
	std::shared_ptr<SpriteText> unitHP;

	MenuBar() {};
};
