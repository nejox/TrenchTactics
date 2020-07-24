#include "Menu.h"

Menu::Menu() {
	this->posX = 0;
	this->posY = 0;
	endX = 0;
	endY = 0;
}

void Menu::initMenu(bool mainmenu)
{
	posX = ConfigReader::instance().getTechnicalConf()->getWindowSizeX() / 2 - 3 * 64;
	posY = ConfigReader::instance().getTechnicalConf()->getWindowSizeY() / 2 - 5 * 64;

	isMainmenu = mainmenu;
	std::vector<Button::BUTTONTYPE> options;
	this->buttons.clear();
	this->texts.clear();

	int x = posX;
	int y = posY;

	if (isMainmenu) {

		menu = std::make_shared<Sprite>();
		menu->load("../Data/Sprites/Token/MENUE_MAIN.bmp");
		menu->setPos(x, y);

		this->endX = 384;
		this->endY = 448;

		menueText = std::make_shared<SpriteText>(50);
		menueText->load("Menu");
		menueText->setPos((x + 48), (y + 16));

		options.push_back(Button::STARTGAME);
		options.push_back(Button::TUTORIAL);
		options.push_back(Button::EXIT);
	}
	else {

		menu = std::make_shared<Sprite>();
		menu->load("../Data/Sprites/Token/MENU_INGAME.bmp");
		menu->setPos(x, y);

		this->endX = 384;
		this->endY = 372;

		options.push_back(Button::CONTINUE);
		options.push_back(Button::BACKTOMAIN);
		options.push_back(Button::EXIT);
	}

	int ButtonX = x + 34;
	int ButtonY = y + 128;


	for (Button::BUTTONTYPE option : options)
	{
		switch (option)
		{
		case Button::STARTGAME:
		{
			std::shared_ptr<Button> button = std::make_shared<Button>(Button::BUTTONTYPE::STARTGAME);
			button->setPos(ButtonX, ButtonY);
			buttons.push_back(button);

			std::shared_ptr<SpriteText> textOption = std::make_shared<SpriteText>(40);
			textOption->load("New Game");
			textOption->setPos(ButtonX + 50, ButtonY + 8);
			texts.push_back(textOption);
			break;
		}
		case Button::TUTORIAL:
		{
			std::shared_ptr<Button> button = std::make_shared<Button>(Button::BUTTONTYPE::TUTORIAL);
			button->setPos(ButtonX, (ButtonY + 96));
			buttons.push_back(button);

			std::shared_ptr<SpriteText> textOption = std::make_shared<SpriteText>(40);
			textOption->load("Tutorial");
			textOption->setPos(ButtonX + 70, (ButtonY + 96) + 8);
			texts.push_back(textOption);
			break;
		}
		case Button::CONTINUE:
		{
			int ingameY = ButtonY - 75;
			std::shared_ptr<Button> button = std::make_shared<Button>(Button::BUTTONTYPE::CONTINUE);
			button->setPos(ButtonX, ingameY);
			buttons.push_back(button);

			std::shared_ptr<SpriteText> textOption = std::make_shared<SpriteText>(40);
			textOption->load("Continue");
			textOption->setPos(ButtonX + 65, ingameY + 8);
			texts.push_back(textOption);
			break;
		}
		case Button::BACKTOMAIN:
		{
			int ingameY = ButtonY - 70;
			std::shared_ptr<Button> button = std::make_shared<Button>(Button::BUTTONTYPE::BACKTOMAIN);
			button->setPos(ButtonX, (ingameY + 96));
			buttons.push_back(button);

			std::shared_ptr<SpriteText> textOption = std::make_shared<SpriteText>(30);
			textOption->load("Back to Main Menu");
			textOption->setPos(ButtonX + 10, (ingameY + 96) + 15);
			texts.push_back(textOption);
			break;
		}
		case Button::EXIT:
		{
			int exitY = ButtonY + 2 * 96;

			if (!isMainmenu) {
				exitY = exitY - 60;
			}

			std::shared_ptr<Button> button = std::make_shared<Button>(Button::BUTTONTYPE::EXIT);
			button->setPos(ButtonX, exitY);
			buttons.push_back(button);

			std::shared_ptr<SpriteText> textOption = std::make_shared<SpriteText>(40);
			textOption->load("Exit");
			textOption->setPos(ButtonX + 120, exitY + 8);
			texts.push_back(textOption);
			break;
		}
		default:
			break;
		}
	}


}

void Menu::showMenu()
{
	showingMenu = true;

	this->menu->render();

	if (this->isMainmenu) {
		this->menueText->render();
	}

	for (size_t i = 0; i < this->buttons.size(); i++)
	{
		buttons[i].get()->update();
	}

	for (size_t i = 0; i < texts.size(); i++)
	{
		texts[i]->render();
	}

}

int Menu::getButtonTypeFromXY(int eventX, int eventY)
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
			Btntype = this->buttons[i]->getType();
			showingMenu = false;
			break;
		}
		else {
			continue;
		}
	}

	return Btntype;
}

