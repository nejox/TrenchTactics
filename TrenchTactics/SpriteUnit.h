#pragma once
#include "Sprite.hpp"

class SpriteUnit :
	public Sprite,
	std::enable_shared_from_this<SpriteUnit>
{
public:

	SpriteUnit(const std::string filename);
	void setAnimation(const std::string filename);
	void render();

	int getCurrentPhase()
	{
		return this->m_currentPhase;
	}

	void setCurrentPhase(int currentPhase)
	{
		this->m_currentPhase = currentPhase;
	}

	std::shared_ptr<SpriteUnit> getptr() {
		return shared_from_this();
	}

private:
	int m_currentPhase;
};



