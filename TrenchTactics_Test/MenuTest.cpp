#include "catch.hpp"
#include "../TrenchTactics/Menu.h"
#include "../TrenchTactics/Button.h"

using namespace std;

TEST_CASE("Menu creation") {
	
	RendererImpl::instance().init(0, 0);
	ConfigReader::instance().initConfigurations();
	
	Menu& menu = Menu::instance();
	menu.initMenu(true);
	menu.showMenu();
	REQUIRE(Menu::instance().IsShowingMenu() == true);

}

TEST_CASE("Menu returns buttons") {
	
	RendererImpl::instance().init(0, 0);
	ConfigReader::instance().initConfigurations();
	Menu::instance().initMenu(true);

	int posX = ConfigReader::instance().getTechnicalConf()->getWindowSizeX() / 2 - 3 * 64;
	int posY = ConfigReader::instance().getTechnicalConf()->getWindowSizeY() / 2 - 5 * 64;
	int ButtonX = posX + 34;
	int ButtonY = posY + 128;

	REQUIRE(Menu::instance().getButtonTypeFromXY(1, 1) == 0);
	REQUIRE(Menu::instance().getButtonTypeFromXY(ButtonX, ButtonY) == Button::BUTTONTYPE::STARTGAME);
	
}