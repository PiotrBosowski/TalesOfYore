#pragma once
#include "Room.h"
#include <iostream>
#include <vector>
#include <string>
class Town : public Room
{
public:
	Town(std::string townName); //creates town-room which is saved in "townName" .txt file
	~Town();

private:
	void indexTown(); //for town-type room
};
