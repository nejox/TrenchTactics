#include "MenuTile.h"

/**
 * set the button of a menutile and update the state of the button and render it.
 *
 * \param button
 */
void MenuTile::setButton(std::shared_ptr<Button> button) {
	if (button) {
		button.get()->setPos(this->getPosX(), this->getPosY());
		this->button = button;
		this->button.get()->update();
	}
}

/**
 * remove a button from a menutile and render the blank menu surface over it.
 *
 */
void MenuTile::removeButton() {
	if (this->button != nullptr) {
		this->button = nullptr;
		this->getSprite()->render(this->getPosX(), this->getPosY() - 12 * 64);
	}
}

/**
 * overrender a button to "move it to the background".
 *
 */
void MenuTile::removeButtonDisplay()
{
	this->getSprite()->render(this->getPosX(), this->getPosY() - 12 * 64);
}
