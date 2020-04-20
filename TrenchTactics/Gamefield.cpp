#include "Gamefield.h"


Gamefield::Gamefield(){
}

Gamefield::~Gamefield(){
}



/// <summary>
/// Function that places a new unit in the active players spawn.
/// Returns 0 if spawn is full. Returns 1 if successful.
/// Traverses the spawn from mid of frontline to the corners.
/// </summary>
/// <param name="unit">pointer to unit that has to be spawned</param>
/// <param name="redPlayerActive">show if red player is the active</param>
/// <returns></returns>
int Gamefield::spawnUnitInSpawn(std::shared_ptr<UnitBase> pUnit, bool redPlayerActive)
{
	vector<vector<std::shared_ptr<FieldTile>>>* activeSpawn;
	bool spawnTileFound = false;
	if (redPlayerActive) activeSpawn = &spawnRed;
	else activeSpawn = &spawnBlue;

	//haesslich! sollte geschickter gemacht werden fuer sinnvolle Spawnreihenfolge, aber mit Uebersichtlichkeit
	//funktioniert bisher nur bei default Groesse des Spielfelds.

	if (fieldTileIsFree(1, 4, *activeSpawn)) {
		(*activeSpawn)[1][4]->setUnit(pUnit);
		return 1;
	}
	if (fieldTileIsFree(1, 5, *activeSpawn)) {
		(*activeSpawn)[1][5]->setUnit(pUnit);
		return 1;
	}
	if (fieldTileIsFree(1, 3, *activeSpawn)) {
		(*activeSpawn)[1][3]->setUnit(pUnit);
		return 1;
	}
	if (fieldTileIsFree(1, 6, *activeSpawn)) {
		(*activeSpawn)[1][6]->setUnit(pUnit);
		return 1;
	}
	if (fieldTileIsFree(1, 2, *activeSpawn)) {
		(*activeSpawn)[1][2]->setUnit(pUnit);
		return 1;
	}
	if (fieldTileIsFree(1, 7, *activeSpawn)) {
		(*activeSpawn)[1][7]->setUnit(pUnit);
		return 1;
	}
	if (fieldTileIsFree(1, 1, *activeSpawn)) {
		(*activeSpawn)[1][1]->setUnit(pUnit);
		return 1;
	}
	if (fieldTileIsFree(1, 8, *activeSpawn)) {
		(*activeSpawn)[1][8]->setUnit(pUnit);
		return 1;
	}
	if (fieldTileIsFree(1, 0, *activeSpawn)) {
		(*activeSpawn)[1][0]->setUnit(pUnit);
		return 1;
	}
	if (fieldTileIsFree(1, 9, *activeSpawn)) {
		(*activeSpawn)[1][9]->setUnit(pUnit);
		return 1;
	}
	if (fieldTileIsFree(0, 4, *activeSpawn)) {
		(*activeSpawn)[0][4]->setUnit(pUnit);
		return 1;
	}
	if (fieldTileIsFree(0, 5, *activeSpawn)) {
		(*activeSpawn)[0][5]->setUnit(pUnit);
		return 1;
	}
	if (fieldTileIsFree(0, 3, *activeSpawn)) {
		(*activeSpawn)[0][3]->setUnit(pUnit);
		return 1;
	}
	if (fieldTileIsFree(0, 6, *activeSpawn)) {
		(*activeSpawn)[0][6]->setUnit(pUnit);
		return 1;
	}
	if (fieldTileIsFree(0, 2, *activeSpawn)) {
		(*activeSpawn)[0][2]->setUnit(pUnit);
		return 1;
	}
	if (fieldTileIsFree(0, 7, *activeSpawn)){
		(*activeSpawn)[0][7]->setUnit(pUnit);
		return 1;
	}
	if (fieldTileIsFree(0, 1, *activeSpawn)) {
		(*activeSpawn)[0][1]->setUnit(pUnit);
		return 1;
	}
	if (fieldTileIsFree(0, 8, *activeSpawn)) {
		(*activeSpawn)[0][8]->setUnit(pUnit);
		return 1;
	}
	if (fieldTileIsFree(0, 0, *activeSpawn)) {
		(*activeSpawn)[0][0]->setUnit(pUnit);
		return 1;
	}
	if (fieldTileIsFree(0, 9, *activeSpawn)) {
		(*activeSpawn)[0][9]->setUnit(pUnit);
		return 1;
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
bool Gamefield::fieldTileIsFree(int x, int y, vector<vector<std::shared_ptr<FieldTile>>> activeSpawn)
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
	Gamefield::setAllFieldSizes();
	Gamefield::initiatePlayerTilesBlue();
	Gamefield::initiatePlayerTilesRed();
	Gamefield::initiateMenuTiles();
	Gamefield::initiateSpawnTilesBlue();
	Gamefield::initiateSpawnTilesRed();
	Gamefield::initiatePlayingFieldTiles();

}

/// <summary>
/// Sets the number of tiles of each type at the start of the game.
/// </summary>
void Gamefield::setAllFieldSizes()
{
	Gamefield::setSizePlayerTilesBlue();
	Gamefield::setSizePlayerTilesRed();
	Gamefield::setSizeMenuBar();
	Gamefield::setSizePlayingField();
	Gamefield::setSizeSpawnBlue();
	Gamefield::setSizeSpawnRed();

}

/// <summary>
/// Sets the size of the blue player's spawn to 2x2.
/// </summary>
void Gamefield::setSizePlayerTilesBlue()
{
	headquarterTilePlayerBlue.resize(2);
	for each (vector<std::shared_ptr<PlayerTile>> hqBlue in headquarterTilePlayerBlue)
	{
		hqBlue.resize(2);
	}
}

/// <summary>
/// Sets the size of the blue player's spawn to 2x2.
/// </summary>
void Gamefield::setSizePlayerTilesRed()
{
	headquarterTilePlayerRed.resize(2);
	for each (vector<std::shared_ptr<PlayerTile>> hqRed in headquarterTilePlayerRed)
	{
		hqRed.resize(2);
	}
}

/// <summary>
/// Sets the size of the menubar at the gamestart.
/// </summary>
void Gamefield::setSizeMenuBar()
{
	menuBar.resize(22);
	for each (vector<std::shared_ptr<MenuTile>> menuCol in menuBar)
	{
		menuCol.resize(3);
	}
}

/// <summary>
/// Sets the size of the playingfield at the gamestart.
/// </summary>
void Gamefield::setSizePlayingField()
{
	playingfield.resize(18);
	for each (vector<std::shared_ptr<FieldTile>> fieldCol in playingfield)
	{
		fieldCol.resize(12);
	}
}

/// <summary>
/// Sets the size of blue player's spawn.
/// </summary>
void Gamefield::setSizeSpawnBlue()
{
	spawnBlue.resize(2);
	for each (vector<std::shared_ptr<FieldTile>> spawnCol in spawnBlue)
	{
		spawnCol.resize(10);
	}
}

/// <summary>
/// Sets the size of red player's spawn.
/// </summary>
void Gamefield::setSizeSpawnRed()
{
	spawnRed.resize(2);
	for each (vector<std::shared_ptr<FieldTile>> spawnCol in spawnRed)
	{
		spawnCol.resize(10);
	}
}




/// <summary>
/// Function to set up the PlayerTiles for blue player at gamestart.
/// </summary>
void Gamefield::initiatePlayerTilesBlue()
{
	for (vector<vector<std::shared_ptr<PlayerTile>>>::iterator xIter = headquarterTilePlayerBlue.begin(); xIter != headquarterTilePlayerBlue.end(); ++xIter) {
		for (vector<std::shared_ptr<PlayerTile>>::iterator yIter = xIter->begin(); yIter != xIter->end(); ++yIter) {
			*yIter = std::shared_ptr <PlayerTile>(new PlayerTile);
		}
	}
}

/// <summary>
/// Function to set up the PlayerTiles for red player at gamestart.
/// </summary>
void Gamefield::initiatePlayerTilesRed()
{
	for (vector<vector<std::shared_ptr<PlayerTile>>>::iterator xIter = headquarterTilePlayerRed.begin(); xIter != headquarterTilePlayerRed.end(); ++xIter) {
		for (vector<std::shared_ptr<PlayerTile>>::iterator yIter = xIter->begin(); yIter != xIter->end(); ++yIter) {
			*yIter = std::shared_ptr <PlayerTile>(new PlayerTile);
		}
	}
}

/// <summary>
/// Function to set up the MenuTiles at gamestart.
/// </summary>
void Gamefield::initiateMenuTiles()
{
	for (vector<vector<std::shared_ptr<MenuTile>>>::iterator xIter = menuBar.begin(); xIter != menuBar.end(); ++xIter) {
		for (vector<std::shared_ptr<MenuTile>>::iterator yIter = xIter->begin(); yIter != xIter->end(); ++yIter) {
			*yIter = std::shared_ptr <MenuTile>(new MenuTile);
		}
	}
}

/// <summary>
/// Function to set up the fieldtiles in blue player's spawn at gamestart.
/// </summary>
void Gamefield::initiateSpawnTilesBlue()
{
	for (vector<vector<std::shared_ptr<FieldTile>>>::iterator xIter = spawnBlue.begin(); xIter != spawnBlue.end(); ++xIter) {
		for (vector<std::shared_ptr<FieldTile>>::iterator yIter = xIter->begin(); yIter != xIter->end(); ++yIter) {
			*yIter = std::shared_ptr <FieldTile> (new FieldTile(FieldTile::terrainType::spawnterrain));
		}
	}
}

/// <summary>
/// Function to set up the fieldtiles in red player's spawn at gamestart.
/// </summary>
void Gamefield::initiateSpawnTilesRed()
{
	for (vector<vector<std::shared_ptr<FieldTile>>>::iterator xIter = spawnRed.begin(); xIter != spawnRed.end(); ++xIter) {
		for (vector<std::shared_ptr<FieldTile>>::iterator yIter = xIter->begin(); yIter != xIter->end(); ++yIter) {
			*yIter = std::shared_ptr < FieldTile> (new FieldTile(FieldTile::terrainType::spawnterrain));
		}
	}
}

/// <summary>
/// Function to set up the fieldtiles in playingfield at gamestart.
/// </summary>
void Gamefield::initiatePlayingFieldTiles()
{
	for (vector<vector<std::shared_ptr<FieldTile>>>::iterator xIter = playingfield.begin(); xIter != playingfield.end(); ++xIter) {
		for (vector<std::shared_ptr<FieldTile>>::iterator yIter = xIter->begin(); yIter != xIter->end(); ++yIter) {
			int rnd = rand() % 3;
			if (rnd == 0)
				*yIter = std::shared_ptr <FieldTile> (new FieldTile(FieldTile::terrainType::stone));
			if (rnd == 1)
				*yIter = std::shared_ptr <FieldTile> (new FieldTile(FieldTile::terrainType::clay));
			if(rnd == 2)
				*yIter = std::shared_ptr <FieldTile> (new FieldTile(FieldTile::terrainType::mud));
		}
	}
}

/// <summary>
/// Function to search playingfield and both spawns for a tile on which a unit stands. Returns a nullpointer if unit was not found.
/// </summary>
/// <param name="pUnit">unit to search for</param>
/// <returns>tile holding the unit</returns>
std::shared_ptr<FieldTile> Gamefield::findTileForUnit(std::shared_ptr<UnitBase> pUnit)
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


/// <summary>
/// Function to get a pointer to tile at x and y. x and y counting from top left.
/// </summary>
/// <param name="x">Horizontal position of tile</param>
/// <param name="y">Vertical position of tile</param>
/// <returns>Pointer to searched Tile.</returns>
std::shared_ptr<Tile> Gamefield::getTilePointerAt(int x, int y)
{
	std::shared_ptr<Tile> pSearchedTile = NULL;

	if ((12 <= x <= 14) && (0 <= y <= 21))
		pSearchedTile = Gamefield::menuBar[x][y];

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