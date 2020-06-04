#include "Mainmenu.h"


void Mainmenu::initMenu()
{
	int x = ConfigReader::instance().getTechnicalConf()->getWindowSizeX() / 2 - 3 * 64;
	int y = ConfigReader::instance().getTechnicalConf()->getWindowSizeY() / 2 - 5 * 64;

	menu = new Sprite();
	menu->load("../Data/Sprites/Token/MENUE_MAIN.bmp");
	menu->setPos(x, y);

	menueText = new SpriteText(50);
	menueText->load("Menu");
	menueText->setPos((x + 48), (y + 16));

	int ButtonX = x + 34;
	int ButtonY = y + 128;

	std::shared_ptr<Button> button1 = std::make_shared<Button>(Button::BUTTONTYPE::STARTGAME);
	button1->setPos(ButtonX, ButtonY);
	buttons.push_back(button1);

	std::shared_ptr<SpriteText> textOption1 = std::make_shared<SpriteText>(40);
	textOption1->load("New Game");
	textOption1->setPos(ButtonX + 50, ButtonY + 8);
	texts.push_back(textOption1);

	std::shared_ptr<Button> button2 = std::make_shared<Button>(Button::BUTTONTYPE::STARTGAME);
	button2->setPos(ButtonX, (ButtonY + 96));
	buttons.push_back(button2);

	std::shared_ptr<SpriteText> textOption2 = std::make_shared<SpriteText>(40);
	textOption2->load("Tutorial");
	textOption2->setPos(ButtonX + 70, (ButtonY + 96) + 8);
	texts.push_back(textOption2);

	std::shared_ptr<Button> button3 = std::make_shared<Button>(Button::BUTTONTYPE::STARTGAME);
	button3->setPos(ButtonX, (ButtonY + 2 * 96));
	buttons.push_back(button3);

	std::shared_ptr<SpriteText> textOption3 = std::make_shared<SpriteText>(40);
	textOption3->load("Exit");
	textOption3->setPos(ButtonX + 120, (ButtonY + 2 * 96) + 8);
	texts.push_back(textOption3);

}

void Mainmenu::showMenu()
{

	this->menu->render();
	this->menueText->render();

	for (size_t i = 0; i < this->buttons.size(); i++)
	{
		buttons[i].get()->update();
	}

	for (size_t i = 0; i < texts.size(); i++)
	{
		texts[i]->render();
	}

}

int Mainmenu::getButtonTypeFromXY(int eventX, int eventY)
{
	int buttonSizeX = 320;
	int buttonSizeY = 71;
	// make sure a button was clicked
	int Btntype = 0;
	for (size_t i = 0; i < buttons.size(); i++)
	{
		int x = buttons[i]->getSprite()->getX();
		int y = buttons[i]->getSprite()->getY();
		if ((eventX >= x && eventX <= (x + buttonSizeX)) && (eventY >= y && eventY <= (y + buttonSizeY))) {
			Btntype = 40 + i % 3;
			break;
		}
		else {
			continue;
		}
	}
	
	return Btntype;
}

