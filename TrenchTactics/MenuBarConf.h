#pragma once
#include <string>


/**
 * MenuBarConf provides necessary information concerning menubar specific stuff
 */
class MenuBarConf {
private:
	std::string menuBarBaseSprite;
	std::string redPlayerActiveFlagSprite;
	std::string bluePlayerActiveFlagSprite;
	std::string buyPhaseTokenSprite;
	std::string movePhaseTokenSprite;
	std::string attackPhaseTokenSprite;

public:
	std::string getMenuBarBaseSprite() {
		return this->menuBarBaseSprite;
	}
	void setMenuBarBaseSprite(std::string menuBarBaseSprite) {
		this->menuBarBaseSprite = menuBarBaseSprite;
	}
	std::string getRedPlayerActiveFlagSprite() {
		return this->redPlayerActiveFlagSprite;
	}
	void setRedPlayerActiveFlagSprite(std::string redPlayerActiveFlagSprite) {
		this->redPlayerActiveFlagSprite = redPlayerActiveFlagSprite;
	}
	std::string getBluePlayerActiveFlagSprite() {
		return this->bluePlayerActiveFlagSprite;
	}
	void setBluePlayerActiveFlagSprite(std::string bluePlayerActiveFlagSprite) {
		this->bluePlayerActiveFlagSprite = bluePlayerActiveFlagSprite;
	}
	std::string getBuyphaseTokenSprite() {
		return this->buyPhaseTokenSprite;
	}
	void setBuyPhaseTokenSprite(std::string buyPhaseTokenSprite) {
		this->buyPhaseTokenSprite = buyPhaseTokenSprite;
	}
	std::string getMovePhaseTokenSprite() {
		return this->movePhaseTokenSprite;
	}
	void setMovePhaseTokenSprite(std::string movePhaseTokenSprite) {
		this->movePhaseTokenSprite = movePhaseTokenSprite;
	}
	std::string getAttackPhaseTokenSprite() {
		return this->attackPhaseTokenSprite;
	}
	void setAttackPhaseTokenSprite(std::string attackPhaseTokenSprite) {
		this->attackPhaseTokenSprite = attackPhaseTokenSprite;
	}
};