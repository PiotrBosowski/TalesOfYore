#pragma once
#include "Room.hpp"
#include <vector>
#include <string>
#include <fstream>

class Town : public Room
{
public:
	Town(std::string townName, int roomNumber_); //creates town-room which is saved in "townName" .txt file

private:
	void indexTown(); //for town-type room
};
