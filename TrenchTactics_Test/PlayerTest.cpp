#include "catch.hpp"
#include "../TrenchTactics/Player.h"
#include "../TrenchTactics/Gamefield.h"

using namespace std;

TEST_CASE("Player Creation") {
	shared_ptr<Player> player = make_shared<Player>();
	ConfigReader::instance().initConfigurations();
	player->init(true);

	// check for nullptr
	REQUIRE(player != nullptr);
	SECTION("Initial plalyer values are correct") {
		REQUIRE(player->getColor() == true);
		REQUIRE(player->getMoney() == ConfigReader::instance().getBalanceConf()->getStartingGold());
	}
}

TEST_CASE("Add and delete Unit from Player Test") {
	ConfigReader::instance().initConfigurations();
	shared_ptr<Player> player = make_shared<Player>();
	shared_ptr<Unit> gunnerUnit = make_shared<Unit>(TYPES::UNITTYPE::GUNNER, true);
	shared_ptr<Unit> ccUnit = make_shared<Unit>(TYPES::UNITTYPE::CC, true);
	Gamefield::instance().init(ConfigReader::instance().getMapConf()->getSizeX(), ConfigReader::instance().getMapConf()->getSizeY(), ConfigReader::instance().getMapConf()->getSeed());;

	//Test that player has no unit
	REQUIRE(player->getUnitArray().size() == 0);
	SECTION("Add units to player") {
		player->addUnit(gunnerUnit);
		REQUIRE(player->getUnitArray().size() == 1);
		player->addUnit(ccUnit);
		REQUIRE(player->getUnitArray().size() == 2);
	}
	SECTION("Copy units to queue check size and empty it again") {
		// fill queue
		player->addUnit(gunnerUnit);
		player->addUnit(ccUnit);
		player->copyUnitsToQueue();
		REQUIRE(player->getUnitArray().size() == 2);
		REQUIRE(player->getUnitQueue().size() == 2);

		//empty queue with command
		player->emptyQueue();
		REQUIRE(player->getUnitArray().size() == 2);
		REQUIRE(player->getUnitQueue().size() == 0);

		//fill queue again
		player->copyUnitsToQueue();
		REQUIRE(player->getUnitArray().size() == 2);
		REQUIRE(player->getUnitQueue().size() == 2);

		//empty queue step by step
		player->popUnit();
		REQUIRE(player->getUnitQueue().size() == 1);
		player->popUnit();
		REQUIRE(player->getUnitQueue().size() == 0);

	}
}
TEST_CASE("Update money and compute income") {
	ConfigReader::instance().initConfigurations();
	shared_ptr<Player> player = make_shared<Player>();
	shared_ptr<Unit> gunnerUnit = make_shared<Unit>(TYPES::UNITTYPE::GUNNER, true);
	shared_ptr<Unit> ccUnit = make_shared<Unit>(TYPES::UNITTYPE::CC, true);
	Gamefield::instance().init(ConfigReader::instance().getMapConf()->getSizeX(), ConfigReader::instance().getMapConf()->getSizeY(), ConfigReader::instance().getMapConf()->getSeed());
	player->init(true);

	SECTION("add money") {
		// check starting gold
		int startingGold = ConfigReader::instance().getBalanceConf()->getStartingGold();
		REQUIRE(player->getMoney() == startingGold);
		player->updateMoney(50);
		REQUIRE(player->getMoney() == startingGold + 50);

		//check boundaries
		player->updateMoney(99999);
		REQUIRE(player->getMoney() == 9999);
		//zero boundary is not working
		player->updateMoney(-999999);
		REQUIRE(player->getMoney() == 0);
	}

	SECTION("compute income") {
		//compute base income without a single trench
		REQUIRE(player->computeIncome() == 100);

		//comput income with one trench TODO - rewrite test to a good form
		player->addUnit(gunnerUnit);
		shared_ptr<FieldTile> testFieldTile = Gamefield::instance().getFieldTileFromXY(600, 600);
		testFieldTile->setUnit(gunnerUnit);
		testFieldTile->setTrench(true);
		REQUIRE(player->computeIncome() == 148);

	}
}

TEST_CASE("Compute supply") {
	ConfigReader::instance().initConfigurations();
	shared_ptr<Player> player = make_shared<Player>();
	shared_ptr<Unit> gunnerUnit = make_shared<Unit>(TYPES::UNITTYPE::GUNNER, true);
	shared_ptr<Unit> ccUnit = make_shared<Unit>(TYPES::UNITTYPE::CC, true);
	player->addUnit(gunnerUnit);
	REQUIRE(player->getUnitArray().size() == 1);
	player->addUnit(ccUnit);
	REQUIRE(player->getUnitArray().size() == 2);
}

TEST_CASE("AP reset of units") {
	ConfigReader::instance().initConfigurations();
	shared_ptr<Player> player = make_shared<Player>();
	shared_ptr<Unit> gunnerUnit = make_shared<Unit>(TYPES::UNITTYPE::GUNNER, true);
	shared_ptr<Unit> ccUnit = make_shared<Unit>(TYPES::UNITTYPE::CC, true);
	player->addUnit(gunnerUnit);
	player->addUnit(ccUnit);

	// check prerequisites
	REQUIRE(gunnerUnit->getCurrentAP() == gunnerUnit->getAp());
	REQUIRE(ccUnit->getCurrentAP() == ccUnit->getAp());

	//set ap of units to two, just for testing reasons
	gunnerUnit->setCurrentAP(2);
	ccUnit->setCurrentAP(2);
	REQUIRE(gunnerUnit->getCurrentAP() == 2);
	REQUIRE(ccUnit->getCurrentAP() == 2);

	// now reset ap of the units using the function of the player class
	player->resetApForAllUnits();
	REQUIRE(gunnerUnit->getCurrentAP() == gunnerUnit->getAp());
	REQUIRE(ccUnit->getCurrentAP() == ccUnit->getAp());
}