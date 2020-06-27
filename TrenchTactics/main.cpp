
#include "Logger.hpp"
#include "ConfigReader.h"
#include "RendererImpl.h"
#include "Unit.h"
#include "Gamefield.h"
#include "Game.h"
#include "SpriteText.h"

/**
 * Main function to start the game
 *
 * \param argc
 * \param argv
 * \return
 */
int main(int argc, char* argv[])
{
	Logger::instance().log(LOGLEVEL::INFO, "Starting main");
	Game* game = new Game();
	game->initGame();
    game->startMenu();

	return (0);
}