#define SDL_MAIN_HANDLED


#include "Framework.hpp"
#include "Game.hpp"
#include "Logger.hpp"
#include "ConfigReader.h"
#include "RendererImpl.h"
#include "Unit.h"
#include "Gamefield.h"

/// <summary>
/// 
/// </summary>
/// <param name="argc"></param>
/// <param name="argv"></param>
/// <returns></returns>
int main(int argc, char* argv[])
{

	ConfigReader& confReader = ConfigReader::instance();

	Logger::instance().log(LOGLEVEL::INFO, "Starting main");
	confReader.initConfigurations();
	std::cout << confReader.getUnitConf(0)->getAp() << std::endl;

	if (RendererImpl::instance().init(confReader.getTechnicalConf()->getWindowSizeX(), confReader.getTechnicalConf()->getWindowSizeY()), 16, false)
		return (0);


	//if (g_pFramework->Init(1408, 768, 16, false) == false)
	//	return (0);

	//CGame Game;
	//Game.Init();
	//Game.Run();
	//Game.Quit();

	//g_pFramework->Quit();
	//g_pFramework->Del();


	Gamefield& gamefield = Gamefield::instance();
	gamefield.init(0, 0, 0);
	std::cout << "check" << std::endl;
	while (true) {

	}

	RendererImpl::instance().destroy();

	return (0);


}