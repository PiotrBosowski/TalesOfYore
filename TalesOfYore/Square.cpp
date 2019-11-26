#include "Square.h"
#include <iostream>
#include "Position.h"
using namespace std;

Square::Square(int t) : type{ t }
{

}

int Square::getType() const
{
	return type;
}

void Square::setType(int t)
{
	type = t;
}

Position Square::getPosition() const
{
	return position;
}

Position & Square::setPosition()
{
	return position;
}

Position & Square::setPosition(Position newPos)
{
	return position = newPos;
}

Square::~Square()
{

}

ostream& operator<<(ostream& s, const Square& sq)
{
	s << sq.getType();
	return s;
}