#pragma once
#include "Sprite.hpp"

class SpriteUnit :
	public Sprite
{
public: 
	
	SpriteUnit();
	void setAnimation(const std::string filename);
	void render();

private:
	int m_actualPhase;
};



