#include "catch.hpp"
#include "../TrenchTactics/Headquarter.h"
#include "../TrenchTactics/ConfigReader.h"



TEST_CASE("Test change of hp as well as dmg state of HQ") {
	ConfigReader& confReader = ConfigReader::instance();
	confReader.initConfigurations();

	shared_ptr<Headquarter> testHQ = make_shared<Headquarter>(true);
	int testDMG = 50;

	SECTION("Headquarter health is loaded correctly") {
		REQUIRE(testHQ->getHP() == confReader.getBalanceConf()->getHqHP());
	}

	SECTION("Headquarter health is changed correctly") {
		testHQ->changeHP(testDMG);
		REQUIRE(testHQ->getCurrentHP() == confReader.getBalanceConf()->getHqHP() - testDMG);
	}

	SECTION("Headquarter state is correctly changed to damaged") {
		testHQ->changeHP(testDMG * 2);
		REQUIRE(testHQ->getDamaged() == false);
		testHQ->changeHP(testDMG);
		REQUIRE(testHQ->getDamaged() == true);
		
	}
}