#ifndef _LEVEL_H_
#define _LEVEL_H_

#include "TileMaker.h"
#include <map>
#include <vector>
#include "Vector2.h"

#define MAX_LEVEL_SIZE_XY 5

using std::map;
using std::vector;

class Level
{
	enum DIRECTION
	{
		DOWN = 0,
		LEFT,
		RIGHT,

		TOTAL_DIRETIONS
	};
private:
	int** level_set;
	map<int, Tiles*> level_layout;
public:
	Level();
	int** GetLevelSetArray();
	void GetLevelLayOut(map<int, Tiles*>&);

	/*
		0 - random room - //Rooms with random blocks 
		1 - room one - //Rooms with only Left or Right exit
		2 - room two - //Rooms with only Left, Right and Bottom exit
		3 - room three - //Rooms with only Left, Right and Top exit
	*/
	void GenerateLevel();

	int GetSizeOfLevel();
	int GetSizeOfTileSet();
	int GetTotalTilesInLevel();

	int ReturnTileViaPos(Vector2);  //Returns the tile via position of the entity/block/etc

	vector<int> ReturnSurroundingTilesViaCurrentTile(int);  //Returns the surrounding tiles in a square of 3 by 3, around the given tile

};

#endif