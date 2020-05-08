#pragma once
#include <string>
#include "GameEndEvent.h"
#include "BalanceConf.h"
#include "ConfigReader.h"
#include "SpriteHQ.h"

class Headquarter
{

private:
	int m_maxHP;
	int m_currentHP;
	bool m_colorRed;
	bool m_damaged;
	std::string m_spriteFilePath;
	std::shared_ptr<SpriteHQ> m_spriteHQ;
	
public:
	Headquarter(bool colourRed)
	{
		m_colorRed = colourRed;
		m_maxHP = ConfigReader::instance().getBalanceConf()->getHqHP();
		m_currentHP = ConfigReader::instance().getBalanceConf()->getHqHP();
		m_damaged = false;

		m_spriteHQ = make_shared<SpriteHQ>(m_colorRed);
				
	}
	/// <summary>
	/// Renders the HQ dependent on its current health state
	/// </summary>
	/// 
	void render()
	{
		this->m_spriteHQ->render(this->getDamaged());
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

	void setDamaged(bool damaged)
	{
		this->m_damaged = damaged;
	}

	bool getDamaged()
	{
		return this->m_damaged;
	}

	void setSprite(std::shared_ptr<SpriteHQ> sprite)
	{
		m_spriteHQ = sprite;
	};

	std::shared_ptr<SpriteHQ> getSprite() {
		return m_spriteHQ;
	}

};