#pragma once
#include "Room.hpp"
class Level : public Room
{
public:
	Level(Cords previousEgressCords, cardinalDirection direction, int roomNumber_); //creates room with given direction and entrance cords

private:
	void rollDimensions(); //initialize height (y) and width (x) of a regular room with random values (range: <MIN_SIZE, MAX_SIZE>)
	void createGroundAndWalls(); //creates, initializes with ground/wall value and pushes to roomMap vector all Squares that creates the room
	void createEntrance(cardinalDirection lastEgressDirection, Cords lastEgressCords); //creates randomly placed entrance on adequate wall
	void createEgress(); //creates randomly placed egress on random wall (other than entrance wall)
	void indexAbsolutelyRoom(Cords entranceCords);
};

