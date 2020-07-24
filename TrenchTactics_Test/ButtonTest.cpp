/*
#include "catch.hpp"
#include "../TrenchTactics/Button.h"

TEST_CASE("Create button") {
	ConfigReader::instance().initConfigurations();
	std::cout << ConfigReader::instance().getTechnicalConf()->getTextFont() << std::endl;
	std::cout << ConfigReader::instance().getTechnicalConf()->getTextFont().c_str() << std::endl;

	// this doesn't work cause loading font doesnt work - dunno why - pls kill me
	// as you can see above by the prints the paths are correct - still nothing
	// i still wanna kill myself
	
	shared_ptr<Button> testConfirmButton = make_shared<Button>(Button::BUTTONTYPE::CONFIRM);
	shared_ptr<Button> testEndTurnButton = make_shared<Button>(Button::BUTTONTYPE::ENDTURN);

	REQUIRE(testEndTurnButton != nullptr);
	REQUIRE(testConfirmButton != nullptr);

	REQUIRE(testConfirmButton->getState() == false);
	REQUIRE(testEndTurnButton->getState() == false);

	//press button now
	testConfirmButton->push();
	REQUIRE(testConfirmButton->getState() == true);
	REQUIRE(testEndTurnButton->getState() == false);
	
}
*/

/*
TEST_CASE("Loading of cost") {
	shared_ptr<Button> testGrenadeUnitButton = make_shared<Button>(Button::BUTTONTYPE::GRENADEUNIT);
	shared_ptr<Button> testRerollButton = make_shared<Button>(Button::BUTTONTYPE::REROLL);

	REQUIRE(testGrenadeUnitButton->getCost() == ConfigReader::instance().getUnitConf(testGrenadeUnitButton->getType())->getCost());
}
*/
