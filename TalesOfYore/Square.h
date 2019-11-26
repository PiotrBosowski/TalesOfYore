#pragma once
#include <iostream>
#include "Position.h"

class Square
{
public:
	Square(int t = ground);
	int getType() const;
	void setType(int t);
	Position getPosition() const;
	Position & setPosition();
	Position & setPosition(Position newPos);
	~Square();

private:
	int type;
	Position position;
};

std::ostream& operator<<(std::ostream&, const Square&);