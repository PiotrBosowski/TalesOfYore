#pragma once
#include <vector>
#include "Structures.hpp"
#include "Position.hpp"
#include "Room.hpp"
class Moving
{
public:
	Moving(Position * postion, World * world);
	bool isQueueEmpty(); //returns true if there are no more steps in vector
	Cords front(); //returns first step in vector
	void eraseFirst(); //deletes first step in vector
	void makeMove();
	void queueMove(Cords cordsToMove);
	~Moving();
private:
	double linearFunction(double A, double B, double x) const;
	std::vector <Cords> stepsQueue;
	Position * const position;
	World * const world;
};
