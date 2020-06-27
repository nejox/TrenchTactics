#include "GameEnd.h"


void GameEnd::initWinningScreen(bool winner) {
	std::string winnerColor;
	if (winner) winnerColor = "Red";
	else winnerColor = "Blue";

	winningScreen = new Sprite();
	winningScreen->load("../Data/Sprites/Token/WIN.bmp");
	winningScreen->setPos(6 * 64, 64);

	winningText = make_shared<SpriteText>(50);
	winningText->load("Player " + winnerColor + " Won!");
	winningText->setPos(7 * 64 + 32, 4 * 64);


}

void GameEnd::showWinningScreen()
{
	this->winningScreen->render();
	this->winningText->render();
	
}

