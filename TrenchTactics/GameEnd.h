#include "Sprite.hpp"
#include "SpriteText.h"

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

void initWinningScreen(bool winner);
void showWinningScreen();

private:
	GameEnd() {};
	shared_ptr<SpriteText> winningText;
	Sprite* winningScreen;

};