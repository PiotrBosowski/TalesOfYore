#include "Town.h"
using namespace std;

Town::Town(string townName)
{
	ifstream townFile;
	townFile.open(townName, ios::in);
	if (townFile.good())
	{
		vector <Square> row;
		char sqType;
		while (!townFile.eof())
		{
			townFile.get(sqType);
			if (sqType != '\n')
			{
				row.push_back(Square(sqType - '0'));
			}
			else
			{
				if (row.size())
				{
					roomMap.push_back(row);
					row.clear();
				}
			}
		}
		townFile.close();
	}
	height = roomMap.size();
	width = roomMap[height - 1].size();
	indexTown();
	egressDirection = E; ////////////////WARNING
}

void Town::indexTown()
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			roomMap[y][x].setPosition().setAbsolute(Cords{ y, x });
			roomMap[y][x].setPosition().setRelative(Cords{ y, x });
			if (roomMap[y][x].getType() == egress)
			{
				egressPosition.setAbsolute(Cords{ y, x });
				egressPosition.setRelative(Cords{ y, x });
				if (y == 0) egressDirection = N; else
				if (y == height - 1) egressDirection = S; else
				if (x == 0) egressDirection = E; else
				if (x == width - 1) egressDirection = W;
			}
		}
	}
}


Town::~Town()
{
}
