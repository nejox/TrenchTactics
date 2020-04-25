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
	vector<vector<std::shared_ptr<FieldTile>>>* activeSpawn;
	if (redPlayerActive) activeSpawn = &spawnRed;
	else activeSpawn = &spawnBlue;


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
	menuBar = std::make_shared<vector<vector <std::shared_ptr<MenuTile>>>>();
	Gamefield::setAllFieldSizes();
	//Gamefield::initiatePlayerTilesBlue();
	//Gamefield::initiatePlayerTilesRed();
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
	headquarterTilePlayerBlue.resize(2);
	for (vector<std::shared_ptr<PlayerTile>> hqBlue : headquarterTilePlayerBlue)
	{
		hqBlue.resize(2);
	}
}

/**
 * Sets the size of the blue player's spawn to 2x2.
 *
 */
void Gamefield::setSizePlayerTilesRed()
{
	headquarterTilePlayerRed.resize(2);
	for (vector<std::shared_ptr<PlayerTile>> hqRed : headquarterTilePlayerRed)
	{
		hqRed.resize(2);
	}
}

/**
 * Sets the size of the menubar at the gamestart.
 *
 */
void Gamefield::setSizeMenuBar()
{
	menuBar->resize(22);
	//for (vector<std::shared_ptr<MenuTile>> menuCol : menuBar.get())
	//{
	//	menuCol.resize(3);
	//}

	for (vector<vector<shared_ptr<MenuTile>>>::iterator i = menuBar->begin(); i != menuBar->end(); ++i)
	{
		i->resize(3);
	}

}

/**
 * Sets the size of the playingfield at the gamestart.
 *
 */
void Gamefield::setSizePlayingField()
{
	playingfield.resize(18);
	for (vector<std::shared_ptr<FieldTile>> fieldCol : playingfield)
	{
		fieldCol.resize(12);
	}
}

/**
 * Sets the size of blue player's spawn.
 *
 */
void Gamefield::setSizeSpawnBlue()
{
	spawnBlue.resize(2);
	for (vector<std::shared_ptr<FieldTile>> spawnCol : spawnBlue)
	{
		spawnCol.resize(10);
	}
}

/**
 * Sets the size of red player's spawn.
 *
 */
void Gamefield::setSizeSpawnRed()
{
	spawnRed.resize(2);
	for (vector<std::shared_ptr<FieldTile>> spawnCol : spawnRed)
	{
		spawnCol.resize(10);
	}
}

/**
 * Function to set up the PlayerTiles for blue player at gamestart.
 *
 */
void Gamefield::initiatePlayerTilesBlue()
{
	for (vector<vector<std::shared_ptr<PlayerTile>>>::iterator xIter = headquarterTilePlayerBlue.begin(); xIter != headquarterTilePlayerBlue.end(); ++xIter) {
		for (vector<std::shared_ptr<PlayerTile>>::iterator yIter = xIter->begin(); yIter != xIter->end(); ++yIter) {
			*yIter = std::shared_ptr <PlayerTile>(new PlayerTile);
			//keinen Plan, ob passende Funktion f�r Renderer und passender Input
			RendererImpl::instance().renderHQ();//blue
		}
	}
}

/**
 * Function to set up the PlayerTiles for red player at gamestart.
 *
 */
void Gamefield::initiatePlayerTilesRed()
{
	for (vector<vector<std::shared_ptr<PlayerTile>>>::iterator xIter = headquarterTilePlayerRed.begin(); xIter != headquarterTilePlayerRed.end(); ++xIter) {
		for (vector<std::shared_ptr<PlayerTile>>::iterator yIter = xIter->begin(); yIter != xIter->end(); ++yIter) {
			*yIter = std::shared_ptr <PlayerTile>(new PlayerTile);
			//keinen Plan, ob passende Funktion f�r Renderer und passender Input
			RendererImpl::instance().renderHQ();//red
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

			std::shared_ptr<MenuTile> tmpMenuTilePointer = std::make_shared<MenuTile>();
			Sprite* terrainSprite = new Sprite();
			terrainSprite->load("../Data/Sprites/Terrain/TERRAIN_SAMPLE.bmp");
			terrainSprite->setPos(3, 3);
			tmpMenuTilePointer->setXPos(3);
			tmpMenuTilePointer->setYPos(3);
			tmpMenuTilePointer->setSprite(terrainSprite);

			tmpMenuTilePointer->getSprite()->render();
			*yIter = tmpMenuTilePointer;

			//*yIter = std::make_shared<MenuTile>();
			//Menu rendern fehlt noch!
		}
	}
}

/**
 * Function to set up the fieldtiles in blue player's spawn at gamestart.
 *
 */
void Gamefield::initiateSpawnTilesBlue()
{
	for (vector<vector<std::shared_ptr<FieldTile>>>::iterator xIter = spawnBlue.begin(); xIter != spawnBlue.end(); ++xIter) {
		for (vector<std::shared_ptr<FieldTile>>::iterator yIter = xIter->begin(); yIter != xIter->end(); ++yIter) {
			std::shared_ptr<FieldTile> tmpFieldTilePointer = std::make_shared<FieldTile>(FieldTile::terrainType::spawnterrain);
			Sprite* terrainSprite = new Sprite();
			terrainSprite->load("../Data/Sprites/Terrain/TERRAIN_SAMPLE.bmp");
			tmpFieldTilePointer->setSprite(terrainSprite);
			tmpFieldTilePointer->getSprite()->render();
			*yIter = tmpFieldTilePointer;
			//Spawn rendern fehlt noch!
		}
	}
}

/**
 * Function to set up the fieldtiles in red player's spawn at gamestart.
 *
 */
void Gamefield::initiateSpawnTilesRed()
{
	for (vector<vector<std::shared_ptr<FieldTile>>>::iterator xIter = spawnRed.begin(); xIter != spawnRed.end(); ++xIter) {
		for (vector<std::shared_ptr<FieldTile>>::iterator yIter = xIter->begin(); yIter != xIter->end(); ++yIter) {

			std::shared_ptr<FieldTile> tmpFieldTilePointer = std::make_shared<FieldTile>(FieldTile::terrainType::spawnterrain);
			Sprite* terrainSprite = new Sprite();
			terrainSprite->load("../Data/Sprites/Terrain/TERRAIN_SAMPLE.bmp");
			tmpFieldTilePointer->setSprite(terrainSprite);
			tmpFieldTilePointer->getSprite()->render();
			*yIter = tmpFieldTilePointer;

			//*yIter = std::shared_ptr < FieldTile>(new FieldTile(FieldTile::terrainType::spawnterrain));
			//Spawn rendern fehlt noch!
		}
	}
}

/**
 * Function to set up the fieldtiles in playingfield at gamestart.
 *
 */
void Gamefield::initiatePlayingFieldTiles()
{
	for (vector<vector<std::shared_ptr<FieldTile>>>::iterator xIter = playingfield.begin(); xIter != playingfield.end(); ++xIter) {
		for (vector<std::shared_ptr<FieldTile>>::iterator yIter = xIter->begin(); yIter != xIter->end(); ++yIter) {
			int rnd = rand() % 3;
			if (rnd == 0) {

				std::shared_ptr<FieldTile> tmpFieldTilePointer = std::make_shared<FieldTile>(FieldTile::terrainType::mud);
				Sprite* terrainSprite = new Sprite();
				terrainSprite->load("../Data/Sprites/Terrain/TERRAIN_SAMPLE.bmp");
				tmpFieldTilePointer->setSprite(terrainSprite);
				tmpFieldTilePointer->getSprite()->render();
				*yIter = tmpFieldTilePointer;

				//*yIter = std::shared_ptr <FieldTile>(new FieldTile(FieldTile::terrainType::stone));

			}
			if (rnd == 1) {

				std::shared_ptr<FieldTile> tmpFieldTilePointer = std::make_shared<FieldTile>(FieldTile::terrainType::mud);
				Sprite* terrainSprite = new Sprite();
				terrainSprite->load("../Data/Sprites/Terrain/TERRAIN_SAMPLE.bmp");
				tmpFieldTilePointer->setSprite(terrainSprite);
				tmpFieldTilePointer->getSprite()->render();
				*yIter = tmpFieldTilePointer;

				//*yIter = std::shared_ptr <FieldTile>(new FieldTile(FieldTile::terrainType::clay));
			}
			if (rnd == 2) {

				std::shared_ptr<FieldTile> tmpFieldTilePointer = std::make_shared<FieldTile>(FieldTile::terrainType::mud);
				Sprite* terrainSprite = new Sprite();
				terrainSprite->load("../Data/Sprites/Terrain/TERRAIN_SAMPLE.bmp");
				tmpFieldTilePointer->setSprite(terrainSprite);
				tmpFieldTilePointer->getSprite()->render();
				*yIter = tmpFieldTilePointer;

				//*yIter = std::shared_ptr <FieldTile>(new FieldTile(FieldTile::terrainType::mud));
			}
			//Playingfield rendern fehlt noch!
		}
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

	for (vector<vector<std::shared_ptr<FieldTile>>>::iterator xIter = playingfield.begin(); xIter != playingfield.end(); ++xIter) {
		for (vector< std::shared_ptr<FieldTile>>::iterator yIter = xIter->begin(); yIter != xIter->end(); ++yIter) {
			pTileToTest = *yIter;
			if (pTileToTest->getUnit() == pUnit) return pTileToTest;
		}
	}

	//Searches blue player's spawn

	for (vector<vector<std::shared_ptr<FieldTile>>>::iterator xIter = spawnBlue.begin(); xIter != spawnBlue.end(); ++xIter) {
		for (vector<std::shared_ptr<FieldTile>>::iterator yIter = xIter->begin(); yIter != xIter->end(); ++yIter) {
			pTileToTest = *yIter;
			if (pTileToTest->getUnit() == pUnit) return pTileToTest;
		}
	}

	//Searches red player's spawn

	for (vector<vector<std::shared_ptr<FieldTile>>>::iterator xIter = spawnRed.begin(); xIter != spawnRed.end(); ++xIter) {
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
		//pSearchedTile = Gamefield::menuBar[x][y];

	if ((2 <= x <= 19) && (0 <= y <= 11))
		pSearchedTile = Gamefield::playingfield[x - 2][y];

	if ((0 <= x <= 1) && (5 <= y <= 6))
		Gamefield::headquarterTilePlayerBlue[x][y - 5];

	if ((20 <= x <= 21) && (5 <= y <= 6))
		Gamefield::headquarterTilePlayerRed[x - 20][y - 5];

	if ((0 <= x <= 1) && (0 <= y <= 4))
		Gamefield::spawnBlue[x][y];

	if ((0 <= x <= 1) && (7 <= y <= 11))
		Gamefield::spawnBlue[x][y - 2];

	if ((20 <= x <= 21) && (0 <= y <= 4))
		Gamefield::spawnRed[x - 20][y];

	if ((20 <= x <= 21) && (7 <= y <= 11))
		Gamefield::spawnRed[x - 20][y - 2];

	return pSearchedTile;
}