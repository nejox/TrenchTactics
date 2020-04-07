#define SDL_MAIN_HANDLED

#include "Framework.hpp"
#include "Game.hpp"
#include "Logger.hpp"

/// <summary>
/// 
/// </summary>
/// <param name="argc"></param>
/// <param name="argv"></param>
/// <returns></returns>
int main(int argc, char* argv[])
{
	Log.log(LOGLEVEL::INFO, "Game started");

	if (g_pFramework->Init(1408, 768, 16, false) == false)
		return (0);

	CGame Game;
	Game.Init();
	Game.Run();
	Game.Quit();

	g_pFramework->Quit();
	g_pFramework->Del();

	return (0);
}