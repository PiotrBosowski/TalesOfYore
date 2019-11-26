#pragma once

class Node;

class Connection
{
public:
	Connection(Node * node_, int distance_);
	int getDistance() const;
	Node * getNode();
	~Connection();

private:
	Node * node;
	int distance;
};

bool operator<(const Connection & one, const Connection & two);
