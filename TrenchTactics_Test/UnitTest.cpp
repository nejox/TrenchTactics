#define CATCH_CONFIG_MAIN
#include "../TrenchTactics/Unit.h"
#include "catch.hpp"
#include <filesystem>

using namespace std;



TEST_CASE("Creation of Units") {
	ConfigReader& confReader = ConfigReader::instance();
	confReader.initConfigurations();
	shared_ptr<Unit> gunnerUnit = make_shared<Unit>(TYPES::UNITTYPE::GUNNER, true);
	shared_ptr<Unit> ccUnit = make_shared<Unit>(TYPES::UNITTYPE::CC, false);
	shared_ptr<Unit> grenadeUnit = make_shared<Unit>(TYPES::UNITTYPE::GRENADE, true);

	SECTION("Units aren't nullptrs - constructor working") {
		REQUIRE(gunnerUnit != nullptr);
		REQUIRE(ccUnit != nullptr);
		REQUIRE(grenadeUnit != nullptr);
	}

	SECTION("Units have the right color") {
		REQUIRE(gunnerUnit->getColorRed() == true);
		REQUIRE(ccUnit->getColorRed() == false);
		REQUIRE(grenadeUnit->getColorRed() == true);
	}

	SECTION("Unitsprite is present") {
		REQUIRE(gunnerUnit->getSprite() != nullptr);
		REQUIRE(ccUnit->getSprite() != nullptr);
		REQUIRE(grenadeUnit->getSprite() != nullptr);
	}

	SECTION("Unittype is in correct state and changes state correctly") {
		REQUIRE(gunnerUnit->getState() == STATES::UNITSTATE::STANDING_NEUTRAL);
		gunnerUnit->attack(ccUnit, false);
		REQUIRE(gunnerUnit->getState() == STATES::UNITSTATE::SHOOTING);
	}

	SECTION("Unitparameters are set as intended") {
		REQUIRE(gunnerUnit->getCost() == confReader.getUnitConf(TYPES::UNITTYPE::GUNNER)->getCost());
		REQUIRE(ccUnit->getCost() == confReader.getUnitConf(TYPES::UNITTYPE::CC)->getCost());
		REQUIRE(grenadeUnit->getCost() == confReader.getUnitConf(TYPES::UNITTYPE::GRENADE)->getCost());

		REQUIRE(gunnerUnit->getHp() == confReader.getUnitConf(TYPES::UNITTYPE::GUNNER)->getHP());
		REQUIRE(ccUnit->getHp() == confReader.getUnitConf(TYPES::UNITTYPE::CC)->getHP());
		REQUIRE(grenadeUnit->getHp() == confReader.getUnitConf(TYPES::UNITTYPE::GRENADE)->getHP());

		REQUIRE(gunnerUnit->getAp() == confReader.getUnitConf(TYPES::UNITTYPE::GUNNER)->getAP());
		REQUIRE(ccUnit->getAp() == confReader.getUnitConf(TYPES::UNITTYPE::CC)->getAP());
		REQUIRE(grenadeUnit->getAp() == confReader.getUnitConf(TYPES::UNITTYPE::GRENADE)->getAP());
	}
}

TEST_CASE("Unit attack") {
	ConfigReader& confReader = ConfigReader::instance();
	confReader.initConfigurations();
	shared_ptr<Unit> gunnerUnit = make_shared<Unit>(TYPES::UNITTYPE::GUNNER, true);
	shared_ptr<Unit> ccUnit = make_shared<Unit>(TYPES::UNITTYPE::CC, false);
	shared_ptr<Unit> grenadeUnit = make_shared<Unit>(TYPES::UNITTYPE::GRENADE, true);

	int maxGunnerUnitAP = confReader.getUnitConf(TYPES::UNITTYPE::GUNNER)->getAP();
	int maxCCUnitHP = confReader.getUnitConf(TYPES::UNITTYPE::CC)->getHP();

	// confirming that units are on the right base levels for HP and AP

	REQUIRE(gunnerUnit->getCurrentAP() == maxGunnerUnitAP);
	REQUIRE(ccUnit->getCurrentHP() == maxCCUnitHP);

	gunnerUnit->attack(ccUnit, false);

	SECTION("AP of attacking unit gets changed while AP of attacked unit does not") {
		REQUIRE(gunnerUnit->getCurrentAP() == maxGunnerUnitAP - confReader.getUnitConf(TYPES::UNITTYPE::GUNNER)->getAPCostAttack());
		REQUIRE(ccUnit->getCurrentAP() == confReader.getUnitConf(TYPES::UNITTYPE::CC)->getAP());
	}

	SECTION("HP of attacked unit gets changed while HP of attacking unit does not") {
		REQUIRE(gunnerUnit->getCurrentHP() == confReader.getUnitConf(TYPES::UNITTYPE::GUNNER)->getHP());
		REQUIRE(ccUnit->getCurrentHP() == (maxCCUnitHP - confReader.getUnitConf(TYPES::UNITTYPE::GUNNER)->getDmg()));
	}

	SECTION("Attacking unit current state gets changed to shooting") {
		REQUIRE(gunnerUnit->getState() == STATES::UNITSTATE::SHOOTING);
	}

	SECTION("Resetting of ap of attacking unit") {
		gunnerUnit->resetAP();
		REQUIRE(gunnerUnit->getAp() == maxGunnerUnitAP);
	}

	shared_ptr<Headquarter> testHQ = make_shared<Headquarter>(true);
	SECTION("Attacking of headquarter changes ap of unit and hp of hq") {
		gunnerUnit->attack(testHQ);
		REQUIRE(testHQ->getCurrentHP() == confReader.getBalanceConf()->getHqHP() -confReader.getUnitConf(TYPES::UNITTYPE::GUNNER)->getDmg());
	}

}


