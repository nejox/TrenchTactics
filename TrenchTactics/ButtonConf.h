#pragma once
#include <string>

/**
 * ButtonConf provides all necessary information about all buttons and their sprites
 * currently only sprite file paths
 */
class ButtonConf {
private:
	std::string grenadeTokenSprite;
	std::string gunnerTokenSprite;
	std::string ccTokenSprite;
	std::string previousUnitTokenSprite;
	std::string nextUnitTokenSprite;
	std::string digTokenSprite;
	std::string confirmTokenSprite;
	std::string cancelTokenSprite;
	std::string rerollTokenSprite;
	std::string addTokenSprite;
	std::string endTurnTokenSprite;
	std::string nextPhaseTokenSprite;
	std::string blankTokenSprite;

public:
	std::string getGrenadeTokenSprite() {
		return this->grenadeTokenSprite;
	}
	void setGrenadeTokenSprite(std::string grenadeTokenSprite) {
		this->grenadeTokenSprite = grenadeTokenSprite;
	}
	std::string getGunnerTokenSprite() {
		return this->gunnerTokenSprite;
	}
	void setGunnerTokenSprite(std::string gunnerTokenSprite) {
		this->gunnerTokenSprite = gunnerTokenSprite;
	}
	std::string getCCTokenSprite() {
		return this->ccTokenSprite;
	}
	void setCCTokenSprite(std::string ccTokenSprite) {
		this->ccTokenSprite = ccTokenSprite;
	}
	std::string getPreviousUnitTokenSprite() {
		return this->previousUnitTokenSprite;
	}
	void setPreviousUnitTokenSprite(std::string previousUnitTokenSprite) {
		this->previousUnitTokenSprite = previousUnitTokenSprite;
	}
	std::string getNextUnitTokenSprite() {
		return this->nextUnitTokenSprite;
	}
	void setNextUnitTokenSprite(std::string nextUnitTokenSprite) {
		this->nextUnitTokenSprite = nextUnitTokenSprite;
	}
	std::string getDigTokenSprite() {
		return this->digTokenSprite;
	}
	void setDigTokenSprite(std::string digTokenSprite) {
		this->digTokenSprite = digTokenSprite;
	}
	std::string getConfirmTokenSprite() {
		return this->confirmTokenSprite;
	}
	void setConfirmTokenSprite(std::string confirmTokenSprite) {
		this->confirmTokenSprite = confirmTokenSprite;
	}
	std::string getCancelTokenSprite() {
		return this->cancelTokenSprite;
	}
	void setCancelTokenSprite(std::string cancelTokenSprite) {
		this->cancelTokenSprite = cancelTokenSprite;
	}
	std::string getRerollTokenSprite() {
		return this->rerollTokenSprite;
	}
	void setRerollTokenSprite(std::string rerrollTokenSprite) {
		this->rerollTokenSprite = rerollTokenSprite;
	}
	std::string getAddTokenSprite() {
		return this->addTokenSprite;
	}
	void setAddTokenSprite(std::string addTokenSprite) {
		this->addTokenSprite = addTokenSprite;
	}
	std::string getEndTurnTokenSprite() {
		return this->endTurnTokenSprite;
	}
	void setEndTurnTokenSprite(std::string endTurnTokenSprite) {
		this->endTurnTokenSprite = endTurnTokenSprite;
	}
	std::string getNextPhaseTokenSprite() {
		return this->nextPhaseTokenSprite;
	}
	void setNextPhaseTokenSprite(std::string nextPhaseTokenSprite) {
		this->nextPhaseTokenSprite = nextPhaseTokenSprite;
	}
	std::string getBlankTokenSprite() {
		return this->blankTokenSprite;
	}
	void setBlankTokenSprite(std::string blankTokenSprite) {
		this->blankTokenSprite = blankTokenSprite;
	}
};