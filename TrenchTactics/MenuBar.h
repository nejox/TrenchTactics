#pragma once
#include "SpriteText.h"
#include "Sprite.hpp"
#include "Player.h"
#include "MenuTile.h"

/**
* Menubar wrapper class
* controls all things concerning the menubar including buttons sprites setup and teardown
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

	void init();

	void updateMenuBar(GAMEPHASES::GAMEPHASE phase, shared_ptr<Player> activePlayer);

	void refreshMenuBar(shared_ptr<Player> activePlayer);


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
	void updateUnitStats(shared_ptr<Unit> unit)
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

	void initButtons(GAMEPHASES::GAMEPHASE phase);
	void deleteButtons();

	void deleteAllButtonDisplays();
	void resetAllButtonDisplays();

	void refreshAllButtonDisplays();

	void reInitButtons(GAMEPHASES::GAMEPHASE phase)
	{
		this->deleteButtons();
		this->initButtons(phase);
	}

	std::shared_ptr<vector<vector<std::shared_ptr<MenuTile>>>> getMenuBar()
	{
		return this->menuBar;
	}


private:
	const std::string slash = " / ";
	const std::string hp = "HP: ";
	const std::string ap = "AP: ";
	const std::string dmg = "DMG: ";
	const std::string rng = "RANGE: ";

	const int pixelToTileFactor = 64;

	std::shared_ptr<vector<vector<std::shared_ptr<MenuTile>>>> menuBar;
	std::shared_ptr<Sprite> activePlayerFlag;
	std::shared_ptr<Sprite> activePhaseToken;
	std::shared_ptr<SpriteText> activePhaseText;
	std::shared_ptr<SpriteText> phaseText;
	std::shared_ptr<SpriteText> money;
	std::shared_ptr<SpriteText> income;
	std::shared_ptr<SpriteText> unitCount;
	std::shared_ptr<SpriteText> unitHP;
	std::shared_ptr<SpriteText> unitAP;
	std::shared_ptr<SpriteText> unitDMG;
	std::shared_ptr<SpriteText> unitRange;

	MenuBar() {};
};
