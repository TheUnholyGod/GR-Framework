#include "Level.h"
#include "MyMath.h"

Level::Level()
{
	level_set = new int*[MAX_LEVEL_SIZE_XY];
	for(int i = 0; i < MAX_LEVEL_SIZE_XY; ++i)
		level_set[i] = new int[MAX_LEVEL_SIZE_XY];


	for (int y = 0; y < MAX_LEVEL_SIZE_XY; ++y)
	{
		for (int x = 0; x < MAX_LEVEL_SIZE_XY; ++x)
		{
			level_set[y][x] = 0;
		}
	}
}

int** Level::GetLevelSetArray()
{
	return level_set;
}

void Level::GetLevelLayOut(map<int, Tiles*>& input_layout)
{
	input_layout = level_layout;
}

void Level::GenerateLevel()
{
	DIRECTION rand_dir = DOWN;
	int x = 0, y = 0;

	x = Math::RandIntMinMax(0, MAX_LEVEL_SIZE_XY);
	level_set[y][x] = Math::RandIntMinMax(1, 2);

	while (true)
	{
		rand_dir = static_cast<DIRECTION>(Math::RandIntMinMax(0, TOTAL_DIRETIONS));

		switch (rand_dir)
		{
		case DOWN:
			++y;
			break;
		case LEFT:
			--x;
			if (level_set[y][x] != 0)
				++x;
			break;
		case RIGHT:
			++x;
			if (level_set[y][x] != 0)
				--x;
			break;
		default:
			break;
		}

		if (x < 1 || x >= MAX_LEVEL_SIZE_XY - 1)
		{
			if (y >= MAX_LEVEL_SIZE_XY - 1)
			{
				level_set[y][x] = 1;

				for (int i = 0; i < MAX_LEVEL_SIZE_XY; ++i)
				{
					for (int j = 0; j < MAX_LEVEL_SIZE_XY; ++j)
					{
						if (level_set[i][j] == 0)
							level_set[i][j] = ((Math::RandIntMinMax(0, 100) < 50) ? 0 : 3);
					}
				}
				break;
			}
			else
			{
				if (x < 0)
					++x;
				else
					--x;
			}
		}

		if (y >= MAX_LEVEL_SIZE_XY)
		{
			--y;
		}

		switch (rand_dir)
		{
		case DOWN:
		{
			if (level_set[y - 1][x] != 2)
			{
				level_set[y - 1][x] = 2;

				level_set[y][x] = 3;
			}
		}
		break;
		case LEFT:
			level_set[y][x] = Math::RandIntMinMax(1, 3);
			break;
		case RIGHT:
			level_set[y][x] = Math::RandIntMinMax(1, 3);
			break;
		default:
			break;
		} 
	}

	int i = 0;
	for (int y = 0; y < MAX_LEVEL_SIZE_XY; ++y)
	{
		for (int x = 0; x < MAX_LEVEL_SIZE_XY; ++x)
		{
			///TWO TIMES OT OFFSET

			level_layout[i] = TileMaker::GetInstance()->GenerateRoom(static_cast<TileMaker::TILE_SET_GENERATOR>(level_set[y][x]));
			++i;
		}
	}
}

int Level::GetSizeOfLevel()
{
	return MAX_LEVEL_SIZE_XY;
}

int Level::GetSizeOfTileSet()
{
	return MAX_TILE_SIZE_XY;
}

int Level::GetTotalTilesInLevel()
{
	return level_layout.size();
}

int Level::ReturnTileViaPos(Vector2 pos)
{
	Vector2 temp;
	double dividor = 1 / MAX_TILE_SIZE_XY;

	temp.x = pos.x * dividor;
	temp.y = pos.y * dividor;

	return (static_cast<int>(temp.y) * 5) + static_cast<int>(temp.x);
}

vector<int> Level::ReturnSurroundingTilesViaCurrentTile(int tile)
{
	vector<int> temp;

	int tile_selected = 0;

	for (int i = -6; i < -3; ++i)
	{
		tile_selected = tile + i;
		if (tile_selected > 0)
		{
			temp.push_back(tile_selected);
		}
	}

	for (int i = 6; i > 3; --i)
	{
		tile_selected = tile + i;
		if (tile_selected < GetTotalTilesInLevel())
		{
			temp.push_back(tile_selected);
		}
	}

	for (int i = -1; i < 2; ++i)
	{
		tile_selected = tile + i;
		if (tile_selected > 0 && tile_selected < GetTotalTilesInLevel() && tile_selected != tile)
		{
			temp.push_back(tile_selected);
		}
	}

	return temp;
}

