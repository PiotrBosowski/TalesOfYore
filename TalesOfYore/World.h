#pragma once
#include "Room.h"
#include <vector>
#include <string>
class World
{
public:
	World();
	void loadTown(int townNumber = 0); //creates and puts a Town in roomVector
	void createLevel(); //creates and puts in roomVector new Level, that will be compatibile with previous ones
	void printMap(); //prints whole map //warning: its retarded yet :/
	~World();

private:
	std::vector <std::string> townNames { "Iiyama.txt" };
	std::vector <Room*> worldMap; //vector that stores all rooms
};

