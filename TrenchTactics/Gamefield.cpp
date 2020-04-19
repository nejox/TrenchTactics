#include "Gamefield.h"


Gamefield::Gamefield(){
}

Gamefield::~Gamefield(){
}



/// <summary>
/// Function that places a new unit in the active players spawn.
/// Returns 0 if spawn is full. Returns 1 if successful.
/// </summary>
/// <param name="unit">pointer to unit that has to be spawned</param>
/// <param name="redPlayerActive">show if red player is the active</param>
/// <returns></returns>
int Gamefield::spawnUnitInSpawn(UnitBase* pUnit, bool redPlayerActive)
{
	vector<vector<FieldTile*>>* activeSpawn;
	bool spawnTileFound = false;
	if (redPlayerActive) activeSpawn = &spawnRed;
	else activeSpawn = &spawnBlue;

	// furchtbarer Weg, aber ist mir so schnell nix besseres eingefallen, fuer sinnvolle Reihenfolge
	for (int i = 0; i <= 11; i++) {
		switch (i) {
		case 0: if (fieldTileIsFree(1, 2, *activeSpawn)) (*activeSpawn)[1][2]->setUnit(pUnit);
			return 1;
		case 1: if (fieldTileIsFree(1, 3, *activeSpawn)) (*activeSpawn)[1][3]->setUnit(pUnit);
			return 1;
		case 2: if (fieldTileIsFree(1, 1, *activeSpawn)) (*activeSpawn)[1][1]->setUnit(pUnit);
			return 1;
		case 3: if (fieldTileIsFree(1, 4, *activeSpawn)) (*activeSpawn)[1][4]->setUnit(pUnit);
			return 1;
		case 4: if (fieldTileIsFree(1, 0, *activeSpawn)) (*activeSpawn)[1][0]->setUnit(pUnit);
			return 1;
		case 5: if (fieldTileIsFree(1, 5, *activeSpawn)) (*activeSpawn)[1][5]->setUnit(pUnit);
			return 1;
		case 6: if (fieldTileIsFree(0, 2, *activeSpawn)) (*activeSpawn)[0][2]->setUnit(pUnit);
			return 1;
		case 7: if (fieldTileIsFree(0, 3, *activeSpawn)) (*activeSpawn)[0][3]->setUnit(pUnit);
			return 1;
		case 8: if (fieldTileIsFree(0, 1, *activeSpawn)) (*activeSpawn)[0][1]->setUnit(pUnit);
			return 1;
		case 9: if (fieldTileIsFree(0, 4, *activeSpawn)) (*activeSpawn)[0][4]->setUnit(pUnit);
			return 1;
		case 10: if (fieldTileIsFree(0, 0, *activeSpawn)) (*activeSpawn)[0][0]->setUnit(pUnit);
			return 1;
		case 11: if (fieldTileIsFree(0, 5, *activeSpawn)) (*activeSpawn)[0][5]->setUnit(pUnit);
			return 1;
		}
	}
	
	
	return 0;
}

/// <summary>
/// Checks if a fieldtile is empty.
/// </summary>
/// <param name="x">horizontal position</param>
/// <param name="y">vertical position</param>
/// <param name="activeSpawn">field that contains the tile</param>
/// <returns></returns>
bool Gamefield::fieldTileIsFree(int x, int y, vector<vector<FieldTile*>> activeSpawn)
{
	if (activeSpawn[x][y] == nullptr) return true;
	return false;
}


/// <summary>
/// Function for setting up the gamefield at the start of a new game.
/// </summary>
/// <param name="FieldWidth">int for delacring width of playingfield. Not used yet.</param>
/// <param name="FieldHeight">int for delacring height of playingfield. Not used yet.</param>
/// <param name="Seed">int for regenerating certain playingfieldlayout. Not used yet.</param>
void Gamefield::Init(int FieldWidth, int FieldHeight,int Seed) {
	Gamefield::initiatePlayerTilesBlue();
	Gamefield::initiatePlayerTilesRed();
	Gamefield::initiateMenuTiles();
	Gamefield::initiateSpawnTilesBlue();
	Gamefield::initiateSpawnTilesRed();
	Gamefield::initiatePlayingFieldTiles();


}
/// <summary>
/// Function to set up the PlayerTiles for blue player at gamestart.
/// </summary>
void Gamefield::initiatePlayerTilesBlue()
{
	for (vector<vector<PlayerTile*>>::iterator xIter = headquarterTilePlayerBlue.begin(); xIter != headquarterTilePlayerBlue.end(); ++xIter) {
		for (vector<PlayerTile*>::iterator yIter = xIter->begin(); yIter != xIter->end(); ++yIter) {
			*yIter = new PlayerTile;
		}
	}
}

/// <summary>
/// Function to set up the PlayerTiles for red player at gamestart.
/// </summary>
void Gamefield::initiatePlayerTilesRed()
{
	for (vector<vector<PlayerTile*>>::iterator xIter = headquarterTilePlayerRed.begin(); xIter != headquarterTilePlayerRed.end(); ++xIter) {
		for (vector<PlayerTile*>::iterator yIter = xIter->begin(); yIter != xIter->end(); ++yIter) {
			*yIter = new PlayerTile;
		}
	}
}

/// <summary>
/// Function to set up the MenuTiles at gamestart.
/// </summary>
void Gamefield::initiateMenuTiles()
{
	for (vector<vector<MenuTile*>>::iterator xIter = menuBar.begin(); xIter != menuBar.end(); ++xIter) {
		for (vector<MenuTile*>::iterator yIter = xIter->begin(); yIter != xIter->end(); ++yIter) {
			*yIter = new MenuTile;
		}
	}
}

/// <summary>
/// Function to set up the fieldtiles in blue player's spawn at gamestart.
/// </summary>
void Gamefield::initiateSpawnTilesBlue()
{
	for (vector<vector<FieldTile*>>::iterator xIter = spawnBlue.begin(); xIter != spawnBlue.end(); ++xIter) {
		for (vector<FieldTile*>::iterator yIter = xIter->begin(); yIter != xIter->end(); ++yIter) {
			*yIter = new FieldTile(FieldTile::terrainType::spawnterrain);
		}
	}
}

/// <summary>
/// Function to set up the fieldtiles in red player's spawn at gamestart.
/// </summary>
void Gamefield::initiateSpawnTilesRed()
{
	for (vector<vector<FieldTile*>>::iterator xIter = spawnRed.begin(); xIter != spawnRed.end(); ++xIter) {
		for (vector<FieldTile*>::iterator yIter = xIter->begin(); yIter != xIter->end(); ++yIter) {
			*yIter = new FieldTile(FieldTile::terrainType::spawnterrain);
		}
	}
}

/// <summary>
/// Function to set up the fieldtiles in playingfield at gamestart.
/// </summary>
void Gamefield::initiatePlayingFieldTiles()
{
	for (vector<vector<FieldTile*>>::iterator xIter = field.begin(); xIter != field.end(); ++xIter) {
		for (vector<FieldTile*>::iterator yIter = xIter->begin(); yIter != xIter->end(); ++yIter) {
			int rnd = rand() % 3;
			if (rnd == 0)
				*yIter = new FieldTile(FieldTile::terrainType::stone);
			if (rnd == 1)
				*yIter = new FieldTile(FieldTile::terrainType::clay);
			if(rnd == 2)
				*yIter = new FieldTile(FieldTile::terrainType::mud);
		}
	}
}

/// <summary>
/// Function to search playingfield and both spawns for a tile on which a unit stands. Returns a nullpointer if unit was not found.
/// </summary>
/// <param name="pUnit">unit to search for</param>
/// <returns>tile holding the unit</returns>
FieldTile* Gamefield::findTileForUnit(UnitBase* pUnit)
{
	FieldTile* pTileToTest = nullptr;

	//Searches playingfield

	for (vector<vector<FieldTile*>>::iterator xIter = field.begin(); xIter != field.end(); ++xIter) {
		for (vector<FieldTile*>::iterator yIter = xIter->begin(); yIter != xIter->end(); ++yIter) {
			pTileToTest = *yIter;
			if (pTileToTest->getUnit() == pUnit) return pTileToTest;
		}
	}

	//Searches blue player's spawn

	for (vector<vector<FieldTile*>>::iterator xIter = spawnBlue.begin(); xIter != spawnBlue.end(); ++xIter) {
		for (vector<FieldTile*>::iterator yIter = xIter->begin(); yIter != xIter->end(); ++yIter) {
			pTileToTest = *yIter;
			if (pTileToTest->getUnit() == pUnit) return pTileToTest;
		}
	}

	//Searches red player's spawn

	for (vector<vector<FieldTile*>>::iterator xIter = spawnRed.begin(); xIter != spawnRed.end(); ++xIter) {
		for (vector<FieldTile*>::iterator yIter = xIter->begin(); yIter != xIter->end(); ++yIter) {
			pTileToTest = *yIter;
			if (pTileToTest->getUnit() == pUnit) return pTileToTest;
		}
	}

	return nullptr;
}


/// <summary>
/// Function to get a pointer to tile at x and y. x and y counting from top left.
/// </summary>
/// <param name="x">Horizontal position of tile</param>
/// <param name="y">Vertical position of tile</param>
/// <returns>Pointer to searched Tile.</returns>
Tile* Gamefield::getTilePointerAt(int x, int y)
{
	Tile* pSearchedTile = NULL;

	if ((12 <= x <= 14) && (0 <= y <= 21))
		pSearchedTile = Gamefield::menuBar[x][y];

	if ((2 <= x <= 19) && (0 <= y <= 11))
		pSearchedTile = Gamefield::field[x - 2][y];

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

/*
/// <summary>
/// Method to find the corresponding Tile to a MouseClickEvent and initiate the handling of said event.
/// </summary>
/// <param name="event"></param>
void Gamefield::assignEventToTile(MouseClickEvent event) {
	int x = event.getX;
	int y = event.getY;

	if ((12 <= event.getY <= 14) && (0 <= event.getX <= 21))
		Gamefield::getMenuBar[event.getX][event.getY - 12]->handleEvent(event);

	if ((2 <= event.getX <= 19) && (0 <= event.getY <= 11))
		Gamefield::getField[event.getX - 2][event.getY]->handleEvent(event);

	if ((0 <= event.getX <= 1) && (5 <= event.getY <= 6))
		Gamefield::getHqTilePlayerBlue[event.getX][event.getY - 5]->handleEvent(event);

	if ((20 <= event.getX <= 21) && (5 <= event.getY <= 6))
		Gamefield::getHqTilePlayerRed[event.getX-20][event.getY - 5]->handleEvent(event);

	if ((0 <= event.getX <= 1) && (0 <= event.getY <= 4))
		Gamefield::getSpawnBlue[event.getX][event.getY]->handleEvent(event);

	if ((0 <= event.getX <= 1) && (7 <= event.getY <= 11))
		Gamefield::getSpawnBlue[event.getX][event.getY - 2]->handleEvent(event);

	if ((20 <= event.getX <= 21) && (0 <= event.getY <= 4))
		Gamefield::getSpawnRed[event.getX-20][event.getY]->handleEvent(event);

	if ((20 <= event.getX <= 21) && (7 <= event.getY <= 11))
		Gamefield::getSpawnRed[event.getX-20][event.getY - 2]->handleEvent(event);

}

*/