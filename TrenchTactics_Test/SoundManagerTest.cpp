#include "catch.hpp"
#include "../TrenchTactics/SoundManagerImpl.h"
#include "../TrenchTactics/RendererImpl.h"
#include "../TrenchTactics/ConfigReader.h"

using namespace std;

TEST_CASE("init Sound") {

	RendererImpl::instance().init(0, 0);
	ConfigReader::instance().initConfigurations();

	REQUIRE(ConfigReader::instance().getTechnicalConf()->getaudioFilePath().empty() != true);

	//Getter fehlen um Instanz auf NULL zu pr�fen
	//entweder schmei�t Fehler oder l�uft durch und wird true
	SoundManagerImpl::instance().startMusic();
	REQUIRE(true);

}
