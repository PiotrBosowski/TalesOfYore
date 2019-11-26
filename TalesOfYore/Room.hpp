#pragma once
#include <vector>
#include "Square.hpp"
#include "Position.hpp"
#include "Structures.hpp"
#include "Node.hpp"
#include "GUI.hpp"
#include "Pathsetting.hpp"

class Room
{
public:
	Room();
	Square * getSquare(Cords absoluteCords);
	Cords getEgressPosition();
	Cords getEntrancePosition();
	Cords getTopLeftCords() const;
	Cords getDownRightCords() const;
	int getRoomNumber();
	bool checkSquareBelonging(const Cords & absoluteCords); //returns true if cordsToCheck belongs to the room
	cardinalDirection getEgressDirection();
	const std::vector <std::vector<Square*>> & getRoomMap() const;
	virtual ~Room();
	int getHeight() const;
	int getWidth() const;
	bool checkLine(const Cords & first, const Cords & second) const;

protected:
	double linearFunction(double A, double B, double x) const;
	bool checkStraightLine(const Cords & first, const Cords & second, const cardinalDirection dir) const;
	bool checkDiagonalLine(const Cords & first, const Cords & second, cardinalDirection dir) const;
	std::vector <std::vector<Square*>> roomMap; //vector that keeps all Squares of which the room is made
	int height; //y dimension, height of the room
	int width;  //x dimension, width of the room
	cardinalDirection egressDirection;  //cardinal direction in which you have to walk to leave the room
	cardinalDirection entranceDirection; //cardinal direction in which you have to walk to enter the room
	Position egressPosition;
	Position entrancePosition;
	unsigned int roomNumber;
public:
	Pathsetting pathsetting;
};

//square class should contain addictional variable - a pointer that is either nullptr (if there is no node on this square) or points to a Node object