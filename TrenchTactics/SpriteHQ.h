#pragma once
#include <string>
#include "Sprite.hpp"

class SpriteHQ : public Sprite
{
public:

	enum state {
		healthy,
		damaged
	};

	SpriteHQ(const std::string filename, int numFrames);
	void render(state health);

private:
	SpriteHQ();

};

