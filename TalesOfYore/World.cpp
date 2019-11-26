#include "World.h"
#include "Room.h"
#include "Town.h"
#include "Level.h"
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

World::World()
{
	loadTown();
}

void World::loadTown(int townNumber)
{
	worldMap.push_back(new Town(townNames[townNumber]));
}

void World::createLevel()
{
	Cords lastEgressCords = worldMap.back()->getEgressPosition();
	cardinalDirection lastEgressDirection = worldMap.back()->getEgressDirection();
	worldMap.push_back(new Level(lastEgressCords, lastEgressDirection));
}

void World::printMap()
{
	for (Room * room : worldMap)
	{
		room->print_room();
	}
}

World::~World() {}
