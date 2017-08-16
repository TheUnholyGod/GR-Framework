#include "TileMaker.h"
#include "MyMath.h"
#include "Loader.h"
#include "BaseDatabase.h"
#include "BaseDatabase.cpp"


TileMaker::TileMaker()
{
	tile_set_base = new BaseDatabase<Tiles>("tile_set_base", "Assets//LevelGenerators.txt");
	tile_set_base->init();
}

TileMaker::~TileMaker()
{
}

/*
0 - air, 
1 - solid block, 
2 - 20/100 chance of spawning rune, 
3 - 50/100 chance of a solid block
*/

Tiles* TileMaker::GenerateRoom(TILE_SET_GENERATOR generator)
{
	tiles_set = new Tiles();

	switch (generator)
	{
	case ROOM_RANDOM:
		for (int y = 0; y < MAX_TILE_SIZE_XY; ++y)
		{
			for (int x = 0; x < MAX_TILE_SIZE_XY; ++x)
			{
				tiles_set->SetTilesInArray(x, y, Math::RandIntMinMax(0, 3));
			}
		}
		break;
	case ROOM_ONE:
		tiles_set = tile_set_base->getObject(Math::RandIntMinMax(1, 5));
		break;
	case ROOM_TWO:
		tiles_set = tile_set_base->getObject(Math::RandIntMinMax(6, 10));
		break;
	case ROOM_THREE:
		tiles_set = tile_set_base->getObject(Math::RandIntMinMax(11, 15));
		break;
	default:
		break;
	}

	return tiles_set;
}

Tiles::Tiles(string input_file)
{
	file_path = input_file;
	level_tiles = new int*[MAX_TILE_SIZE_XY];
	
	for (int i = 0; i < MAX_TILE_SIZE_XY; ++i)
	{
		level_tiles[i] = new int[MAX_TILE_SIZE_XY];
	}

	for (int y = 0; y < MAX_TILE_SIZE_XY; ++y)
	{
		for (int x = 0; x < MAX_TILE_SIZE_XY; ++x)
		{
			level_tiles[y][x] = 0;
		}
	}

	Loader::GetInstance()->LoadData(input_file);
	string temp = "";
	for (int i = 0; i < Loader::GetInstance()->GetData().size(); ++i)
	{
		temp = Loader::GetInstance()->GetData()[i];

		for (int y = 0; y < MAX_TILE_SIZE_XY; ++y)
		{
			for (int x = 0; x < MAX_TILE_SIZE_XY; ++x)
			{
				level_tiles[y][x] = temp[x] - '0';
			}
		}
	}

}

Tiles::Tiles()
{
	level_tiles = new int*[MAX_TILE_SIZE_XY];

	for (int i = 0; i < MAX_TILE_SIZE_XY; ++i)
	{
		level_tiles[i] = new int[MAX_TILE_SIZE_XY];
	}

	for (int y = 0; y < MAX_TILE_SIZE_XY; ++y)
	{
		for (int x = 0; x < MAX_TILE_SIZE_XY; ++x)
		{
			level_tiles[y][x] = 0;
		}
	}
}

int** Tiles::GetTilesArray()
{
	return level_tiles;
}

void Tiles::SetTilesInArray(int x, int y, int input)
{
	level_tiles[y][x] = input;
}

Tiles& Tiles::operator=(Tiles* input)
{
	for (int y = 0; y < MAX_TILE_SIZE_XY; ++y)
	{
		for (int x = 0; x < MAX_TILE_SIZE_XY; ++x)
		{
			this->level_tiles[y][x] = input->level_tiles[y][x];
		}
	}

	return *this;
}