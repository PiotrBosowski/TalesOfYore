#pragma once
#include "Structures.hpp"

class Position
{
public:
	Position(Cords initialCords = { 0, 0, 0 });
	Position(Cords * initialCords);
	Cords get() const; //returns current cords
	void set(const Cords & absoluteCords); //changes cords to absoluteCords
	Position operator++(int);
	Position & operator++();
	Position operator--(int);
	Position & operator--();
	Position & operator=(const Cords & target);
	operator Cords(); //converts Position to Cords
	~Position();

private:
	Cords cords; //structure that stores x and y coordinates
};

bool operator==(const Cords & original, const Cords & compare); //returns true if cords and levels are equal
Cords operator+=(Cords & original, const Cords & add);
Cords operator+(const Cords & one, const Cords &two);
Cords operator-(const Cords & one, const Cords &two);
bool operator<=(const Cords & original, const Cords & compare);
bool operator<(const Cords & original, const Cords & compare);
bool operator>=(const Cords & original, const Cords & compare);
bool operator>(const Cords & original, const Cords & compare);
cardinalDirection getDirectionOfSuchVector(const Cords & original);