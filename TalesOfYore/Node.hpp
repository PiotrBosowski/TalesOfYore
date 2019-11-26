#pragma once
#include "Square.hpp"
#include <set>
#include <bitset>
#include "Connection.hpp"

class Node
{
public:
	Node(Square * square);
	~Node();
	Cords getPosition() const;
	bool checkDirection(cardinalDirection dir);
	void addConnection(Connection connection);
	std::bitset<8> type;
	std::multiset<Connection> & getConnectionSet();
	operator Cords() const;

private:
	std::multiset<Connection> connectionSet;
	Position * position; //pointer to a square's position
};