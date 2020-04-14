#include "jsoncpp/dist/json/json.h"
#include <fstream>
#include <iostream>
#include "ConfigReader.h"
#include "Logger.hpp"


ConfigReader::ConfigReader()
{
	this->balanceConf = NULL;
	this->techConf = NULL;
	this->mapConf = NULL;
}
ConfigReader::~ConfigReader()
{
}

void ConfigReader::initConfigurations()
{
	this->unitConfMap = createUnitConfMap();
	this->balanceConf = createBalanceConf();
	this->techConf = createTechConf();
	this->mapConf = createMapConf();
}

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


MapConf* ConfigReader::createMapConf()
{
	Json::Value root = getJsonRootFromFile("../conf/gameConf.json")["map"];
	MapConf* mapConf = new MapConf();
	mapConf->setSeed(root["seed"].asInt());
	mapConf->setSizeX(root["sizeX"].asInt());
	mapConf->setSizeY(root["sizeY"].asInt());
	return mapConf;
}
TechConf* ConfigReader::createTechConf()
{
	Json::Value root = getJsonRootFromFile("../conf/gameConf.json")["technical"];
	TechConf* techConf = new TechConf();
	techConf->setFPS(root["seed"].asInt());
	techConf->setWindowSizeX(root["windowSizeX"].asInt());
	techConf->setWindowSizeY(root["windowSizeY"].asInt());
	return techConf;
}
BalanceConf* ConfigReader::createBalanceConf()
{
	Json::Value root = getJsonRootFromFile("../conf/gameConf.json")["balance"];
	BalanceConf* balanceConf = new BalanceConf();
	balanceConf->setHqHp(root["hqHP"].asInt());
	balanceConf->setMaxAmountUnits(root["maxAmountUnits"].asInt());
	balanceConf->setRerollCost(root["rerollCost"].asInt());
	balanceConf->setStartingGold(root["startingGold"].asInt());
	balanceConf->setTrenchIncomeFactoR(root["trenchIncomeFactor"].asInt());
	return balanceConf;
}

std::map<int, UnitConf*> ConfigReader::createUnitConfMap()
{
	std::map<int, UnitConf*> unitConfMap;
	Json::Value root = getJsonRootFromFile("../conf/unitConf.json");

	for (int i = 0; i < 3; i++)
	{
		Json::Value rootElem = root[i];
		UnitConf* unitConf = new UnitConf();
		unitConf->setAp(rootElem["ap"].asInt());
		unitConf->setApCostAttack(rootElem["apCostAttack"].asInt());
		unitConf->setApCostMove(rootElem["apCostMove"].asInt());
		unitConf->setApCostTrench(rootElem["apCostTrench"].asInt());
		unitConf->setCost(rootElem["cost"].asInt());
		unitConf->setDmg(rootElem["dmg"].asInt());
		unitConf->setHp(rootElem["hp"].asInt());
		unitConf->setRange(rootElem["range"].asInt());
		unitConf->setSpawnProbability(rootElem["spawnProbability"].asInt());
		unitConf->setSpriteFilePath(rootElem["spriteFilePath"].asString());
		unitConf->setName(rootElem["name"].asString());
		unitConfMap[i] = unitConf;
	}
	this->unitConfMap = unitConfMap;
	return unitConfMap;
}
