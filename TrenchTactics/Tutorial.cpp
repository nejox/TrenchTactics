#include "Tutorial.h"


void Tutorial::initTutorial()
{
	this->currentPhase = GAMEPHASES::TUTORIALPHASE::INTRO;

	for (GAMEPHASES::TUTORIALPHASE phase : GAMEPHASES::TutAll) {

		switch (phase)
		{
		case GAMEPHASES::INTRO:
		{
			std::shared_ptr<Sprite> tokenSprite = std::make_shared<Sprite>();
			tokenSprite->load("../Data/Sprites/Tutorial/INTRO.bmp");
			tutorialTokens.push_back(tokenSprite);
			break;
		}
		case GAMEPHASES::MENU:
		{
			std::shared_ptr<Sprite> tokenSprite = std::make_shared<Sprite>();
			tokenSprite->load("../Data/Sprites/Tutorial/MENU.bmp");
			tutorialTokens.push_back(tokenSprite);
			break;
		}
		case GAMEPHASES::UNITS:
		{
			std::shared_ptr<Sprite> tokenSprite = std::make_shared<Sprite>();
			tokenSprite->load("../Data/Sprites/Tutorial/UNITS.bmp");
			tutorialTokens.push_back(tokenSprite);
			break;
		}
		case GAMEPHASES::TUT_BUY:
		{
			std::shared_ptr<Sprite> tokenSprite = std::make_shared<Sprite>();
			tokenSprite->load("../Data/Sprites/Tutorial/BUYPHASE.bmp");
			tutorialTokens.push_back(tokenSprite);
			break;
		}
		case GAMEPHASES::TUT_MOVE:
		{
			std::shared_ptr<Sprite> tokenSprite = std::make_shared<Sprite>();
			tokenSprite->load("../Data/Sprites/Tutorial/MOVEPHASE.bmp");
			tutorialTokens.push_back(tokenSprite);
			break;
		}
		case GAMEPHASES::TUT_ATTACK:
		{
			std::shared_ptr<Sprite> tokenSprite = std::make_shared<Sprite>();
			tokenSprite->load("../Data/Sprites/Tutorial/ATTACKPHASE.bmp");
			tutorialTokens.push_back(tokenSprite);
			break;
		}
		default:
			break;
		}
	}

	posX = 6 * 64;
	posY = 1 * 64;

	for (size_t i = 0; i < tutorialTokens.size(); i++)
	{
		tutorialTokens[i]->setPos(posX, posY);
	}

}

void Tutorial::showTutorial()
{

	tutorialTokens[currentPhase]->render();

}

void Tutorial::handleMouseClick(int x, int y)
{
	int buttonSizeX = 640;
	int buttonSizeY = 448;
	
	//if mouse click is in the tutorial popup, show next one
	if (x >= posX && x <= (posX + buttonSizeX) && y >= posY && y <= (posY + buttonSizeY)) {
		switch (currentPhase)
		{
		case GAMEPHASES::INTRO:
			currentPhase = GAMEPHASES::MENU;
			showTutorial();
			break;
		case GAMEPHASES::MENU:
			currentPhase = GAMEPHASES::UNITS;
			showTutorial();
			break;
		case GAMEPHASES::UNITS:
			currentPhase = GAMEPHASES::TUT_BUY;
			showTutorial();
			break;
		case GAMEPHASES::TUT_BUY:
			currentPhase = GAMEPHASES::TUT_MOVE;
			showTutorial();
			break;
		case GAMEPHASES::TUT_MOVE:
			currentPhase = GAMEPHASES::TUT_ATTACK;
			showTutorial();
			break;
		case GAMEPHASES::TUT_ATTACK:
			currentPhase = GAMEPHASES::INTRO;
			EventBus::instance().publish(new EndTutorialEvent(posX,(posX+buttonSizeX),posY,(posY+buttonSizeY)));
			break;
		default:
			break;
		}
	}
}
