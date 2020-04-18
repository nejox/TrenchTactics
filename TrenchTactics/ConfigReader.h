#pragma once
#include "jsoncpp/dist/json/json.h"
#include "UnitConf.h"
#include "MapConf.h"
#include "TechConf.h"
#include "BalanceConf.h"
#include <string>
#include <map>

class ConfigReader
{
public:
	~ConfigReader();
	ConfigReader(const ConfigReader&) = delete;
	ConfigReader& operator=(const ConfigReader&) = delete;
	ConfigReader(ConfigReader&&) = delete;
	ConfigReader& operator=(ConfigReader&&) = delete;

	static auto& instance() {
		static ConfigReader confReader;
		return confReader;
	}

	UnitConf* getUnitConf(int id)
	{
		return this->unitConfMap[id];
	}

	BalanceConf* getBalanceConf() {
		return this->balanceConf;
	}

	MapConf* getMapConf() {
		return this->mapConf;
	}

	TechConf* getTechnicalConf() {
		return this->techConf;
	}

	void initConfigurations();

private:
	ConfigReader();
	std::map<int, UnitConf*> unitConfMap;
	BalanceConf* balanceConf;
	MapConf* mapConf;
	TechConf* techConf;
	Json::Value getJsonRootFromFile(std::string filePath);
	MapConf* createMapConf();
	TechConf* createTechConf();
	BalanceConf* createBalanceConf();
	std::map<int, UnitConf*> createUnitConfMap();
};