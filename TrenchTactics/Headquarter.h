#pragma once
#include <string>


class Headquarter
{

public:
	int m_maxHP = 500;
	int m_currentHP = 500;
	std::string m_spriteFilePath;
	
	

	void changeHP(int damage);

	int getCurrentHP()
	{
		return m_currentHP;
	}

	std::string getSpriteFilePath()
	{
		return m_spriteFilePath;
	}


};