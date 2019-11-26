#include "Position.h"
#include <iostream>
using namespace std;

Position::Position()
{
}

void Position::setAbsolute(const Cords & newCords)
{
	abs = newCords;
}

Cords Position::getAbsolute() const
{
	return abs;
}

void Position::setRelative(const Cords & newCords)
{
	rel = newCords;
}

Cords Position::getRelative() const
{
	return rel;
}

Position::~Position()
{
}

std::ostream& operator<<(std::ostream& s, const Cords& cords)
{
	std::cout << "(" << cords.x << "," << cords.y << ")";
	return s;
}
