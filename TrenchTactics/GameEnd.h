#include "Sprite.hpp"
#include "SpriteText.h"

/*
* game end class containing all fuctions show winning screen 
*/
class GameEnd {

public:
	GameEnd(const GameEnd&) = delete;
	GameEnd& operator=(const GameEnd&) = delete;
	GameEnd(GameEnd&&) = delete;
	GameEnd& operator=(GameEnd&&) = delete;
	~GameEnd() {}

	static auto& instance() {
		static GameEnd gameEnd;
		return gameEnd;
	}

	/*
*initializes winning screen sprites
*\param winner that will be shown on screen
*/
void initWinningScreen(bool winner);
/*
*renders winning screen and text
*/
void showWinningScreen();

private:
	GameEnd() {};
	shared_ptr<SpriteText> winningText;
	Sprite* winningScreen;

};