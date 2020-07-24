#include "catch.hpp"
#include "../TrenchTactics/Sprite.h"
#include "../TrenchTactics/ConfigReader.h"

using namespace std;

TEST_CASE("init Sprite") {

//	RendererImpl::instance().init(0, 0);
	ConfigReader::instance().initConfigurations();
	
	REQUIRE(ConfigReader::instance().getMapConf()->getCorpseSprite().empty() != true);
	int x = 360;
	int y = 420;
	Sprite* SUT = new Sprite();
	SUT->load(ConfigReader::instance().getMapConf()->getCorpseSprite());
	SUT->setPos(x, y);
	REQUIRE(SUT->getX() == x);
	REQUIRE(SUT->getY() == y);

}
