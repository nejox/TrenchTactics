#pragma once
#include <vector>
#include "Button.h"

class Mainmenu
{
public:
	Mainmenu(const Mainmenu&) = delete;
	Mainmenu& operator=(const Mainmenu&) = delete;
	Mainmenu(Mainmenu&&) = delete;
	Mainmenu& operator=(Mainmenu&&) = delete;
	~Mainmenu() {}

	static auto& instance() {
		static Mainmenu menu;
		return menu;
	}

public:
	void initMenu();
	void showMenu();

	int getButtonTypeFromXY(int x, int y);

private:
	Mainmenu() {};
	Sprite* menu = nullptr;
	SpriteText* menueText = nullptr;
	std::vector<std::shared_ptr<Button>> buttons;
	std::vector<std::shared_ptr<SpriteText>> texts;

};
