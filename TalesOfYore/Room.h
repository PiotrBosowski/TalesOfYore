#pragma once
#include <vector>
#include <string>
#include "Square.h"
#include "Position.h"
#include <fstream>
#include <random>
#include "Structures.h"
 
class Room
{
public:
	Room();
	Cords getEgressPosition();
	cardinalDirection getEgressDirection();
	void print_room(); //debug print, should be rather overloaded operator<< int GIT class
	~Room();

protected:
	std::vector <std::vector<Square>> roomMap; //vector that keeps all Squares of which the room is made
	int height; //y dimension, height of the room
	int width;  //x dimension, width of the room
	cardinalDirection egressDirection;  //cardinal direction in which you have to walk to leave the room
	Position firstSquarePosition;
	Position lastSquarePosition;
	Position egressPosition; //stores relative coordinates of room's egress
};