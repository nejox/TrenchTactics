#include "jsoncpp/dist/json/json.h"
#include <fstream>
#include <iostream>
#include <string>
#include "ConfigReader.h"
#include "Logger.hpp"

/**
 * standard constructor
 *
 */
ConfigReader::ConfigReader()
{
	this->balanceConf = NULL;
	this->techConf = NULL;
	this->mapConf = NULL;
}

/**
 * standard destructor
 *
 */
ConfigReader::~ConfigReader()
{
}

/**
 * BaseFunction to initialize the all configurations from json config
 *
 */
void ConfigReader::initConfigurations()
{
	this->unitConfMap = createUnitConfMap();
	this->balanceConf = createBalanceConf();
	this->techConf = createTechConf();
	this->mapConf = createMapConf();
}

/**
 * Read json file and return a json Value object to extract data
 *
 * \param filePath Path to the json file you want to read
 * \return
 */
Json::Value ConfigReader::getJsonRootFromFile(std::string filePath) {
	Json::Value root;
	std::ifstream ifs;
	ifs.open(filePath);
	Json::CharReaderBuilder builder;
	builder["collectComments"] = true;
	JSONCPP_STRING errs;
	if (!parseFromStream(builder, ifs, &root, &errs)) {
		Logger::instance().log(LOGLEVEL::FATAL, errs);
	}
	ifs.close();
	return root;
}

/**
 * Wrapper function to create Map Config
 *
 * \return Map configuration
 */
std::shared_ptr<MapConf> ConfigReader::createMapConf()
{
	Json::Value root = getJsonRootFromFile("../conf/gameConf.json")["map"];
	std::shared_ptr<MapConf> mapConf = std::make_shared<MapConf>();
	mapConf->setSeed(root["seed"].asInt());
	mapConf->setSizeX(root["sizeX"].asInt());
	mapConf->setSizeY(root["sizeY"].asInt());
	mapConf->setHeadquarterSpriteBlue(root["headquarterSpriteBlue"].asString());
	mapConf->setHeadquarterSpriteRed(root["headquarterSpirteRed"].asString());
	std::vector<std::string> terrainSpriteList;
	for (auto terrain : root["terrainSprites"]) {
		terrainSpriteList.push_back(terrain.asString());
	}
	mapConf->setTerrainSpriteList(terrainSpriteList);
	mapConf->setSpawnTileSprite(root["spawnSprite"].asString());
	return mapConf;
}

/**
 * Wrapper function to create Technical Config
 *
 * \return Technical configuration
 */
std::shared_ptr<TechConf> ConfigReader::createTechConf()
{
	Json::Value root = getJsonRootFromFile("../conf/gameConf.json")["technical"];
	std::shared_ptr<TechConf> techConf = std::make_shared<TechConf>();
	techConf->setFPS(root["seed"].asInt());
	techConf->setWindowSizeX(root["windowSizeX"].asInt());
	techConf->setWindowSizeY(root["windowSizeY"].asInt());
	return techConf;
}

/**
 * Wrapper function to create Balance Config
 *
 * \return Balance configuration
 */
std::shared_ptr<BalanceConf> ConfigReader::createBalanceConf()
{
	Json::Value root = getJsonRootFromFile("../conf/gameConf.json")["balance"];
	std::shared_ptr<BalanceConf> balanceConf = std::make_shared<BalanceConf>();
	balanceConf->setHqHp(root["hqHP"].asInt());
	balanceConf->setMaxAmountUnits(root["maxAmountUnits"].asInt());
	balanceConf->setRerollCost(root["rerollCost"].asInt());
	balanceConf->setStartingGold(root["startingGold"].asInt());
	balanceConf->setTrenchIncomeFactoR(root["trenchIncomeFactor"].asInt());
	return balanceConf;
}

/**
 * Wrapper function that creates a unit config for every unit specified in the config file
 * returns a map with the id of the unit as key
 *
 * \return
 */
std::map<int, std::shared_ptr<UnitConf>> ConfigReader::createUnitConfMap()
{
	std::map<int, std::shared_ptr<UnitConf>> unitConfMap;
	Json::Value root = getJsonRootFromFile("../conf/unitConf.json");

	for (int i = 0; i < 3; i++)
	{
		Json::Value rootElem = root[i];
		std::shared_ptr<UnitConf> unitConf = std::make_shared<UnitConf>();
		unitConf->setAp(rootElem["ap"].asInt());
		unitConf->setApCostAttack(rootElem["apCostAttack"].asInt());
		unitConf->setApCostMove(rootElem["apCostMove"].asInt());
		unitConf->setApCostTrench(rootElem["apCostTrench"].asInt());
		unitConf->setCost(rootElem["cost"].asInt());
		unitConf->setDmg(rootElem["dmg"].asInt());
		unitConf->setHp(rootElem["hp"].asInt());
		unitConf->setRange(rootElem["range"].asInt());
		unitConf->setSpawnProbability(rootElem["spawnProbability"].asInt());
		unitConf->setSpriteFilePathStandingActiveRed(rootElem["spritesRed"]["standingActive"].asString());
		unitConf->setSpriteFilePathStandingNeutralRed(rootElem["spritesRed"]["standingNeutral"].asString());
		unitConf->setSpriteFilePathShootingRed(rootElem["spritesRed"]["shooting"].asString());
		unitConf->setSpriteFilePathRunningRed(rootElem["spritesRed"]["running"].asString());
		unitConf->setSpriteFilePathStandingActiveBlue(rootElem["spritesBlue"]["standingActive"].asString());
		unitConf->setSpriteFilePathStandingNeutralBlue(rootElem["spritesBlue"]["standingNeutral"].asString());
		unitConf->setSpriteFilePathShootingBlue(rootElem["spritesBlue"]["shooting"].asString());
		unitConf->setSpriteFilePathRunningBlue(rootElem["spritesBlue"]["running"].asString());
		unitConf->setName(rootElem["name"].asString());
		unitConfMap[i] = unitConf;
	}
	this->unitConfMap = unitConfMap;
	return unitConfMap;
}
