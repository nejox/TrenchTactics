#pragma once
#include "SpriteText.h"
#include "Sprite.hpp"
#include "Player.h"

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
*Initializes a MenuDisplayer instance with fully initialized moneyToken and unitCountTOken
*initializes money and unitCount and sets positions
*/
	void init()
	{
		moneyToken = make_shared<Sprite>();
		moneyToken->load("../Data/Sprites/Token/MONEY_TOKEN.bmp");
		moneyToken->setPos(27, 13 * 64);

		money = make_shared<SpriteText>(40);
		//money->setPos((64 + 27), (13 * 64 + 9));

		unitCountToken = make_shared<Sprite>();
		unitCountToken->load("../Data/Sprites/Token/UNIT_COUNTER.bmp");
		unitCountToken->setPos((64 * 19 + 20), (13 * 64));

		unitCount = make_shared<SpriteText>(40);
		//unitCount->setPos((64 * 20 + 20), (13 * 64 + 9));

		unitHP = make_shared<SpriteText>(25);
		//unitHP->setPos((64 * 11), (64 * 13));
	}

	

	/**
	*renders the active players stats
	*Overloaded funtion
	*/
	void render(shared_ptr<Player> activePlayer)
	{
		showPlayerStats(activePlayer);
	}	
	/**
	*renders the active players stats and the currently active Units HP
	*Overloaded funtion
	*/
	void render(shared_ptr<Player> activePlayer, shared_ptr<Unit> unit)
	{
		showPlayerStats(activePlayer);
		showUnitStats(unit);
	}

	void showPlayerStats(shared_ptr<Player> activePlayer);
	void showUnitStats(shared_ptr<Unit>unit);


private:
	std::shared_ptr<Sprite> moneyToken;
	std::shared_ptr<SpriteText> money;
	std::shared_ptr<Sprite> unitCountToken;
	std::shared_ptr<SpriteText> unitCount;
	std::shared_ptr<SpriteText> unitHP;

	MenuBar() {};
};
