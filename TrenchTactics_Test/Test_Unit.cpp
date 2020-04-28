#define CATCH_CONFIG_MAIN
#include "../TrenchTactics/Unit.h"
#include "catch.hpp"





TEST_CASE("Units are Initialized")
{

	std::string name = "GUNNER";
	Unit* test = new Unit(Unit::UnitType::GUNNER, true);
	REQUIRE(name == test->getName());

}
