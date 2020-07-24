#include "catch.hpp"
#include "../TrenchTactics/Gamefield.h"


using namespace std;

TEST_CASE("Gamefield creation") {

	RendererImpl::instance().init(0, 0);
	ConfigReader::instance().initConfigurations();

	Gamefield& field = Gamefield::instance();
	field.init(ConfigReader::instance().getMapConf()->getSizeX(), ConfigReader::instance().getMapConf()->getSizeY(), ConfigReader::instance().getMapConf()->getSeed());
	//check if at least one tile was created
	REQUIRE(field.getTilePointerAt(0, 0) != nullptr );

}

TEST_CASE("Spawn unit on field") {

	RendererImpl::instance().init(0, 0);
	ConfigReader::instance().initConfigurations();
	Gamefield& field = Gamefield::instance();
	field.init(ConfigReader::instance().getMapConf()->getSizeX(), ConfigReader::instance().getMapConf()->getSizeY(), ConfigReader::instance().getMapConf()->getSeed());

	shared_ptr<Unit> unit = make_shared<Unit>(true);

	field.spawnUnitInSpawn(unit, true);

	REQUIRE(field.findTileByUnit(unit) != nullptr);

}

TEST_CASE("Check if Unit has enemies around") {

	RendererImpl::instance().init(0, 0);
	ConfigReader::instance().initConfigurations();
	Gamefield& field = Gamefield::instance();
	field.init(ConfigReader::instance().getMapConf()->getSizeX(), ConfigReader::instance().getMapConf()->getSizeY(), ConfigReader::instance().getMapConf()->getSeed());

	shared_ptr<Unit> unit = make_shared<Unit>(true);

	field.spawnUnitInSpawn(unit, true);

	REQUIRE(field.checkUnitHasEnemysAround(unit, true) == false);

}

TEST_CASE("FieldTile is free") {

	RendererImpl::instance().init(0, 0);
	ConfigReader::instance().initConfigurations();
	Gamefield& field = Gamefield::instance();
	field.init(ConfigReader::instance().getMapConf()->getSizeX(), ConfigReader::instance().getMapConf()->getSizeY(), ConfigReader::instance().getMapConf()->getSeed());

	shared_ptr<Unit> unit = make_shared<Unit>(true);

	field.spawnUnitInSpawn(unit, true);

	REQUIRE(field.fieldTileIsFree(field.findTileByUnit(unit)->getPosX(), field.findTileByUnit(unit)->getPosY(), field.getPlayingfield()) == false);

}

TEST_CASE("Deselect and unmark all tiles") {

	RendererImpl::instance().init(0, 0);
	ConfigReader::instance().initConfigurations();

	Gamefield& field = Gamefield::instance();
	field.init(ConfigReader::instance().getMapConf()->getSizeX(), ConfigReader::instance().getMapConf()->getSizeY(), ConfigReader::instance().getMapConf()->getSeed());
	field.getTilePointerAt(0, 0)->setSelected(true);
	field.deselectAndUnmarkAllTiles();
	//check if at least one tile was created
	REQUIRE(field.getTilePointerAt(0, 0)->getSelected() == false);

}

