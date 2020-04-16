#pragma once

class Headquarter
{
public:
	int m_maxHP = 500;
	int m_currentHP = 500;

	void changeHP(int damage);

	int getCurrentHP()
	{
		return m_currentHP;
	}


};