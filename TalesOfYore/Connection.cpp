#include "Connection.hpp"


Connection::Connection(Node * node_, int distance_)
	: node{ node_ }, distance{ distance_ }
{

}

int Connection::getDistance() const
{
	return distance;
}

Node * Connection::getNode()
{
	return node;
}


Connection::~Connection()
{
}



bool operator<(const Connection & one, const Connection & two)
{
	if (one.getDistance() < two.getDistance()) return true;
	else return false;
}