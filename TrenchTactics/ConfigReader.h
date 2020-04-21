#pragma once
#include "jsoncpp/dist/json/json.h"
#include "UnitConf.h"
#include "MapConf.h"
#include "TechConf.h"
#include "BalanceConf.h"
#include <string>
#include <map>

/**
 * ConfigReader class which enables reading configs 
 * Provides a singelton instance 
 * Then provides all instances of different configurations
 */
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

	std::shared_ptr<UnitConf> getUnitConf(int id)
	{
		return this->unitConfMap[id];
	}

	std::shared_ptr <BalanceConf> getBalanceConf() {
		return this->balanceConf;
	}

	std::shared_ptr <MapConf> getMapConf() {
		return this->mapConf;
	}

	std::shared_ptr <TechConf> getTechnicalConf() {
		return this->techConf;
	}

	void initConfigurations();

private:
	ConfigReader();
	std::map<int, std::shared_ptr<UnitConf>> unitConfMap;
	std::shared_ptr<BalanceConf> balanceConf;
	std::shared_ptr<MapConf> mapConf;
	std::shared_ptr<TechConf> techConf;
	Json::Value getJsonRootFromFile(std::string filePath);
	std::shared_ptr<MapConf> createMapConf();
	std::shared_ptr<TechConf> createTechConf();
	std::shared_ptr<BalanceConf> createBalanceConf();
	std::map<int, std::shared_ptr<UnitConf>> createUnitConfMap();
};