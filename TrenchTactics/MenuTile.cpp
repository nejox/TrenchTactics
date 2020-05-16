#include "MenuTile.h"

void MenuTile::setButton(std::shared_ptr<Button> button) {
	if (button) {
		button.get()->setPos(this->getPosX(), this->getPosY());
		this->button = button;
		this->button.get()->update();
	}
}

void MenuTile::removeButton() {
	if (this->button != nullptr) {
		this->button = nullptr;
		this->getSprite()->render(this->getPosX(), this->getPosY() - 12 * 64);
	}
}

	void MenuTile::removeButtonDisplay() 
	{
			this->getSprite()->render(this->getPosX(), this->getPosY() - 12 * 64);
	}
