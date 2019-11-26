#pragma once
#include <vector>
#include "Node.hpp"

class Room;

class Pathsetting
{
public:
	Pathsetting(const Room * const room_);
	void prepareGraph();
	const std::vector<Node*> & getNodesVector();
	~Pathsetting();

private:
	double linearFunction(double A, double B, double x) const;
	const Room * const room;
	std::vector <Node*> nodesVector;
	bool checkLine(const Cords & first, const Cords & second) const; //absolute cords
	bool checkStraightLine(const Cords & first, const Cords & second, const cardinalDirection lineDirection) const; //absolute cords
	bool checkDiagonalLine(const Cords & first, const Cords & second, cardinalDirection dir) const; //absolute cords
	bool checkPair(const Node * const first, const Node * const second);
	void checkNESWsquares(Node * nodeToCheck, const std::vector<std::vector<Square*>> & roomMapRef);
	void resizeNodesMap(std::vector<std::vector<Node*>> & nodesMap);
	void fillNodesMap(std::vector<std::vector<Node*>> & nodesMap);
	void initializeNodesVectorUsing(std::vector<std::vector<Node*>> & nodesMap);
	void createConnections();
};
