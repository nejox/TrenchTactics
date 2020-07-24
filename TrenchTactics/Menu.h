#pragma once
#include <vector>
#include "Button.h"

class Menu
{
public:
	Menu(const Menu&) = delete;
	Menu& operator=(const Menu&) = delete;
	Menu(Menu&&) = delete;
	Menu& operator=(Menu&&) = delete;
	~Menu() {}

	static auto& instance() {
		static Menu menu;
		return menu;
	}

public:
	void initMenu(bool mainmenu);
	void showMenu();
	int getButtonTypeFromXY(int x, int y);

	bool IsShowingMenu() {
		return this->showingMenu;
	}

	int getPosX() {
		return this->posX;
	}

	int getPosY() {
		return this->posY;
	}

	int getEndX() {
		return this->endX;
	}

	int getEndY() {
		return this->endY;
	}

private:
	Menu();

	int posX;
	int posY;
	int endX;
	int endY;

	bool isMainmenu;
	bool showingMenu = false;;
	std::shared_ptr<Sprite> menu = nullptr;
	std::shared_ptr<SpriteText> menueText = nullptr;
	std::vector<std::shared_ptr<Button>> buttons;
	std::vector<std::shared_ptr<SpriteText>> texts;

};
