#include "catch.hpp"
#include "../TrenchTactics/MenuBar.h"

using namespace std;

TEST_CASE("Test init functions") {
	shared_ptr<MenuBar> testBar = make_shared<MenuBar>();
	testBar->init();

	REQUIRE(testBar != nullptr);
}

TEST_CASE("Test if Buttons are created") {
	shared_ptr<MenuBar> testBar = make_shared<MenuBar>();
	testBar->init();
	testBar->initButtons(GAMEPHASES::GAMEPHASE::BUY);

	REQUIRE(testBar->getMenuBar().get()->at(7).at(1).get()->getButton() != nullptr);
}

TEST_CASE("Test if Buttons are deleted") {
	shared_ptr<MenuBar> testBar = make_shared<MenuBar>();
	testBar->init();
	testBar->initButtons(GAMEPHASES::GAMEPHASE::BUY);
	testBar->deleteAllButtons();

	for (int i = 4; i < 15; i = i++) {
		REQUIRE(testBar->getMenuBar().get()->at(i).at(1).get()->getButton() == nullptr);
	}
}

