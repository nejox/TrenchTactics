#include "Corpse.h"

Corpse::Corpse(int x, int y)
{
	reward = 10; //TO DO: ConfigReader::instance().get ...
	corpseSprite = std::make_shared<Sprite>();
	corpseSprite->load(ConfigReader::instance().getMapConf()->getCorpseSprite());
	this->corpseSprite->setPos(x, y);
}

void Corpse::render()
{
	this->corpseSprite->render();
}


