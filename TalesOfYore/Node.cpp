#include "Node.hpp"
using namespace std;

Node::Node(Square * square)
: position{ &square->position }
{
	type.set(); //1 to all bits //true means node will be able to "see" in this direction
}

Node::~Node()
{
}

Cords Node::getPosition() const
{
	return *position;
}

bool Node::checkDirection(cardinalDirection dir)
{
	return (type[dir]);
}

void Node::addConnection(Connection connection)
{
	connectionSet.insert(connection);
}

std::multiset<Connection>& Node::getConnectionSet()
{
	return connectionSet;
}

Node::operator Cords() const
{
	return position->get();
}

