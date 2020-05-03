#pragma once
#include "SpriteText.h"
#include "Sprite.hpp"
#include "Player.h"


class MenuDisplayer
{
public:
	/**
	*Initializes a MenuDisplayer instance with fully initialized moneyToken and unitCountTOken 
	*initializes money and unitCount and sets positions
	*/

	MenuDisplayer(const MenuDisplayer&) = delete; 
	MenuDisplayer& operator=(const MenuDisplayer&) = delete;
	MenuDisplayer(MenuDisplayer&&) = delete;
	MenuDisplayer& operator=(MenuDisplayer&&) = delete;

	static auto& instance() {
		static MenuDisplayer menuDisplayer;
		return menuDisplayer;
	}

	MenuDisplayer init()
	{
		moneyToken = make_shared<Sprite>();
		moneyToken->load("../Data/Sprites/Token/MONEY_TOKEN.bmp");
		unitCountToken->setPos(7, 14 * 64);

		money = make_shared<SpriteText>(10);
		money->setPos((64 + 7), (14 * 64));

		unitCountToken = make_shared<Sprite>();
		unitCountToken->load("../Data/Sprites/Token/UNIT_COUNTER.bmp");
		unitCountToken->setPos((64 * 20), (14 * 64));

		unitCount = make_shared<SpriteText>(10);
		unitCount->setPos((64 * 21), (14 * 64));

		unitHP = make_shared<SpriteText>(10);
		unitHP->setPos((64 * 11), (64 * 14));
	}

	~MenuDisplayer() {}

	/**
	*renders the active players stats
	*Overloaded funtion
	*/
	void render(Player* activePlayer)
	{
		showPlayerStats(activePlayer);
	}	
	/**
	*renders the active players stats and the currently active Units HP
	*Overloaded funtion
	*/
	void render(Player* activePlayer, Unit* unit)
	{
		showPlayerStats(activePlayer);
		showUnitStats(unit);
	}

	void showPlayerStats(Player* activePlayer);
	void showUnitStats(Unit* unit);


private:
	std::shared_ptr<Sprite> moneyToken;
	std::shared_ptr<SpriteText> money;
	std::shared_ptr<Sprite> unitCountToken;
	std::shared_ptr<SpriteText> unitCount;
	std::shared_ptr<SpriteText> unitHP;

	MenuDisplayer();
};
