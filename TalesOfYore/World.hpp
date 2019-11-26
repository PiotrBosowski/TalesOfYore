#pragma once
#include "Room.hpp"
#include "Town.hpp"
#include "Level.hpp"
#include <vector>
#include <string>
#include "GUI.hpp"
#include "Structures.hpp"

class World
{
	friend void GUI::draw(World *);
public:
	World(int townNumber = 0); //creates a world that starts with 0th town
	void loadTown(int townNumber = 0); //creates and puts a Town in roomVector according to a txt file (default file -> file no. 0)
	void createLevel(unsigned int numberOfLevels = 1); //creates and puts in roomVector new Level, that will be compatibile with previous one
	Position getNextEntrancePosition(); //returns cords of latest rooms egress (==next rooms entrance)
	Position getSpawnPosition();
	Square * getSquare(const Cords & absoluteCords) const;
	const std::vector <Room*> & getWorldMap() const;
	int getRoomCounter() const;
	~World();

private:
	std::vector <std::string> townNames { "Iiyama.txt" };
	std::vector <Room*> worldMap; //vector that stores all rooms
	int roomCounter = 0;
};