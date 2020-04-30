#include "Gamefield.h"

Gamefield::Gamefield() {
}

Gamefield::~Gamefield() {
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
	if (redPlayerActive)
		activeSpawn = spawnRed;
	else
		activeSpawn = spawnBlue;


	//funktioniert bisher nur bei default Groesse des Spielfelds.
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 5; ++j) {
			if (fieldTileIsFree(1 - i, 4 - j, *activeSpawn)) {
				(*activeSpawn)[1 - i][4 - j]->setUnit(pUnit);
				//startAnimation richtige Funktion? Hab beim Renderer noch keinen Ueberblick
				//RendererImpl::instance().startAnimation((*activeSpawn)[1 - i][4 - j]->getUnit()->getSpriteFilePathStanding());
				return 1;
			}
			if (fieldTileIsFree(1 - i, 5 + j, *activeSpawn)) {
				(*activeSpawn)[1 - i][5 + j]->setUnit(pUnit);
				//startAnimation richtige Funktion? Hab beim Renderer noch keinen Ueberblick
				//RendererImpl::instance().startAnimation((*activeSpawn)[1 - i][4 - j]->getUnit()->getSpriteFilePathStanding());
				return 1;
			}
		}
	}
	pUnit.get()->update(STATES::STANDING_NEUTRAL);
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
bool Gamefield::fieldTileIsFree(int x, int y, vector<vector<std::shared_ptr<FieldTile>>> activeSpawn)
{
	if (activeSpawn[x][y] == nullptr) return true;
	return false;
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

			// tell render function to only render the specific 64*64 slice of whole menu
			tmpMenuTilePointer->getSprite()->render((xIter - menuBar->begin()) * 64, (yIter - xIter->begin()) * 64);
			*yIter = tmpMenuTilePointer;
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
 * Function to set up the fieldtiles in playingfield at gamestart.
 *
 */
void Gamefield::initiatePlayingFieldTiles()
{
	for (vector<vector<std::shared_ptr<FieldTile>>>::iterator xIter = playingfield->begin(); xIter != playingfield->end(); ++xIter) {
		for (vector<std::shared_ptr<FieldTile>>::iterator yIter = xIter->begin(); yIter != xIter->end(); ++yIter) {
			int rnd = rand() % 6;

			if (rnd <= 3) {

				std::shared_ptr<FieldTile> tmpFieldTilePointer = std::make_shared<FieldTile>(FieldTile::terrainType::mud);
				Sprite* terrainSprite = new Sprite();
				terrainSprite->load("../Data/Sprites/Terrain/TERRAIN_SAND_1.bmp");
				terrainSprite->setPos((xIter - playingfield->begin()) * 64 + 2 * 64, (yIter - xIter->begin()) * 64);
				tmpFieldTilePointer->setSprite(terrainSprite);
				tmpFieldTilePointer->getSprite()->render();
				*yIter = tmpFieldTilePointer;
			}
			if (rnd == 4) {

				std::shared_ptr<FieldTile> tmpFieldTilePointer = std::make_shared<FieldTile>(FieldTile::terrainType::mud);
				Sprite* terrainSprite = new Sprite();
				terrainSprite->load("../Data/Sprites/Terrain/TERRAIN_STONE_1.bmp");
				terrainSprite->setPos((xIter - playingfield->begin()) * 64 + 2 * 64, (yIter - xIter->begin()) * 64);
				tmpFieldTilePointer->setSprite(terrainSprite);
				tmpFieldTilePointer->getSprite()->render();
				*yIter = tmpFieldTilePointer;
			}
			if (rnd == 5) {

				std::shared_ptr<FieldTile> tmpFieldTilePointer = std::make_shared<FieldTile>(FieldTile::terrainType::mud);
				Sprite* terrainSprite = new Sprite();
				terrainSprite->load("../Data/Sprites/Terrain/TERRAIN_MUD_1.bmp");
				terrainSprite->setPos((xIter - playingfield->begin()) * 64 + 2 * 64, (yIter - xIter->begin()) * 64);
				tmpFieldTilePointer->setSprite(terrainSprite);
				tmpFieldTilePointer->getSprite()->render();
				*yIter = tmpFieldTilePointer;
			}
		}
	}
}

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
		std::unique_ptr<Sprite> buttonSprite = std::make_unique<Sprite>();
		std::unique_ptr<Sprite> buttonSprite1 = std::make_unique<Sprite>();
		std::unique_ptr<Sprite> buttonSprite2 = std::make_unique<Sprite>();

		buttonSprite->load("../Data/Sprites/Token/GRENADE_TOKEN.bmp");
		buttonSprite1->load("../Data/Sprites/Token/GUNNER_TOKEN.bmp");
		buttonSprite2->load("../Data/Sprites/Token/CC_TOKEN.bmp");
		/**
		 * 			if (rnd == 1) {
						buttonSprite->load("../Data/Sprites/Token/GRENADE_TOKEN.bmp");
					}
					else if (rnd == 2) {
						buttonSprite->load("../Data/Sprites/Token/GUNNER_TOKEN.bmp");
					}
					else if (rnd == 3) {
						buttonSprite->load("../Data/Sprites/Token/CC_TOKEN.bmp");
					}
		 *
		 * \param phase
		 */
		for (int i = 0; i < 3; i++)
		{
			if (i == 0) {
				buttonSprite->setPos(i * 2 * 64 + 5 * 64, 64 * 13);
				button.get()->setSprite(buttonSprite.get());
				button.get()->getSprite()->render(64, 0);
			}
			else if (i == 1) {
				buttonSprite1->setPos(i * 2 * 64 + 5 * 64, 64 * 13);
				button1.get()->setSprite(buttonSprite1.get());
				button1.get()->getSprite()->render(64, 0);
			}
			else if (i == 2) {
				buttonSprite2->setPos(i * 2 * 64 + 5 * 64, 64 * 13);
				button2.get()->setSprite(buttonSprite2.get());
				button2.get()->getSprite()->render(64, 0);
			}
		}

	}
	else if (phase == GAMEPHASES::MOVE)
	{

	}
	else if (phase == GAMEPHASES::ATTACK) {

	}

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

	if ((12 <= x <= 14) && (0 <= y <= 21))
		pSearchedTile = Gamefield::menuBar.get()->at(x).at(y);

	if ((2 <= x <= 19) && (0 <= y <= 11))
		pSearchedTile = Gamefield::menuBar.get()->at(x - 2).at(y);

	if ((0 <= x <= 1) && (5 <= y <= 6))
		Gamefield::headquarterTilePlayerBlue.get()[x][y - 5];

	if ((20 <= x <= 21) && (5 <= y <= 6))
		Gamefield::headquarterTilePlayerRed.get()[x - 20][y - 5];

	if ((0 <= x <= 1) && (0 <= y <= 4))
		Gamefield::spawnBlue.get()[x][y];

	if ((0 <= x <= 1) && (7 <= y <= 11))
		Gamefield::spawnBlue.get()[x][y - 2];

	if ((20 <= x <= 21) && (0 <= y <= 4))
		Gamefield::spawnRed.get()[x - 20][y];

	if ((20 <= x <= 21) && (7 <= y <= 11))
		Gamefield::spawnRed.get()[x - 20][y - 2];

	return pSearchedTile;
}

