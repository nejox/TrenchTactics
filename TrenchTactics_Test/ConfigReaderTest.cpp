#include "catch.hpp"
#include "../TrenchTactics/ConfigReader.h"
#include <iostream>
#include <filesystem>


inline bool file_exists(const std::string& name) {
	struct stat buffer;
	return (stat(name.c_str(), &buffer) == 0);
}

TEST_CASE("Create Config Reader and initialize all components") {
	ConfigReader& confReader = ConfigReader::instance();
	confReader.initConfigurations();

	SECTION("BalanceConf is created") {
		REQUIRE(confReader.getBalanceConf() != nullptr);
	}
	SECTION("UnitConf is created") {
		for (int i = 0; i <= 2; i++) {
			REQUIRE(confReader.getUnitConf(i) != nullptr);
		}
	}
	SECTION("ButtonConf is created") {
		REQUIRE(confReader.getButtonConf() != nullptr);
	}
	SECTION("MenuBarConf is created") {
		REQUIRE(confReader.getMenuBarConf() != nullptr);
	}
	SECTION("TileConf is created") {
		REQUIRE(confReader.getTileConf() != nullptr);
	}
	SECTION("TechConf is created") {
		REQUIRE(confReader.getTechnicalConf() != nullptr);
	}
	SECTION("MapConf is created") {
		REQUIRE(confReader.getMapConf() != nullptr);
	}
}

TEST_CASE("BalanceConf values are initialized") {
	ConfigReader& confReader = ConfigReader::instance();
	confReader.initConfigurations();
	std::shared_ptr<BalanceConf> balanceConf = confReader.getBalanceConf();
	SECTION("Test if balanceConf values are initialized (by sample)") {
		SECTION("HQHP is in a reasonable range") {
			REQUIRE(balanceConf->getHqHP() > 0);
			REQUIRE(balanceConf->getHqHP() < 10000);
		}
		SECTION("MaxAmount of units is in a reasonable range") {
			REQUIRE(balanceConf->getMaxAmountUnits() > 0);
			REQUIRE(balanceConf->getMaxAmountUnits() < 50);
		}
		SECTION("Rerollcost is in a reasonablve range") {
			REQUIRE(balanceConf->getRerollCost() > 0);
			REQUIRE(balanceConf->getRerollCost() < 1000);
		}
	}
}

TEST_CASE("MapConf values are initialized") {
	ConfigReader& confReader = ConfigReader::instance();
	confReader.initConfigurations();
	std::shared_ptr<MapConf> mapConf = confReader.getMapConf();
	SECTION("Test if mapConf values are initialized (by sample)") {
		SECTION("SizeX is in a reasonable range") {
			REQUIRE(mapConf->getSizeX() > 0);
			REQUIRE(mapConf->getSizeX() < 5000);
		}
		SECTION("SizeY is in a reasonable range") {
			REQUIRE(mapConf->getSizeY() > 0);
			REQUIRE(mapConf->getSizeY() < 5000);
		}
		SECTION("CorpseSprite String is actually a string and an actual file") {
			REQUIRE(mapConf->getCorpseSprite().length() > 0);
			REQUIRE(file_exists(mapConf->getCorpseSprite()) == true);
		}
	}
}

TEST_CASE("UnitConf values are initialized") {
	ConfigReader& confReader = ConfigReader::instance();
	confReader.initConfigurations();
	std::shared_ptr<UnitConf> unitConf = confReader.getUnitConf(0);
	SECTION("Test if unitConf values are initialized (by sample)") {
		SECTION("ApCostAttack is in a reasonable range") {
			REQUIRE(unitConf->getApCostAttack() > 0);
			REQUIRE(unitConf->getApCostAttack() < 100);
		}
		SECTION("DMG is in a reasonable range") {
			REQUIRE(unitConf->getDmg() > 0);
			REQUIRE(unitConf->getDmg() < 5000);
		}
		SECTION("RunnigSprite String is actually a string, an actual file, and red and blue is not identical") {
			REQUIRE(unitConf->getSpriteFilePathRunningBlue().length() > 0);
			REQUIRE(file_exists(unitConf->getSpriteFilePathRunningBlue()) == true);
			REQUIRE(unitConf->getSpriteFilePathRunningBlue() != unitConf->getSpriteFilePathRunningRed());
		}
	}
}

TEST_CASE("TileConf values are initialized") {
	ConfigReader& confReader = ConfigReader::instance();
	confReader.initConfigurations();
	std::shared_ptr<TileConf> tileConf = confReader.getTileConf();
	SECTION("Test if tileConf values are initialized (by sample)") {
		SECTION("HeadquarterSprite String is actually a string, an actual file, and red and blue is not identical") {
			REQUIRE(tileConf->getHeadquarterSpriteBlue().length() > 0);
			REQUIRE(file_exists(tileConf->getHeadquarterSpriteBlue()) == true);
			REQUIRE(tileConf->getHeadquarterSpriteBlue() != tileConf->getHeadquarterSpriteRed());
		}
		SECTION("MoneyTokenSprite String is actually a string and an actual file") {
			REQUIRE(tileConf->getMoneyTokenSprite().length() > 0);
			REQUIRE(file_exists(tileConf->getMoneyTokenSprite()) == true);
		}
		SECTION("NextUnitButton String is actually a string and an actual file") {
			REQUIRE(tileConf->getNextUnitButtonSprite().length() > 0);
			REQUIRE(file_exists(tileConf->getNextUnitButtonSprite()) == true);
		}
	}
}

TEST_CASE("TechConf values are initialized") {
	ConfigReader& confReader = ConfigReader::instance();
	confReader.initConfigurations();
	std::shared_ptr<TechConf> techConf = confReader.getTechnicalConf();
	SECTION("Test if techConf values are initialized (by sample)") {
		SECTION("FPS is in a reasonable range") {
			REQUIRE(techConf->getFPS() > 0);
			REQUIRE(techConf->getFPS() < 500);
		}
		SECTION("WindowSizeX is in a reasonable range") {
			REQUIRE(techConf->getWindowSizeX() > 0);
			REQUIRE(techConf->getWindowSizeX() < 5000);
		}
		SECTION("TextFont String is actually a string and an actual file") {
			REQUIRE(techConf->getTextFont().length() > 0);
			REQUIRE(file_exists(techConf->getTextFont()) == true);
		}
	}
}

TEST_CASE("MenuBarConf values are initialized") {
	ConfigReader& confReader = ConfigReader::instance();
	confReader.initConfigurations();
	std::shared_ptr<MenuBarConf> menuBarConf = confReader.getMenuBarConf();
	SECTION("Test if menuBarconf values are initialized (by sample)") {
		SECTION("AttackPhaseTokenSprite String is actually a string and an actual file") {
			REQUIRE(menuBarConf->getAttackPhaseTokenSprite().length() > 0);
			REQUIRE(file_exists(menuBarConf->getAttackPhaseTokenSprite()) == true);
		}
		SECTION("MenuBarBaseSprite String is actually a string and an actual file") {
			REQUIRE(menuBarConf->getMenuBarBaseSprite().length() > 0);
			REQUIRE(file_exists(menuBarConf->getMenuBarBaseSprite()) == true);
		}
		SECTION("MovePhaseTokenSprite String is actually a string and an actual file") {
			REQUIRE(menuBarConf->getMovePhaseTokenSprite().length() > 0);
			REQUIRE(file_exists(menuBarConf->getMovePhaseTokenSprite()) == true);
		}
	}
}

TEST_CASE("ButtonConf values are initialized") {
	ConfigReader& confReader = ConfigReader::instance();
	confReader.initConfigurations();
	std::shared_ptr<ButtonConf> buttonConf = confReader.getButtonConf();
	SECTION("Test if buttonConf values are initialized (by sample)") {
		SECTION("AddTokenSprite String is actually a string and an actual file") {
			REQUIRE(buttonConf->getAddTokenSprite().length() > 0);
			REQUIRE(file_exists(buttonConf->getAddTokenSprite()) == true);
		}
		SECTION("DigTokenSprite String is actually a string and an actual file") {
			REQUIRE(buttonConf->getDigTokenSprite().length() > 0);
			REQUIRE(file_exists(buttonConf->getDigTokenSprite()) == true);
		}
		SECTION("GunnerTokenSprite String is actually a string, an actual file, and gunner- and grenadeTokenSprite are not identical") {
			REQUIRE(buttonConf->getGunnerTokenSprite().length() > 0);
			REQUIRE(file_exists(buttonConf->getGunnerTokenSprite()) == true);
			REQUIRE(buttonConf->getGunnerTokenSprite() != buttonConf->getGrenadeTokenSprite());
		}
	}

}

