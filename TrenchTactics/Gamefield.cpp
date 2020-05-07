#include "Gamefield.h"
#include "SpriteButton.h"

Gamefield::Gamefield() {
	//setting up the randomnumbergenerator
	srand(time(NULL));
	//making all parts of the map into shared pointers 
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
 * get a red spawn tile based on a pixel position x and y
 * returns nullptr when not valid
 *
 * \param posY
 * \param posX
 * \return
 */
std::shared_ptr<FieldTile> Gamefield::getSpawnFieldRed(int posY, int posX) {
	//changing coordinates from pixels to tiles
	posY = posY / 64;
	posX = posX / 64;
	//checking if horizontal position is out of red spawn
	if (posX >= 20 || posX < 18) {
		return nullptr;
	}
	//checking if vertical position is out of 
	else if (posY < 0 || posY >= 11) {
		return nullptr;
	}
	//checking if position is on red HQ
	else if (posY == 5 || posY == 6) {
		return nullptr;
	}
	//checking if position is in upper half of red spawn, if yes returns the tile
	else if (posY < 5) {
		return this->getSpawnRed().get()->at(posX - -20).at(posY);
	}
	//position can only be in bottom half of red spawn and returns rhe tile
	else {
		return this->getSpawnRed().get()->at(posX - 20).at(posY - 2);
	}

}

/**
 * get a blue spawn tile based on a pixel position x and y
 * returns nullptr when not valid
 *
 * \param posY
 * \param posX
 * \return
 */
std::shared_ptr<FieldTile> Gamefield::getSpawnFieldBlue(int posY, int posX) {
	//changing position from pixels to tiles
	posY = posY / 64;
	posX = posX / 64;

	//checking if horizontal position is out of blue spawn
	if (posX >= 2 || posX < 0) {
		return nullptr;
	}
	//checking if vertical position is out of blue spawn
	else if (posY < 0 || posY >= 11) {
		return nullptr;
	}
	//checking if position is on blue HQ
	else if (posY == 5 || posY == 6) {
		return nullptr;
	}
	//checking if position is in upper half of blue spawn, if yes returns the tile
	else if (posY < 5) {
		return this->getSpawnBlue().get()->at(posX).at(posY);
	}
	//position can only be in bottom half of blue spawn and returns the tile
	else {
		return this->getSpawnBlue().get()->at(posX).at(posY - 2);
	}

}


/**
 * get a menu tile based on a pixel position x and y
 * returns nullptr when not valid
 *
 * \param posX
 * \param posY
 * \return
 */
std::shared_ptr<MenuTile> Gamefield::getMenuTileFromXY(int posX, int posY) {
	posY = posY / 64 - 12;
	posX = posX / 64;

	if (posX >= 19) {
		return nullptr;
	}
	else if (posY != 1) {
		return nullptr;
	}
	else {
		return this->getMenuBar().get()->at(posX).at(posY);
	}
}

/**
 * get a field tile based on a pixel position x and y
 * returns nullptr when not valid
 *
 * \param posX
 * \param posY
 * \return
 */
std::shared_ptr<FieldTile> Gamefield::getFieldTileFromXY(int posX, int posY) {
	//change position from pixels to tiles of playingfield
	posY = posY / 64;
	posX = posX / 64 - 2;
	//checking if horizontal position is out of playingfield
	if (posX >= 18 || posX < 0) {
		return nullptr;
	}
	//checking if vertical position if out of playingfield
	else if (posY < 0 || posY >= 12) {
		return nullptr;
	}
	//position in playingfield, return the tile
	else {
		return this->getPlayingfield().get()->at(posX).at(posY);
	}
}

/**
 * get a spawn tile based on a pixel position x and y and the color of a player
 * returns nullptr when not valid
 *
 * \param colorRed
 * \param posX
 * \param posY
 * \return
 */
std::shared_ptr<FieldTile> Gamefield::getSpawnTileFromXY(bool colorRed, int posX, int posY) {
	//searches in red spawn
	if (colorRed) {
		return this->getSpawnFieldRed(posX, posY);
	}
	//searches in blue spawn
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
	
	//spawn unit for red player
	if (redPlayerActive) {
		activeSpawn = spawnRed;
		//iterates over the two spawncolumns from center to edge of map
		for (int i = 1; i > 0; --i) {
			//iterates over the tiles in the spawncolums
			for (int j = 0; j < 5; ++j) {
				//checks the upper half of the spawn for the next free tile in current column from center to the edge of map
				if (fieldTileIsFree(1 - i, 4 - j, activeSpawn)) {
					//sets the position of the new sprite, places unit on tile and gets the neutral-sprite for unit
					activeSpawn.get()->at(1 - i).at(4 - j)->setPos((1 - i) * 64 + 20 * 64, (4 - j) * 64);
					activeSpawn.get()->at(1 - i).at(4 - j)->setUnit(pUnit);
					return 1;
				}
				//checks the lower half of the spawn for the next free tile in current column from center to the edge of map
				if (fieldTileIsFree(1 - i, 5 + j, activeSpawn)) {
					//sets the position of the new sprite, places unit on tile and gets the neutral-sprite for unit
					activeSpawn.get()->at(1 - i).at(5 + j)->setPos((1 - i) * 64 + 20 * 64, (5 + j) * 64 + 2 * 64);
					activeSpawn.get()->at(1 - i).at(5 + j)->setUnit(pUnit);
					return 1;
				}
			}
		}
	}
	else {
		activeSpawn = spawnBlue;
		//iterates over the two spawncolumns from center to edge of map
		for (int i = 0; i < 2; ++i) {
			//iterates over the tiles in the spawncolums
			for (int j = 0; j < 5; ++j) {
				//checks the upper half of the spawn for the next free tile in current column from center to the edge of map
				if (fieldTileIsFree(1 - i, 4 - j, activeSpawn)) {
					//sets the position of the new sprite, places unit on tile and gets the neutral-sprite for unit
					activeSpawn.get()->at(1 - i).at(4 - j)->setPos((1 - i) * 64, (4 - j) * 64);
					activeSpawn.get()->at(1 - i).at(4 - j)->setUnit(pUnit);
					return 1;
				}
				//checks the lower half of the spawn for the next free tile in current column from center to the edge of map
				if (fieldTileIsFree(1 - i, 5 + j, activeSpawn)) {
					//sets the position of the new sprite, places unit on tile and gets the neutral-sprite for unit
					activeSpawn.get()->at(1 - i).at(5 + j)->setPos((1 - i) * 64, (5 + j) * 64 + 2 * 64);
					activeSpawn.get()->at(1 - i).at(5 + j)->setUnit(pUnit);
					return 1;
				}
			}
		}
	}

	return 0;
}

/**
 * Checks if there is no unit on a fieldtile. Position of the Tile is counted from top left corner of the field. Field can be a spawn or the playingfield.
 * No pixel position!
 *
 * \param x horizontal position in the field (can be a spawn or playingfield)
 * \param y vertical position in the field (can be a spawn or playingfield)
 * \param field Part of the field that contains the tile
 * \return
 */
bool Gamefield::fieldTileIsFree(int x, int y, std::shared_ptr<vector<vector<std::shared_ptr<FieldTile>>>> field)
{
	//checks for a unit at the given position in the field and returns false, if there is a unit in tile
	if (field->at(x).at(y).get()->getUnit().get()) {
		return false;
	}
	else {
		return true;
	}
}

/**
 * Function to search playingfield and both spawns for a tile on which a unit stands. Returns a nullpointer if unit was not found.
 *
 * \param pUnit unit to search for
 * \return tile holding the unit
 */
std::shared_ptr<FieldTile> Gamefield::findeTileByUnit(std::shared_ptr<Unit> pUnit)
{
	std::shared_ptr<FieldTile> pTileToTest = nullptr;

	//Iterates over columns of playingfield from left to right
	for (vector<vector<std::shared_ptr<FieldTile>>>::iterator xIter = playingfield->begin(); xIter != playingfield->end(); ++xIter) {
		//Iterates over the tiles in the column from top to bottom
		for (vector< std::shared_ptr<FieldTile>>::iterator yIter = xIter->begin(); yIter != xIter->end(); ++yIter) {
			//checks the current tile for the unit and returns the a pointer ti the tile, if the unit is found
			pTileToTest = *yIter;
			if (pTileToTest->getUnit() == pUnit) return pTileToTest;
		}
	}

	//Iterates over columns of blue spawn from left to right
	for (vector<vector<std::shared_ptr<FieldTile>>>::iterator xIter = spawnBlue->begin(); xIter != spawnBlue->end(); ++xIter) {
		//Iterates over the tiles in the column from top to bottom
		for (vector<std::shared_ptr<FieldTile>>::iterator yIter = xIter->begin(); yIter != xIter->end(); ++yIter) {
			//checks the current tile for the unit and returns the a pointer ti the tile, if the unit is found
			pTileToTest = *yIter;
			if (pTileToTest->getUnit() == pUnit) return pTileToTest;
		}
	}

	//Iterates over the columns of red spawn from left to right
	for (vector<vector<std::shared_ptr<FieldTile>>>::iterator xIter = spawnRed->begin(); xIter != spawnRed->end(); ++xIter) {
		//Iterates over the tiles in the column from top to bottom
		for (vector<std::shared_ptr<FieldTile>>::iterator yIter = xIter->begin(); yIter != xIter->end(); ++yIter) {
			//checks the current tile for the unit and returns the a pointer ti the tile, if the unit is found
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
	// change position from pixels to tiles
	x = x / 64;
	y = y / 64;
	std::shared_ptr<Tile> pSearchedTile = nullptr;

	//if position is in menu
	if ((0 <= x <= 21) && (12 <= y <= 14))
		pSearchedTile = Gamefield::menuBar.get()->at(x).at(y - 12);
	//if position is in playingfield
	if ((2 <= x <= 19) && (0 <= y <= 11))
		pSearchedTile = Gamefield::playingfield.get()->at(x - 2).at(y);
	//if position is in blue HQ
	if ((0 <= x <= 1) && (5 <= y <= 6))
		pSearchedTile = Gamefield::headquarterTilePlayerBlue.get()->at(x).at(y - 5);
	//if position is in red HQ
	if ((20 <= x <= 21) && (5 <= y <= 6))
		pSearchedTile = Gamefield::headquarterTilePlayerRed.get()->at(x - 20).at(y - 5);
	//if position is in top half of blue spawn
	if ((0 <= x <= 1) && (0 <= y <= 4))
		pSearchedTile = Gamefield::spawnBlue.get()->at(x).at(y);
	//if position is in bottom half of blue spawn
	if ((0 <= x <= 1) && (7 <= y <= 11))
		pSearchedTile = Gamefield::spawnBlue.get()->at(x).at(y - 2);
	//if position is in top half of red spawn
	if ((20 <= x <= 21) && (0 <= y <= 4))
		pSearchedTile = Gamefield::spawnRed.get()->at(x - 20).at(y);
	//if position is in bottom half of red spawn
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
	//change position from pixels to tiles
	xPos = xPos / 64;
	yPos = yPos / 64;
	//iterates over all tiles, that are in range of selected tile
	for (int i = -range; i <= range; ++i) {
		for (int j = (abs(i) - range); j <= abs(abs(i) - range); ++j) {
			//checks if the current tile is on playingfield
			if ((2 <= (xPos + i)) && ((xPos + i) <= 19) && (0 <= (yPos + j)) && ((yPos + j) <= 11)) {
				//mark the current tile
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
	//change position from pixels to tiles
	xPos = xPos / 64;
	yPos = yPos / 64;
	//select the chosen tile and mark tiles in range, if there is a unit on the tile markes the tiles in range of the unit
	playingfield.get()->at(xPos - 2).at(yPos)->setSelected(true);
	if (playingfield.get()->at(xPos - 2).at(yPos)->getUnit())
		markTilesAround(xPos * 64, yPos * 64, playingfield.get()->at(xPos - 2).at(yPos)->getUnit()->getRange());
}

/**
*
*Function to reset the selected- and marked-status for each spawn- and playingfieldtile.
*/
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
	for (vector<vector<std::shared_ptr<FieldTile>>>::iterator xIter1 = spawnBlue->begin(); xIter1 != spawnBlue->end(); ++xIter1) {
		for (vector<std::shared_ptr<FieldTile>>::iterator yIter1 = xIter1->begin(); yIter1 != xIter1->end(); ++yIter1) {
			yIter1->get()->setSelected(false);
		}
	}
	//deselects and unmarks the red player's spawn
	for (vector<vector<std::shared_ptr<FieldTile>>>::iterator xIter2 = spawnRed->begin(); xIter2 != spawnRed->end(); ++xIter2) {
		for (vector<std::shared_ptr<FieldTile>>::iterator yIter2 = xIter2->begin(); yIter2 != xIter2->end(); ++yIter2) {
			yIter2->get()->setSelected(false);
		}
	}

}

/**
 * get a random unit button sprite based on a provided rndNumber
 *
 * \param rndNumber
 * \return
 */
SpriteButton* Gamefield::getRandomUnitButtonSprite(int rndNumber) {
	SpriteButton* buttonSprite = new SpriteButton();

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

/**
 * display necessary buttons based on phase
 *
 * \param current gamephase
 */
void Gamefield::displayButtons(GAMEPHASES::GAMEPHASE phase) {
	if (phase == GAMEPHASES::BUY) {

		//create the three buttons
		std::shared_ptr<Button> button = std::make_shared<Button>();
		std::shared_ptr<Button> button1 = std::make_shared<Button>();
		std::shared_ptr<Button> button2 = std::make_shared<Button>();

		for (int i = 0; i < 3; i++) {
			int rnd = std::rand() % 3;

			//get sprite based on rnd number
			SpriteButton* buttonSprite = getRandomUnitButtonSprite(rnd);

			if (i == 0) {
				//set type, positon and reference
				button->setType(rnd);
				button->setSprite(buttonSprite);
				this->getMenuBar().get()->at(4).at(1).get()->setButton(button);
			}
			else if (i == 1) {
				button1->setType(rnd);
				button1->setSprite(buttonSprite);
				this->getMenuBar().get()->at(6).at(1).get()->setButton(button1);
			}
			else if (i == 2) {
				button2.get()->setType(rnd);
				button2.get()->setSprite(buttonSprite);
				this->getMenuBar().get()->at(8).at(1).get()->setButton(button2);
			}
		}
	}
	else if (phase == GAMEPHASES::MOVE || phase == GAMEPHASES::ATTACK)
	{
		//display buttons for next and previous unit
		std::shared_ptr<Button> previousUnitButton = std::make_shared<Button>();
		std::shared_ptr<Button> nextUnitButton = std::make_shared<Button>();
		SpriteButton* nextUnit = new SpriteButton();
		nextUnit->load("../Data/Sprites/Token/NEXTUNIT_TOKEN.bmp");
		SpriteButton* previousUnit = new SpriteButton();
		previousUnit->load("../Data/Sprites/Token/PREVIOUSUNIT_TOKEN.bmp");

		previousUnitButton->setSprite(nextUnit);
		//dummy values until now -> move to a config style file required
		previousUnitButton->setType(20);
		nextUnitButton->setSprite(previousUnit);
		nextUnitButton->setType(10);

		this->getMenuBar().get()->at(6).at(1).get()->setButton(previousUnitButton);
		this->getMenuBar().get()->at(5).at(1).get()->setButton(nextUnitButton);
	}

	//always display end phase and end turn buttons
	std::shared_ptr<Button> nextPhaseButton = std::make_shared<Button>();
	std::shared_ptr<Button> buttonEndTurn = std::make_shared<Button>();

	SpriteButton* nextPhase = new SpriteButton();
	nextPhase->load("../Data/Sprites/Token/NEXTPHASE_TOKEN.bmp");
	SpriteButton* nextTurn = new SpriteButton();
	nextTurn->load("../Data/Sprites/Token/ENDTURN_TOKEN.bmp");

	nextPhaseButton->setSprite(nextPhase);
	nextPhaseButton->setType(50);

	buttonEndTurn->setSprite(nextTurn);
	buttonEndTurn->setType(31);

	this->getMenuBar().get()->at(13).at(1).get()->setButton(nextPhaseButton);
	this->getMenuBar().get()->at(17).at(1).get()->setButton(buttonEndTurn);
}

/**
 *
 */
void Gamefield::deleteButtons() {
	for (int i = 4; i < 9; i++) {
		this->getMenuBar().get()->at(i).at(1).get()->removeButton();
	}
}



// ------------ Setupfunctions for gamestart -------------------------



/**
 * Creates a complete field tile based on position and terraintype
 *
 * \param posX position in pixel size X
 * \param posY position in pixel size Y
 * \param type Terraintype enum
 * \return
 */
std::shared_ptr<FieldTile> Gamefield::createFieldTile(int posX, int posY, FieldTile::TERRAINTYPE type) {
	std::shared_ptr<FieldTile> tmpFieldTilePointer = std::make_shared<FieldTile>();
	Sprite* terrainSprite = new Sprite();
	if (type == FieldTile::TERRAINTYPE::MUD) {
		tmpFieldTilePointer.get()->setTerrain(FieldTile::TERRAINTYPE::MUD);
		terrainSprite->load("../Data/Sprites/Terrain/TERRAIN_MUD_1.bmp");
	}
	else if (type == FieldTile::TERRAINTYPE::STONE) {
		tmpFieldTilePointer.get()->setTerrain(FieldTile::TERRAINTYPE::STONE);
		terrainSprite->load("../Data/Sprites/Terrain/TERRAIN_STONE_1.bmp");
	}
	else if (type == FieldTile::TERRAINTYPE::CLAY) {
		tmpFieldTilePointer.get()->setTerrain(FieldTile::TERRAINTYPE::CLAY);
		terrainSprite->load("../Data/Sprites/Terrain/TERRAIN_SAND_1.bmp");
	}
	terrainSprite->setPos(posX, posY);
	tmpFieldTilePointer->setSprite(terrainSprite);
	tmpFieldTilePointer->getSprite()->render();
	tmpFieldTilePointer->setPos(posX, posY);
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

				*yIter = createFieldTile((xIter - playingfield->begin()) * 64 + 2 * 64, (yIter - xIter->begin()) * 64, FieldTile::TERRAINTYPE::MUD);;
			}

			if (rnd == 4) {
				*yIter = createFieldTile((xIter - playingfield->begin()) * 64 + 2 * 64, (yIter - xIter->begin()) * 64, FieldTile::TERRAINTYPE::STONE);
			}

			if (rnd == 5) {
				*yIter = createFieldTile((xIter - playingfield->begin()) * 64 + 2 * 64, (yIter - xIter->begin()) * 64, FieldTile::TERRAINTYPE::CLAY);
			}
		}
	}
}


/**
 * Provides a random spawntile based on a number between 0 and 3 for red and blue side
 *
 * \param rndNumber number between 0 and 3
 * \param colorRed tile for red player or not
 * \return
 */
Sprite* Gamefield::getRandomSpawnTileSprite(int rndNumber, bool colorRed) {
	Sprite* terrainSprite = new Sprite();
	std::string path = "../Data/Sprites/Terrain/SPAWNTILE_";
	if (colorRed) {
		path = path + "RED_";
	}
	else {
		path = path + "BLUE_";
	}
	if (rndNumber == 0) {

		terrainSprite->load(path + std::to_string(rndNumber) + ".bmp");
	}
	else if (rndNumber == 1) {
		terrainSprite->load(path + std::to_string(rndNumber) + ".bmp");
	}

	else if (rndNumber == 2) {
		terrainSprite->load(path + std::to_string(rndNumber) + ".bmp");
	}
	else if (rndNumber == 3) {
		terrainSprite->load(path + std::to_string(rndNumber) + ".bmp");
	}
	return terrainSprite;
}

/**
 * Function to set up the fieldtiles in blue player's spawn at gamestart.
 *
 */
void Gamefield::initiateSpawnTilesBlue()
{
	int cnt = 0;
	Sprite* terrain = getRandomSpawnTileSprite(rand() % 4, false);
	for (vector<vector<std::shared_ptr<FieldTile>>>::iterator xIter = spawnBlue->begin(); xIter != spawnBlue->end(); ++xIter) {
		for (vector<std::shared_ptr<FieldTile>>::iterator yIter = xIter->begin(); yIter != xIter->end(); ++yIter) {
			if (cnt == 2) {
				cnt = 0;
				terrain = getRandomSpawnTileSprite(rand() % 4, false);
			}
			std::shared_ptr<FieldTile> tmpFieldTilePointer = std::make_shared<FieldTile>(FieldTile::TERRAINTYPE::SPAWNTERRAIN);

			if ((yIter - xIter->begin()) >= 5) {
				tmpFieldTilePointer->setSprite(terrain);
				tmpFieldTilePointer->setPos((xIter - spawnBlue->begin()) * 64, (yIter - xIter->begin()) * 64 + 2 * 64);
				tmpFieldTilePointer->getSprite()->render((xIter - spawnBlue->begin()) * 64, ((yIter - xIter->begin()) % 2 * 64));
			}
			else {
				tmpFieldTilePointer->setSprite(terrain);
				tmpFieldTilePointer->setPos((xIter - spawnBlue->begin()) * 64, (yIter - xIter->begin()) * 64);
				tmpFieldTilePointer->getSprite()->render((xIter - spawnBlue->begin()) * 64, ((yIter - xIter->begin()) % 2 * 64));
			}

			*yIter = tmpFieldTilePointer;
			cnt++;
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
	Sprite* terrain = getRandomSpawnTileSprite(rand() % 4, true);
	for (vector<vector<std::shared_ptr<FieldTile>>>::iterator xIter = spawnRed->begin(); xIter != spawnRed->end(); ++xIter) {
		for (vector<std::shared_ptr<FieldTile>>::iterator yIter = xIter->begin(); yIter != xIter->end(); ++yIter) {
			if (cnt == 2) {
				cnt = 0;
				terrain = getRandomSpawnTileSprite(rand() % 4, true);
			}
			std::shared_ptr<FieldTile> tmpFieldTilePointer = std::make_shared<FieldTile>(FieldTile::TERRAINTYPE::SPAWNTERRAIN);

			if ((yIter - xIter->begin()) >= 5) {
				terrain->setPos((xIter - spawnRed->begin()) * 64 + 20 * 64, (yIter - xIter->begin()) * 64 + 2 * 64);
				tmpFieldTilePointer->setSprite(terrain);
				tmpFieldTilePointer->setPos((xIter - spawnRed->begin()) * 64 + 20 * 64, (yIter - xIter->begin()) * 64 + 2 * 64);
				tmpFieldTilePointer->getSprite()->render((xIter - spawnRed->begin()) * 64, ((yIter - xIter->begin()) % 2 * 64));
			}
			else {
				terrain->setPos((xIter - spawnRed->begin()) * 64 + 20 * 64, (yIter - xIter->begin()) * 64);
				tmpFieldTilePointer->setSprite(terrain);
				tmpFieldTilePointer->setPos((xIter - spawnRed->begin()) * 64 + 20 * 64, (yIter - xIter->begin()) * 64);
				tmpFieldTilePointer->getSprite()->render((xIter - spawnRed->begin()) * 64, ((yIter - xIter->begin()) % 2 * 64));
			}

			*yIter = tmpFieldTilePointer;
			cnt++;
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
	std::shared_ptr<Headquarter> hq = make_shared<Headquarter>(false);

	for (vector<vector<std::shared_ptr<PlayerTile>>>::iterator xIter = headquarterTilePlayerBlue->begin(); xIter != headquarterTilePlayerBlue->end(); ++xIter) {
		for (vector<std::shared_ptr<PlayerTile>>::iterator yIter = xIter->begin(); yIter != xIter->end(); ++yIter) {
			// create PlayerTile as shared pointer 
			std::shared_ptr<PlayerTile> tmpMenuTilePointer = std::make_shared<PlayerTile>();
			//tmpMenuTilePointer->setHeadquarter(hq);

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

	//std::shared_ptr<Headquarter> hq = make_shared<Headquarter>(true);

	for (vector<vector<std::shared_ptr<PlayerTile>>>::iterator xIter = headquarterTilePlayerRed->begin(); xIter != headquarterTilePlayerRed->end(); ++xIter) {
		for (vector<std::shared_ptr<PlayerTile>>::iterator yIter = xIter->begin(); yIter != xIter->end(); ++yIter) {
			// create PlayerTile as shared pointer 
			std::shared_ptr<PlayerTile> tmpMenuTilePointer = std::make_shared<PlayerTile>();
			//tmpMenuTilePointer->setHeadquarter(hq);

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