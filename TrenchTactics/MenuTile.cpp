#include "MenuTile.h"

void MenuTile::setButton(std::shared_ptr<Button> button) {
	if (button) {
		button.get()->getSprite()->setPos(this->getPosX(), this->getPosY());
		this->button = button;
		this->button.get()->getSprite()->render();//64, 0);
	}
}

void MenuTile::removeButton() {
	if (this->button != nullptr) {
		this->button = nullptr;
		this->getSprite()->render(this->getPosX(), this->getPosY() - 12 * 64);
	}
}