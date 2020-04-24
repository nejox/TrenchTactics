#pragma once
#include <string>
#include "GameEndEvent.h"
#include "BalanceConf.h"
#include "ConfigReader.h"



class Headquarter
{

private:
	int m_maxHP;
	int m_currentHP;
	bool m_colorRed;
	std::string m_spriteFilePath;


public:
	Headquarter(bool colourRed)
	{

		std::shared_ptr<MapConf> c = ConfigReader::instance().getMapConf();
		std::shared_ptr<BalanceConf> b = ConfigReader::instance().getBalanceConf();

		m_colorRed = colourRed;
		m_maxHP = b->getHqHP();
		m_currentHP = b->getHqHP();


		if (colourRed)
		{
			m_spriteFilePath = c->getHeadquarterSpriteRed(); //TO DO: config scheiß einfügen
		}
		else
		{
			m_spriteFilePath = c->getHeadquarterSpriteBlue(); //TO DO: config scheiß einfügen
		}
	}

	void changeHP(int damage);

	int getCurrentHP()
	{
		return m_currentHP;
	}

	std::string getSpriteFilePath()
	{
		return m_spriteFilePath;
	}

	bool getColorRed()
	{
		return this->m_colorRed;
	}







};