#include "Level.h"
using namespace std;
constexpr unsigned int MAX_SIZE = 20;
constexpr unsigned int MIN_SIZE = 3;


Level::Level(Cords lastEgressCords, cardinalDirection lastEgressDirection)
{
	rollDimensions();
	createGroundAndWalls();
	createEntrance(lastEgressDirection);
	createEgress();
	indexRelativelyRoom();
	indexAbsolutelyRoom(lastEgressCords);
}

void Level::rollDimensions()
{
	random_device generator;
	uniform_int_distribution<int> dimension_distr(MIN_SIZE, MAX_SIZE);
	height = dimension_distr(generator);
	width = dimension_distr(generator);
	firstSquarePosition.setRelative(Cords{ 0,0 });
	lastSquarePosition.setRelative(Cords{ width - 1, height - 1 });
}

void Level::createGroundAndWalls()
{
	roomMap.resize(height);
	Square s;
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (y == 0 || x == 0 || y == height - 1 || x == width - 1) s.setType(1);
			else s.setType(0);
			roomMap[y].push_back(s);
		}
	}
}

void Level::createEntrance(cardinalDirection lastEgressDirection)
{
	random_device generator;
	uniform_int_distribution<int> entranceY_distr(1, height - 2);
	uniform_int_distribution<int> entranceX_distr(1, width - 2);
	entranceDirection = lastEgressDirection;

	switch (entranceDirection)
	{
	case N:	entrancePosition.setRelative(Cords{ height - 1, entranceX_distr(generator) }); break; //entrance on the bottom wall of the room
	case E: entrancePosition.setRelative(Cords{ entranceY_distr(generator), 0 }); break; //entrance on the left wall of the room
	case S: entrancePosition.setRelative(Cords{ 0, entranceX_distr(generator) }); break; //entrance on the upper wall of the room
	case W: entrancePosition.setRelative(Cords{ entranceY_distr(generator), width - 1 }); break; //entrance on the right wall of the room
	}
	roomMap[entrancePosition.getRelative().y][entrancePosition.getRelative().x].setType(entrance);
}

void Level::createEgress()
{
	random_device generator;
	uniform_int_distribution<int> egressY_distr(1, height - 2);
	uniform_int_distribution<int> egressX_distr(1, width - 2);
	uniform_int_distribution<int> egress_direction(0, 3);
	egressDirection = static_cast<cardinalDirection>(egress_direction(generator));
	if (egressDirection == oppositeDirection(entranceDirection)) egressDirection = oppositeDirection(egressDirection);

	switch (egressDirection)
	{
	case N: egressPosition.setRelative(Cords{ 0, egressX_distr(generator) }); break; //egress on the upper wall of the room
	case E: egressPosition.setRelative(Cords{ egressY_distr(generator), width - 1 }); break; //egress on the right wall of the room
	case S: egressPosition.setRelative(Cords{ height - 1, egressX_distr(generator) }); break; //egress on the bottom wall of the room
	case W: egressPosition.setRelative(Cords{ egressY_distr(generator), 0 }); break; //egress on the left wall of the room
	}
	roomMap[egressPosition.getRelative().y][egressPosition.getRelative().x].setType(egress);
}

void Level::indexRelativelyRoom()
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			roomMap[y][x].setPosition().setRelative(Cords{ y, x });
		}
	}
}

void Level::indexAbsolutelyRoom(Cords entranceCords)
{
	entrancePosition.setAbsolute(entranceCords);
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			roomMap[y][x].setPosition().setAbsolute(Cords{ entranceCords.y + y - entrancePosition.getRelative().y, entranceCords.x + x - entrancePosition.getRelative().x });
			if (roomMap[y][x].getType() == egress) egressPosition.setAbsolute(Cords{ roomMap[0][0].getPosition().getAbsolute().y + y, roomMap[0][0].getPosition().getAbsolute().x + x });
		}
	}
}

Level::~Level()
{
}
