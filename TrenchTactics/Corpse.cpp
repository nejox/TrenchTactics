#include "Corpse.h"

Corpse::Corpse(int x, int y)
{
	reward = 10; //TO DO: ConfigReader::instance().get ...
	corpseSprite = new Sprite();
	corpseSprite->load(ConfigReader::instance().getMapConf()->getCorpseSprite()); // TO DO: same
	this->corpseSprite->setPos(x, y);
}

void Corpse::render()
{
	this->corpseSprite->render();
}


