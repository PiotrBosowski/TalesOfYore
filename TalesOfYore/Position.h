#pragma once
#include <iostream>
#include "Structures.h"
class Position
{
public:
	Position();
	void setAbsolute(const Cords & newCords); //same overloaded
	Cords getAbsolute() const; //gets absolute position
	void setRelative(const Cords & newCords); //same but overloaded
	Cords getRelative() const; //gets absolute position
	~Position();

private:
	Cords abs; //stores absolute cords
	Cords rel; //stores relative (in-room) cords
};

std::ostream& operator<<(std::ostream& s, const Cords& cords);       // those 2 functions does almost the same thing