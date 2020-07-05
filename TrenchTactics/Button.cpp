#include "Button.h"

/**
 * Set the type of the created button
 * triggers the loading of the cost as well as the loading of the specific sprite from the config
 *
 * \param type the buttontype you want to create
 */
void Button::setType(BUTTONTYPE type) {
	this->type = type;
	this->loadSpriteFromType(type);
	this->loadCostFromType(type);
}

/**
 * Set the x and y position of a button
 *
 * \param x the x coordinate in pixel value
 * \param y the y coordinate in pixel value
 */
void Button::setPos(int x, int y)
{
	this->sprite->setPos(x, y);
	if (this->cost != 0) {
		this->costText->setPos(x + 18, y + 58);
	}

}

/**
 * Push the given button - changes the state of the button even if it is already pressed
 * Pushing a pressed button resets it
 *
 */
void Button::push() {
	this->pressed = (!(this->pressed));
}

/**
 * Update the Button and render its current state
 *
 */
void Button::update() {
	if (sprite != nullptr) {
		sprite->render(pressed);
		costText->render();
	}
}

/**
 * Load a Button Sprite specified by the supplied type
 *
 * \param type int value for button type
 */
void Button::loadSpriteFromType(int type)
{
	std::shared_ptr<ButtonConf> buttonConf = ConfigReader::instance().getButtonConf();
	switch (type)
	{
	case 0:
		this->sprite->load(buttonConf->getGrenadeTokenSprite());
		break;
	case 1:
		this->sprite->load(buttonConf->getGunnerTokenSprite());
		break;
	case 2:
		this->sprite->load(buttonConf->getCCTokenSprite());
		break;
	case 10:
		this->sprite->load(buttonConf->getPreviousUnitTokenSprite());
		break;
	case 11:
		this->sprite->load(buttonConf->getNextUnitTokenSprite());
		break;
	case 12:
		this->sprite->load(buttonConf->getDigTokenSprite());
		break;
	case 20:
		this->sprite->load(buttonConf->getConfirmTokenSprite());
		break;
	case 21:
		this->sprite->load(buttonConf->getCancelTokenSprite());
		break;
	case 22:
		this->sprite->load(buttonConf->getRerollTokenSprite());
		break;
	case 23:
		this->sprite->load(buttonConf->getAddTokenSprite());
		break;
	case 30:
		this->sprite->load(buttonConf->getEndTurnTokenSprite());
		break;
	case 31:
		this->sprite->load(buttonConf->getNextPhaseTokenSprite());
		break;
	case 40:
	case 41:
	case 42:
	case 43:
	case 45:
		this->sprite->load(buttonConf->getMainMenuButtonSprite());
		break;
	default:
		this->sprite->load(buttonConf->getBlankTokenSprite());
	}
}


/**
 * Read the cost of a unit from the config based on the supplied type
 *
 *
 * \param type unittype to get specific cost
 */
void Button::loadCostFromType(int type)
{
	if (type >= 0 && type < 3) {
		this->cost = ConfigReader::instance().getUnitConf(type)->getCost();
		this->costText->load(std::to_string(cost));
	}
	else if (type == 22) {
		this->cost = ConfigReader::instance().getBalanceConf()->getRerollCost();
		this->costText->load(std::to_string(cost));
	}
	else if (type == 23) {
		this->cost = ConfigReader::instance().getBalanceConf()->getAdditionalUnitRollCost();
		this->costText->load(" " + std::to_string(cost));
	}
	else {
		this->cost = 0; //TO DO: um später möglichkeit zu haben kosten unter confirm button zu zeigen
	}
}