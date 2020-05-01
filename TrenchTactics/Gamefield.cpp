#include "Gamefield.h"

Gamefield::Gamefield() {
<<<<<<< HEAD
=======
	srand(time(NULL));
>>>>>>> 34f102274403816074528cf23dac2d7270c37396
	this->menuBar = std::make_shared<vector<vector<std::shared_ptr<MenuTile>>>>();
	this->headquarterTilePlayerBlue = std::make_shared<vector<vector<std::shared_ptr<PlayerTile>>>>();
	this->headquarterTilePlayerRed = std::make_shared<vector<vector<std::shared_ptr<PlayerTile>>>>();
	this->playingfield = std::make_shared<vector<vector<std::shared_ptr<FieldTile>>>>();
	this->spawnBlue = std::make_shared<vector<vector<std::shared_ptr<FieldTile>>>>();
	this->spawnRed = std::make_shared<vector<vector<std::shared_ptr<FieldTile>>>>();
}

Gamefield::~Gamefield() {
}

/**
 *
 *
 * \param posY
 * \param posX
 * \return
 */
std::shared_ptr<FieldTile> Gamefield::getSpawnFieldRed(int posY, int posX) {
	posY = posY / 64;
	posX = posX / 64;

	if (posX >= 20 || posX <= 18) {
		return nullptr;
	}
	else if (posY < 0 || posY >= 13) {
		return nullptr;
	}
	else {
		return this->getSpawnRed().get()->at(posX).at(posY);
	}

}

/**
 *
 *
 * \param posY
 * \param posX
 * \return
 */
std::shared_ptr<FieldTile> Gamefield::getSpawnFieldBlue(int posY, int posX) {
	posY = posY / 64;
	posX = posX / 64;


	if (posX >= 2 || posX <= 0) {
		return nullptr;
	}
	else if (posY < 0 || posY >= 13) {
		return nullptr;
	}
	else {
		return this->getSpawnBlue().get()->at(posX).at(posY);
	}

}


/**
 *
 *
 * \param posX
 * \param posY
 * \return
 */
std::shared_ptr<MenuTile> Gamefield::getMenuTileFromXY(int posX, int posY) {
	posY = posY / 64;
	posX = posX / 64;

	if (posY >= 19) {
		return nullptr;
	}
	else if (posX != 13) {
		return nullptr;
	}
	else {
		return std::shared_ptr<MenuTile>(menuBar.get()->at(posX).at(1));
	}
}

/**
 *
 *
 * \param posX
 * \param posY
 * \return
 */
std::shared_ptr<FieldTile> Gamefield::getFieldTileFromXY(int posX, int posY) {
	posY = posY / 64;
	posX = posX / 64;
	if (posX >= 19 || posX <= 1) {
		return nullptr;
	}
	else if (posY < 0 || posY >= 11) {
		return nullptr;
	}
	else {
		return this->getField().get()->at(posX).at(posY);
	}
}

/**
 *
 *
 * \param colorRed
 * \param posX
 * \param posY
 * \return
 */
std::shared_ptr<FieldTile> Gamefield::getSpawnTileFromXY(bool colorRed, int posX, int posY) {
	if (colorRed) {
		return this->getSpawnFieldRed(posX, posY);
	}
	else {
		return this->getSpawnFieldBlue(posX, posY);
	}
}

/**
 * Function that places a new unit in the active players spawn.
 * Returns 0 if spawn is full. Returns 1 if successful.
 * Traverses the spawn from mid of frontline to the corners.
 *
 * \param pUnit pointer to unit that has to be spawned
 * \param redPlayerActive show if red player is the active
 * \return
 */
int Gamefield::spawnUnitInSpawn(std::shared_ptr<Unit> pUnit, bool redPlayerActive)
{
	std::shared_ptr<vector<vector<std::shared_ptr<FieldTile>>>> activeSpawn;

	//funktioniert bisher nur bei default Groesse des Spielfelds.

	// 
	if (redPlayerActive) {
		activeSpawn = spawnRed;
		for (int i = 1; i > 0; --i) {
			for (int j = 0; j < 5; ++j) {
				if (fieldTileIsFree(1 - i, 4 - j, activeSpawn)) {
					pUnit->getSprite()->setPos((1 - i) * 64, (4 - j) * 64);
					pUnit->getSprite()->Sprite::render((1 - i) * 64, (4 - j) * 64);
					activeSpawn.get()->at(1 - i).at(4 - j)->setUnit(pUnit);
					pUnit.get()->update(STATES::STANDING_NEUTRAL);
					return 1;
				}
				if (fieldTileIsFree(1 - i, 5 + j, activeSpawn)) {
					pUnit->getSprite()->setPos((1 - i) * 64, (5 + j) * 64);
					pUnit->getSprite()->Sprite::render((1 - i) * 64, (5 + j) * 64);
					activeSpawn.get()->at(1 - i).at(5 + j)->setUnit(pUnit);
					pUnit.get()->update(STATES::STANDING_NEUTRAL);
					return 1;
				}
			}
		}
	}
	else {
		activeSpawn = spawnBlue;

		for (int i = 0; i < 2; ++i) {
			for (int j = 0; j < 5; ++j) {
				if (fieldTileIsFree(1 - i, 4 - j, activeSpawn)) {
					pUnit->getSprite()->setPos((1 - i) * 64, (4 - j) * 64);
					pUnit->getSprite()->Sprite::render((1 - i) * 64, (4 - j) * 64);
					activeSpawn.get()->at(1 - i).at(4 - j)->setUnit(pUnit);
					pUnit.get()->update(STATES::STANDING_NEUTRAL);
					return 1;
				}
				if (fieldTileIsFree(1 - i, 5 + j, activeSpawn)) {
					pUnit->getSprite()->setPos((1 - i) * 64, (5 + j) * 64);
					pUnit->getSprite()->Sprite::render((1 - i) * 64, (5 + j) * 64);
					activeSpawn.get()->at(1 - i).at(5 + j)->setUnit(pUnit);
					pUnit.get()->update(STATES::STANDING_NEUTRAL);
					return 1;
				}
			}
		}
	}
	
	return 0;
}

/**
 * Checks if a fieldtile is empty.
 *
 * \param x horizontal position
 * \param y vertical position
 * \param activeSpawn field that contains the tile
 * \return
 */
bool Gamefield::fieldTileIsFree(int x, int y, std::shared_ptr<vector<vector<std::shared_ptr<FieldTile>>>> field)
{
	if (field->at(x).at(y).get()) return true;
	return false;
}



/**
 * Function to search playingfield and both spawns for a tile on which a unit stands. Returns a nullpointer if unit was not found.
 *
 * \param pUnit unit to search for
 * \return tile holding the unit
 */
std::shared_ptr<FieldTile> Gamefield::findTileForUnit(std::shared_ptr<Unit> pUnit)
{
	std::shared_ptr<FieldTile> pTileToTest = nullptr;

	//Searches playingfield

	for (vector<vector<std::shared_ptr<FieldTile>>>::iterator xIter = playingfield->begin(); xIter != playingfield->end(); ++xIter) {
		for (vector< std::shared_ptr<FieldTile>>::iterator yIter = xIter->begin(); yIter != xIter->end(); ++yIter) {
			pTileToTest = *yIter;
			if (pTileToTest->getUnit() == pUnit) return pTileToTest;
		}
	}

	//Searches blue player's spawn

	for (vector<vector<std::shared_ptr<FieldTile>>>::iterator xIter = spawnBlue->begin(); xIter != spawnBlue->end(); ++xIter) {
		for (vector<std::shared_ptr<FieldTile>>::iterator yIter = xIter->begin(); yIter != xIter->end(); ++yIter) {
			pTileToTest = *yIter;
			if (pTileToTest->getUnit() == pUnit) return pTileToTest;
		}
	}

	//Searches red player's spawn

	for (vector<vector<std::shared_ptr<FieldTile>>>::iterator xIter = spawnRed->begin(); xIter != spawnRed->end(); ++xIter) {
		for (vector<std::shared_ptr<FieldTile>>::iterator yIter = xIter->begin(); yIter != xIter->end(); ++yIter) {
			pTileToTest = *yIter;
			if (pTileToTest->getUnit() == pUnit) return pTileToTest;
		}
	}

	return nullptr;
}

/**
 * Function to get a pointer to tile at x and y. x and y counting from top left.
 *
 * \param x Horizontal position of tile
 * \param y Vertical position of tile
 * \return Pointer to searched Tile.
 */
std::shared_ptr<Tile> Gamefield::getTilePointerAt(int x, int y)
{
	std::shared_ptr<Tile> pSearchedTile = NULL;


	if ((0 <= x <= 21) && (12 <= y <= 14))
		pSearchedTile = Gamefield::menuBar.get()->at(x).at(y - 12);

	if ((2 <= x <= 19) && (0 <= y <= 11))
		pSearchedTile = Gamefield::playingfield.get()->at(x - 2).at(y);

	if ((0 <= x <= 1) && (5 <= y <= 6))
		pSearchedTile = Gamefield::headquarterTilePlayerBlue.get()->at(x).at(y - 5);

	if ((20 <= x <= 21) && (5 <= y <= 6))
		pSearchedTile = Gamefield::headquarterTilePlayerRed.get()->at(x - 20).at(y - 5);

	if ((0 <= x <= 1) && (0 <= y <= 4))
		pSearchedTile = Gamefield::spawnBlue.get()->at(x).at(y);

	if ((0 <= x <= 1) && (7 <= y <= 11))
		pSearchedTile = Gamefield::spawnBlue.get()->at(x).at(y - 2);

	if ((20 <= x <= 21) && (0 <= y <= 4))
		pSearchedTile = Gamefield::spawnRed.get()->at(x - 20).at(y);

	if ((20 <= x <= 21) && (7 <= y <= 11))
		pSearchedTile = Gamefield::spawnRed.get()->at(x - 20).at(y - 2);

	return pSearchedTile;
}

/**
*Function to mark the tiles around a given tile as in range. Positions counting from top left tile in playingfield.
*
*\param xPos Horizontal postion of the tile
*\param yPos Vertical postion of the tile
*/
void Gamefield::markTilesAround(int xPos, int yPos, int range)
{
	for (int i = -range; i <= range; ++i) {
		for (int j = (abs(i) - range); j <= abs(abs(i) - range); ++j) {
			if ((2 <= (xPos + i)) && ((xPos + i) <= 19) && (0 <= (yPos + j)) && ((yPos + j) <= 11)) {
				Gamefield::playingfield.get()->at(xPos - 2 + i).at(yPos + j)->setMarked(true);
				SpriteMarker* tmpSprite = new SpriteMarker();
				tmpSprite->load("../Data/Sprites/Token/REACHABLE_MARKER.bmp");
				tmpSprite->makeTransparent();
				tmpSprite->setPos((xPos + i) * 64, (yPos + j) * 64);
				tmpSprite->render();
			}
		}
	}
}

/**
*Function to mark a tile as selected and call the function to mark surrounding tiles if needed. Positions counting from top left tile in playingfield.
*
*\param xPos Horizontal position of the tile
*\param yPos Vertical position of the tile
*/
void Gamefield::selectTile(int xPos, int yPos)
{
	playingfield.get()->at(xPos).at(yPos)->setSelected(true);
	if (playingfield.get()->at(xPos).at(yPos)->getUnit())
		markTilesAround(xPos, yPos, playingfield.get()->at(xPos).at(yPos)->getUnit()->getRange());
	//nur fuer angriffe; neue variante fuer bewegung noetig
}

/**
*
*Function to reset the selected- and marked-status for each spawn- and playingfieldtile.
*/
/*------------- Funktioniert noch nicht richtig ----------------------------------------------------------

void Gamefield::deselectAndUnmarkAllTiles()
{
	//deselects and unmarks the playingfield
	for (vector<vector<std::shared_ptr<FieldTile>>>::iterator xIter = playingfield->begin(); xIter != playingfield->end(); ++xIter) {
		for (vector<std::shared_ptr<FieldTile>>::iterator yIter = xIter->begin(); yIter != xIter->end(); ++yIter) {
			yIter->get()->setSelected(false);
			yIter->get()->setMarked(false);
			yIter->get()->getSprite()->render();
		}
	}
	//deselects and unmarks the blue player's spawn
	for (vector<vector<std::shared_ptr<FieldTile>>>::iterator xIter1 = spawnBlue->begin(); xIter1 != playingfield->end(); ++xIter1) {
		for (vector<std::shared_ptr<FieldTile>>::iterator yIter1 = xIter1->begin(); yIter1 != xIter1->end(); ++yIter1) {
			yIter1->get()->setSelected(false);
			yIter1->get()->setMarked(false);
			yIter1->get()->getSprite()->render();
		}
	}
	//deselects and unmarks the red player's spawn
	for (vector<vector<std::shared_ptr<FieldTile>>>::iterator xIter2 = playingfield->begin(); xIter2 != playingfield->end(); ++xIter2) {
		for (vector<std::shared_ptr<FieldTile>>::iterator yIter2 = xIter2->begin(); yIter2 != xIter2->end(); ++yIter2) {
			yIter2->get()->setSelected(false);
			yIter2->get()->setMarked(false);
			yIter2->get()->getSprite()->render();
		}
	}

}
<<<<<<< HEAD
-----------------------------------------------------------------------------------------------------------*/
=======

/**
 *
 *
 * \param rndNumber
 * \return
 */
Sprite* getRandomButtonSprite(int rndNumber) {
	Sprite* buttonSprite = new Sprite();

	if (rndNumber == 0) {
		buttonSprite->load("../Data/Sprites/Token/GRENADE_TOKEN.bmp");
	}
	else if (rndNumber == 1) {
		buttonSprite->load("../Data/Sprites/Token/GUNNER_TOKEN.bmp");
	}
	else if (rndNumber == 2) {
		buttonSprite->load("../Data/Sprites/Token/CC_TOKEN.bmp");
	}
	return buttonSprite;
}
>>>>>>> 34f102274403816074528cf23dac2d7270c37396

/**
 *
 *
 * \param
 */
void Gamefield::displayButtons(GAMEPHASES::GAMEPHASE phase) {
	if (phase == GAMEPHASES::BUY) {

		std::shared_ptr<Button> button = std::make_shared<Button>();
		std::shared_ptr<Button> button1 = std::make_shared<Button>();
		std::shared_ptr<Button> button2 = std::make_shared<Button>();

		for (int i = 0; i < 3; i++) {
			int rndo = std::rand() % 3;
			Sprite* buttonSprite = getRandomButtonSprite(rndo);

			if (i == 0) {
				button.get()->setType(rndo);
				button.get()->setSprite(buttonSprite);
				this->getMenuBar().get()->at(4).at(1).get()->setButton(button);
			}
			else if (i == 1) {
				button1.get()->setType(rndo);
				button1.get()->setSprite(buttonSprite);
				this->getMenuBar().get()->at(6).at(1).get()->setButton(button1);
			}
			else if (i == 2) {
				button2.get()->setType(rndo);
				button2.get()->setSprite(buttonSprite);
				this->getMenuBar().get()->at(8).at(1).get()->setButton(button2);
			}
		}

	}
	else if (phase == GAMEPHASES::MOVE)
	{

	}
	else if (phase == GAMEPHASES::ATTACK) {

	}

}

// ------------ Setupfunctions for gamestart -------------------------



/**
 *
 *
 * \param posX
 * \param posY
 * \param type
 * \return
 */
std::shared_ptr<FieldTile> createFieldTile(int posX, int posY, FieldTile::terrainType type) {
	std::shared_ptr<FieldTile> tmpFieldTilePointer = std::make_shared<FieldTile>();
	Sprite* terrainSprite = new Sprite();
	if (type == FieldTile::terrainType::clay) {
		tmpFieldTilePointer.get()->setTerrain(FieldTile::terrainType::clay);
		terrainSprite->load("../Data/Sprites/Terrain/TERRAIN_MUD_1.bmp");
	}
	else if (type == FieldTile::terrainType::mud) {
		tmpFieldTilePointer.get()->setTerrain(FieldTile::terrainType::clay);
		terrainSprite->load("../Data/Sprites/Terrain/TERRAIN_MUD_1.bmp");
	}
	else if (type == FieldTile::terrainType::stone) {
		tmpFieldTilePointer.get()->setTerrain(FieldTile::terrainType::clay);
		terrainSprite->load("../Data/Sprites/Terrain/TERRAIN_MUD_1.bmp");
	}
	terrainSprite->setPos(posX, posY);
	tmpFieldTilePointer->setSprite(terrainSprite);
	tmpFieldTilePointer->getSprite()->render();
	return tmpFieldTilePointer;
}

/**
 * Function to set up the fieldtiles in playingfield at gamestart.
 *
 */
void Gamefield::initiatePlayingFieldTiles()
{
	for (vector<vector<std::shared_ptr<FieldTile>>>::iterator xIter = playingfield->begin(); xIter != playingfield->end(); ++xIter) {
		for (vector<std::shared_ptr<FieldTile>>::iterator yIter = xIter->begin(); yIter != xIter->end(); ++yIter) {
			int rnd = rand() % 6;

			if (rnd <= 3) {

				*yIter = createFieldTile((xIter - playingfield->begin()) * 64 + 2 * 64, (yIter - xIter->begin()) * 64, FieldTile::terrainType::mud);;
			}

			if (rnd == 4) {
				*yIter = createFieldTile((xIter - playingfield->begin()) * 64 + 2 * 64, (yIter - xIter->begin()) * 64, FieldTile::terrainType::mud);
			}

			if (rnd == 5) {
				*yIter = createFieldTile((xIter - playingfield->begin()) * 64 + 2 * 64, (yIter - xIter->begin()) * 64, FieldTile::terrainType::mud);
			}
		}
	}
}

/**
 * Function to set up the fieldtiles in blue player's spawn at gamestart.
 *
 */
void Gamefield::initiateSpawnTilesBlue()
{
	int cnt = 0;
	for (vector<vector<std::shared_ptr<FieldTile>>>::iterator xIter = spawnBlue->begin(); xIter != spawnBlue->end(); ++xIter) {
		for (vector<std::shared_ptr<FieldTile>>::iterator yIter = xIter->begin(); yIter != xIter->end(); ++yIter) {

			std::shared_ptr<FieldTile> tmpFieldTilePointer = std::make_shared<FieldTile>(FieldTile::terrainType::spawnterrain);
			Sprite* terrainSprite = new Sprite();

			terrainSprite->load("../Data/Sprites/Terrain/SPAWNTILE_BLUE_" + std::to_string(cnt) + ".bmp");
			if ((yIter - xIter->begin()) >= 5) {
				terrainSprite->setPos((xIter - spawnBlue->begin()) * 64, (yIter - xIter->begin()) * 64 + 2 * 64);
				tmpFieldTilePointer->setSprite(terrainSprite);
				tmpFieldTilePointer->getSprite()->render(((xIter - spawnBlue->begin()) % 2) * 64, ((yIter - xIter->begin()) % 2) * 64);
			}
			else {
				terrainSprite->setPos((xIter - spawnBlue->begin()) * 64, (yIter - xIter->begin()) * 64);
				tmpFieldTilePointer->setSprite(terrainSprite);
				tmpFieldTilePointer->getSprite()->render(((xIter - spawnBlue->begin()) % 2) * 64, ((yIter - xIter->begin()) % 2) * 64);
			}

			*yIter = tmpFieldTilePointer;
			if ((((yIter - xIter->begin())) % 4) == 3) {
				cnt++;
				if (cnt == 4) {
					cnt = 0;
				}
			}
		}
	}
}

/**
 * Function to set up the fieldtiles in red player's spawn at gamestart.
 *
 */
void Gamefield::initiateSpawnTilesRed()
{
	int cnt = 0;
	for (vector<vector<std::shared_ptr<FieldTile>>>::iterator xIter = spawnRed->begin(); xIter != spawnRed->end(); ++xIter) {
		for (vector<std::shared_ptr<FieldTile>>::iterator yIter = xIter->begin(); yIter != xIter->end(); ++yIter) {
			if ((((xIter - spawnRed->begin()) + (yIter - xIter->begin())) % 5) == 4) {
				cnt++;
				if (cnt == 4) {
					cnt = 0;
				}
			}
			std::shared_ptr<FieldTile> tmpFieldTilePointer = std::make_shared<FieldTile>(FieldTile::terrainType::spawnterrain);
			Sprite* terrainSprite = new Sprite();
			terrainSprite->load("../Data/Sprites/Terrain/SPAWNTILE_RED_" + std::to_string(cnt) + ".bmp");
			if ((yIter - xIter->begin()) >= 5) {
				terrainSprite->setPos((xIter - spawnRed->begin()) * 64 + 20 * 64, (yIter - xIter->begin()) * 64 + 2 * 64);
				tmpFieldTilePointer->setSprite(terrainSprite);
				tmpFieldTilePointer->getSprite()->render(((xIter - spawnRed->begin()) % 2) * 64, ((yIter - xIter->begin()) % 2) * 64);
			}
			else {
				terrainSprite->setPos((xIter - spawnRed->begin()) * 64 + 20 * 64, (yIter - xIter->begin()) * 64);
				tmpFieldTilePointer->setSprite(terrainSprite);
				tmpFieldTilePointer->getSprite()->render((xIter - spawnRed->begin()) * 64, ((yIter - xIter->begin()) % 2) * 64);
			}

			*yIter = tmpFieldTilePointer;
		}
	}
}

/**
 * Function to set up the MenuTiles at gamestart.
 *
 */
void Gamefield::initiateMenuTiles()
{
	for (vector<vector<std::shared_ptr<MenuTile>>>::iterator xIter = menuBar->begin(); xIter != menuBar->end(); ++xIter) {
		for (vector<std::shared_ptr<MenuTile>>::iterator yIter = xIter->begin(); yIter != xIter->end(); ++yIter) {

			// create MenuTile as shared pointer 
			std::shared_ptr<MenuTile> tmpMenuTilePointer = std::make_shared<MenuTile>();

			// create Sprite and load menuBar file with all individual sprites
			Sprite* terrainSprite = new Sprite();
			terrainSprite->load("../Data/Sprites/Token/MENUE_BAR.bmp");

			// set pos where sprite shall be renderd
			terrainSprite->setPos((xIter - menuBar->begin()) * 64, (yIter - xIter->begin()) * 64 + 12 * 64);
			tmpMenuTilePointer->setSprite(terrainSprite);
			tmpMenuTilePointer->setPos((xIter - menuBar->begin()) * 64, (yIter - xIter->begin()) * 64 + 12 * 64);

			// tell render function to only render the specific 64*64 slice of whole menu
			tmpMenuTilePointer->getSprite()->render((xIter - menuBar->begin()) * 64, (yIter - xIter->begin()) * 64);
			*yIter = tmpMenuTilePointer;
		}
	}
}

/**
 * Function to set up the PlayerTiles for blue player at gamestart.
 *
 */
void Gamefield::initiatePlayerTilesBlue()
{
	for (vector<vector<std::shared_ptr<PlayerTile>>>::iterator xIter = headquarterTilePlayerBlue->begin(); xIter != headquarterTilePlayerBlue->end(); ++xIter) {
		for (vector<std::shared_ptr<PlayerTile>>::iterator yIter = xIter->begin(); yIter != xIter->end(); ++yIter) {
			// create PlayerTile as shared pointer 
			std::shared_ptr<PlayerTile> tmpMenuTilePointer = std::make_shared<PlayerTile>();

			// create Sprite and load menuBar file with all individual sprites
			Sprite* terrainSprite = new Sprite();
			terrainSprite->load("../Data/Sprites/HQ/B_HQ.bmp");

			// set pos where sprite shall be renderd

			terrainSprite->setPos((xIter - headquarterTilePlayerBlue->begin()) * 64, (yIter - xIter->begin()) * 64 + 5 * 64);
			tmpMenuTilePointer->setSprite(terrainSprite);

			// tell render function to only render the specific 64*64 slice of whole menu
			tmpMenuTilePointer->getSprite()->render((xIter - headquarterTilePlayerBlue->begin()) * 64, (yIter - xIter->begin()) * 64);
			*yIter = tmpMenuTilePointer;
		}
	}
}



/**
 * Function to set up the PlayerTiles for red player at gamestart.
*
 */
void Gamefield::initiatePlayerTilesRed()
{
	for (vector<vector<std::shared_ptr<PlayerTile>>>::iterator xIter = headquarterTilePlayerRed->begin(); xIter != headquarterTilePlayerRed->end(); ++xIter) {
		for (vector<std::shared_ptr<PlayerTile>>::iterator yIter = xIter->begin(); yIter != xIter->end(); ++yIter) {
			// create PlayerTile as shared pointer 
			std::shared_ptr<PlayerTile> tmpMenuTilePointer = std::make_shared<PlayerTile>();

			// create Sprite and load menuBar file with all individual sprites
			Sprite* terrainSprite = new Sprite();
			terrainSprite->load("../Data/Sprites/HQ/R_HQ.bmp");

			// set pos where sprite shall be renderd
			terrainSprite->setPos((xIter - headquarterTilePlayerRed->begin()) * 64 + 20 * 64, (yIter - xIter->begin()) * 64 + 5 * 64);
			tmpMenuTilePointer->setSprite(terrainSprite);

			// tell render function to only render the specific 64*64 slice of whole menu
			tmpMenuTilePointer->getSprite()->render((xIter - headquarterTilePlayerRed->begin()) * 64, (yIter - xIter->begin()) * 64);
			*yIter = tmpMenuTilePointer;
		}
	}
}


/**
 * Sets the number of tiles of each type at the start of the game.
 *
 */
void Gamefield::setAllFieldSizes()
{
	Gamefield::setSizePlayerTilesBlue();
	Gamefield::setSizePlayerTilesRed();
	Gamefield::setSizeMenuBar();
	Gamefield::setSizePlayingField();
	Gamefield::setSizeSpawnBlue();
	Gamefield::setSizeSpawnRed();

}

/**
 * Sets the size of the blue player's spawn to 2x2.
 *
 */
void Gamefield::setSizePlayerTilesBlue()
{
	headquarterTilePlayerBlue->resize(2);
	for (vector<vector<shared_ptr<PlayerTile>>>::iterator hqBlue = headquarterTilePlayerBlue->begin(); hqBlue != headquarterTilePlayerBlue->end(); ++hqBlue)
	{
		hqBlue->resize(2);
	}
}

/**
 * Sets the size of the blue player's spawn to 2x2.
 *
 */
void Gamefield::setSizePlayerTilesRed()
{
	headquarterTilePlayerRed->resize(2);
	for (vector<vector<shared_ptr<PlayerTile>>>::iterator hqRed = headquarterTilePlayerRed->begin(); hqRed != headquarterTilePlayerRed->end(); ++hqRed)
	{
		hqRed->resize(2);
	}
}

/**
 * Sets the size of the menubar at the gamestart.
 *
 */
void Gamefield::setSizeMenuBar()
{
	menuBar->resize(22);

	for (vector<vector<shared_ptr<MenuTile>>>::iterator menuCol = menuBar->begin(); menuCol != menuBar->end(); ++menuCol)
	{
		menuCol->resize(3);
	}

}

/**
 * Sets the size of the playingfield at the gamestart.
 *
 */
void Gamefield::setSizePlayingField()
{
	playingfield->resize(18);

	for (vector<vector<shared_ptr<FieldTile>>>::iterator fieldCol = playingfield->begin(); fieldCol != playingfield->end(); ++fieldCol)
	{
		fieldCol->resize(12);
	}
}

/**
 * Sets the size of blue player's spawn.
 *
 */
void Gamefield::setSizeSpawnBlue()
{
	spawnBlue->resize(2);
	for (vector<vector<shared_ptr<FieldTile>>>::iterator spawnCol = spawnBlue->begin(); spawnCol != spawnBlue->end(); ++spawnCol)
	{
		spawnCol->resize(10);
	}
}

/**
 * Sets the size of red player's spawn.
 *
 */
void Gamefield::setSizeSpawnRed()
{
	spawnRed->resize(2);
	for (vector<vector<shared_ptr<FieldTile>>>::iterator spawnCol = spawnRed->begin(); spawnCol != spawnRed->end(); ++spawnCol)
	{
		spawnCol->resize(10);
	}
}


/**
 * Function for setting up the gamefield at the start of a new game.
 *
 * \param FieldWidth int for delacring width of playingfield. Not used yet.
 * \param FieldHeight int for delacring height of playingfield. Not used yet.
 * \param Seed int for regenerating certain playingfieldlayout. Not used yet.
 */
void Gamefield::init(int FieldWidth, int FieldHeight, int Seed) {
	menuBar = std::make_shared<vector<vector<std::shared_ptr<MenuTile>>>>();
	playingfield = std::make_shared<vector<vector<std::shared_ptr<FieldTile>>>>();
	spawnBlue = std::make_shared<vector<vector<std::shared_ptr<FieldTile>>>>();
	spawnRed = std::make_shared<vector<vector<std::shared_ptr<FieldTile>>>>();
	headquarterTilePlayerBlue = std::make_shared<vector<vector<std::shared_ptr<PlayerTile>>>>();
	headquarterTilePlayerRed = std::make_shared<vector<vector<std::shared_ptr<PlayerTile>>>>();
	Gamefield::setAllFieldSizes();
	Gamefield::initiatePlayerTilesBlue();
	Gamefield::initiatePlayerTilesRed();
	Gamefield::initiateMenuTiles();
	Gamefield::initiateSpawnTilesBlue();
	Gamefield::initiateSpawnTilesRed();
	Gamefield::initiatePlayingFieldTiles();

}