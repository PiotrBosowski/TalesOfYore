#pragma once
#include "Room.h"
#include <random>
class Level : public Room
{
public:
	Level(Cords previousEgressCords, cardinalDirection direction = N); //creates room with given direction and entrance cords
	~Level();

private:
	cardinalDirection entranceDirection; //cardinal direction in which you have to walk to enter the room
	Position entrancePosition; //stores relative coordinates of room's entrance
	void rollDimensions(); //initialize height (y) and width (x) of a regular room with random values (range: <MIN_SIZE, MAX_SIZE>)
	void createGroundAndWalls(); //creates, initializes with ground/wall value and pushes to roomMap vector all Squares that creates the room
	void createEntrance(cardinalDirection lastEgressDirection); //creates randomly placed entrance on adequate wall
	void createEgress(); //creates randomly placed egress on random wall (other than entrance wall)
	void indexRelativelyRoom(); //sets absolute and relative coordinates of squares that create regular room
	void indexAbsolutelyRoom(Cords entranceCords);
};

