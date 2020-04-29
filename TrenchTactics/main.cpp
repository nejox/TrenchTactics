#define SDL_MAIN_HANDLED


#include "Framework.hpp"
#include "Game.hpp"
#include "Logger.hpp"
#include "ConfigReader.h"
#include "RendererImpl.h"
#include "Unit.h"
#include "Gamefield.h"
#include "GameLoop.h"
#include "SpriteText.h"

/// <summary>
/// 
/// </summary>
/// <param name="argc"></param>
/// <param name="argv"></param>
/// <returns></returns>
int main(int argc, char* argv[])
{


	Logger::instance().log(LOGLEVEL::INFO, "Starting main");

	Game* game = new Game();
	game->initGame();

	return (0);


}