#pragma once
#include "../jsoncpp/dist/json/json.h"

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
private:
	ConfigReader();
};