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
		std::shared_ptr<BalanceConf> c = ConfigReader::instance().getBalanceConf();

		m_colorRed = colourRed;
		m_maxHP = c->getHqHP();
		m_currentHP = c->getHqHP();

		if (colourRed)
		{
			m_spriteFilePath = c->getSpriteFilePathRed(); //TO DO: config scheiß einfügen
		}
		else
		{
			m_spriteFilePath = c->getSpriteFilePathBlue(); //TO DO: config scheiß einfügen
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