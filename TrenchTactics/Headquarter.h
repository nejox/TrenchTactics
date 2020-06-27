#pragma once
#include "GameEndEvent.h"
#include "BalanceConf.h"
#include "ConfigReader.h"
#include "SpriteHQ.h"
#include "SpriteHealthBar.h"
#include "EventBus.h"

/**
 * Base headquarter class that holds all information concerning the headquarter of a player like health, color or spritefilepath.
 */
class Headquarter
{

private:
	int m_maxHP;
	int m_currentHP;
	bool m_colorRed;
	bool m_damaged;
	std::string m_spriteFilePath;
	std::shared_ptr<SpriteHQ> m_spriteHQ;
	std::shared_ptr<SpriteHealthBar> m_spriteHealthBar;

public:
	Headquarter(bool colourRed)
	{
		m_colorRed = colourRed;
		m_maxHP = ConfigReader::instance().getBalanceConf()->getHqHP();
		m_currentHP = ConfigReader::instance().getBalanceConf()->getHqHP();
		m_damaged = false;

		m_spriteHQ = std::make_shared<SpriteHQ>(m_colorRed);

		m_spriteHealthBar = std::make_shared<SpriteHealthBar>();

	}

	/**
	 * Renders the HQ dependent on its current health state.
	 *
	 */
	void render()
	{
		this->m_spriteHQ->render(this->getDamaged());
		this->m_spriteHealthBar->render(this->m_maxHP, this->m_currentHP);
	}

	void changeHP(int damage);

	int getCurrentHP()
	{
		return m_currentHP;
	}

	int getHP()
	{
		return m_maxHP;
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

	std::shared_ptr<SpriteHealthBar> getSpriteHealthBar() {
		return m_spriteHealthBar;
	}

	void resetHQ();
};