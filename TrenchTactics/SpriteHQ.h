#pragma once
#include <string>
#include "Sprite.hpp"

class SpriteHQ : public Sprite
{
public:

	bool damaged;

	SpriteHQ(const std::string filename);
	void render(bool damaged);

private:
	SpriteHQ();

};

