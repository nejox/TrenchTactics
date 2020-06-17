#pragma once
#include <iostream>
#include <vector>
#include "Sprite.hpp"
#include "Gamephases.h"
#include "StartTutorialEvent.h"

class Tutorial
{
public:
	Tutorial(const Tutorial&) = delete;
	Tutorial& operator=(const Tutorial&) = delete;
	Tutorial(Tutorial&&) = delete;
	Tutorial& operator=(Tutorial&&) = delete;
	~Tutorial() {}

	static auto& instance() {
		static Tutorial tut;
		return tut;
	}

	void initTutorial();
	void showTutorial();
	void handleMouseClick(int x, int y);
	
private:
	int posX;
	int posY;
	GAMEPHASES::TUTORIALPHASE currentPhase;
	std::vector<std::shared_ptr<Sprite>> tutorialTokens;

	Tutorial() {};

};

