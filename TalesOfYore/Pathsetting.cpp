#include "Pathsetting.hpp"
#include "Room.hpp"
#include <vector>
using namespace std;

Pathsetting::Pathsetting(const Room * const room_)
	: room{ room_ }
{
}

void Pathsetting::prepareGraph()
{
	{
		vector<vector<Node*>> nodesMap;
		resizeNodesMap(nodesMap);
		fillNodesMap(nodesMap);
		//tutaj wybieramy rodzaj wyznaczenia grafu na podstawie mapy nodesMap: czy tworzymy liste czy pozostajemy jako mapa
		//if(nodesNumber < 1000)
		initializeNodesVectorUsing(nodesMap); //od tego momentu wezly mamy przepisane do vectora nalezacego do klasy Pathsetting, mapa zaraz zostanie usunieta
	}
	createConnections();
}

const std::vector<Node*>& Pathsetting::getNodesVector()
{
	return nodesVector;
}

void Pathsetting::initializeNodesVectorUsing(vector<vector<Node*>> & nodesMap)
{
	int nodeCounter = 0;
	for (vector<Node*> row : nodesMap)
	{
		for (Node* node : row)
		{
			if (node)
			{
				nodesVector.push_back(node); //nic nie usuwamy, jedynie przenosimy adresy nodow z mapy do wektora, mapa zostanie automatycznie usunieta
				nodeCounter++;
			}
		}
	}
	cout << nodeCounter << endl;
}

void Pathsetting::resizeNodesMap(vector<vector<Node*>> & nodesMap)
{
	int roomHeight = room->getHeight();
	int roomWidth = room->getWidth();
	for (int i = 0; i < roomHeight; i++)
			nodesMap.push_back(vector<Node*>{static_cast<unsigned __int64>(roomWidth), nullptr});
}
bool Pathsetting::checkLine(const Cords & first, const Cords & second) const
{
	//return true; //uncomment
	cardinalDirection lineDirection = getDirectionOfSuchVector(second - first);
	if (lineDirection == N || lineDirection == E || lineDirection == S || lineDirection == W)
		return checkStraightLine(first, second, lineDirection);
	else if (lineDirection == NE || lineDirection == SE || lineDirection == SW || lineDirection == NW)
		return checkDiagonalLine(first, second, lineDirection);
	else return false;
}

bool Pathsetting::checkStraightLine(const Cords & first, const Cords & second, const cardinalDirection dir) const
{
	auto & roomMap = room->getRoomMap();
	int rel_x = first.x - room->getTopLeftCords().x;
	int rel_y = first.y - room->getTopLeftCords().y;
	switch (dir)
	{
	case N:
	{
		int distance = first.y - second.y;
		for (int i = 2; i <= distance - 2; i++)
		{
			if (!roomMap[rel_y - i][rel_x]->isStepable()) return false;
		}
		return true;
	}
	case E:
	{
		int distance = second.x - first.x;
		for (int i = 2; i <= distance - 2; i++)
		{
			if (!roomMap[rel_y][rel_x + i]->isStepable()) return false;
		}
		return true;
	}
	case S:
	{
		int distance = second.y - first.y;
		for (int i = 2; i <= distance - 2; i++)
		{
			if (!roomMap[rel_y + i][rel_x]->isStepable()) return false;
		}
		return true;
	}
	case W:
	{
		int distance = second.x - first.x;
		for (int i = 2; i <= distance - 2; i++)
		{
			if (!roomMap[rel_y][rel_x - i]->isStepable()) return false;
		}
		return true;
	}
	default: return false;
	}
}

bool Pathsetting::checkDiagonalLine(const Cords &  first, const Cords & second, cardinalDirection dir) const
{
	auto & roomMap = room->getRoomMap();
	int actual_x_rel = first.x - room->getTopLeftCords().x;
	int actual_y_rel = first.y - room->getTopLeftCords().y;
	double A = static_cast<double>(second.y - first.y) / (second.x - first.x);
	double B = actual_y_rel - A * actual_x_rel;
	int distance = abs(first.x - second.x) + abs(first.y - second.y);
	switch (dir)
	{
	case NE:
	{
		while (distance > 0)
		{
			if (linearFunction(A, B, actual_x_rel + 1) < actual_y_rel)
			{
				--actual_y_rel;
			}
			else
			{
				++actual_x_rel;
			}
			if (!roomMap[actual_y_rel][actual_x_rel]->isStepable()) return false;
			distance--;
		}
		return true;
	}
	case SE:
	{
		while (distance > 0)
		{
			if (linearFunction(A, B, actual_x_rel + 1) > actual_y_rel + 1)
			{
				++actual_y_rel;
			}
			else
			{
				++actual_x_rel;
			}
			if (!roomMap[actual_y_rel][actual_x_rel]->isStepable()) return false;
			distance--;
		}
		return true;
	}
	case SW:
	{
		//return true;
		while (distance > 0)
		{
			if (linearFunction(A, B, actual_x_rel) > actual_y_rel + 1)
			{
				++actual_y_rel;
			}
			else
			{
				--actual_x_rel;
			}
			if (!roomMap[actual_y_rel][actual_x_rel]->isStepable()) return false;
			distance--;
		}
		return true;
	}
	case NW:
	{
		while (distance > 0)
		{
			if (linearFunction(A, B, actual_x_rel) < actual_y_rel)
			{
				--actual_y_rel;
			}
			else
			{
				--actual_x_rel;
			}
			if (!roomMap[actual_y_rel][actual_x_rel]->isStepable()) return false;
			distance--;
		}
		return true;
	}
	default: return false;
	}
}
bool Pathsetting::checkPair(const Node * const first, const Node * const second)
{
	//return true; //uncomment to see all possible pairs
	cardinalDirection vectorDirection = getDirectionOfSuchVector(second->getPosition() - first->getPosition());
	if (first->type[vectorDirection])
		if (second->type[oppositeDirection(vectorDirection)])
			if(checkLine(*first, *second)) return true; //check if line is available to walk
	return false;
}

int calculateDistance(const Cords & one, const Cords & two)
{
	return abs(two.x - one.x) + abs(two.y - one.y);
}

void Pathsetting::createConnections()
{
	int licznikdodanych = 0;
	for (size_t i = 0, imax = nodesVector.size(); i < imax; i++)
	{
		Node * first = nodesVector[i];
		for (size_t j = i + 1, jmax = nodesVector.size(); j < jmax; j++) //it is essential to initialize j with i + 1 ,then you dont have to check if first == second
		{
			Node * second = nodesVector[j];
			if (checkPair(first, second))
			{
				int distance = calculateDistance(first->getPosition(), second->getPosition());
				first->addConnection(Connection{ second, distance });
				second->addConnection(Connection{ first, distance });
				licznikdodanych++;
			}
		}
	}
	cout << licznikdodanych << "dodanych" << endl;
}


void Pathsetting::checkNESWsquares(Node * nodeToCheck, const std::vector<std::vector<Square*>> & roomMapRef)
{
	int nodeRelCordX = nodeToCheck->getPosition().x - room->getTopLeftCords().x;
	int nodeRelCordY = nodeToCheck->getPosition().y - room->getTopLeftCords().y;
	bitset<8>newType = nodeToCheck->type;
	if (nodeToCheck->type[NW] && nodeToCheck->type[NE])
	{
		if (!roomMapRef[nodeRelCordY - 1][nodeRelCordX]->isStepable()) //N
		{
			newType[N] = false;
			newType[NE] = false;
			newType[NW] = false;
		}
	}
	if (nodeToCheck->type[NE] && nodeToCheck->type[SE])
	{
		if (!roomMapRef[nodeRelCordY][nodeRelCordX + 1]->isStepable()) //E
		{
			newType[E] = false;
			newType[NE] = false;
			newType[SE] = false;
		}
	}
	if (nodeToCheck->type[SE] && nodeToCheck->type[SW])
	{
		if (!roomMapRef[nodeRelCordY + 1][nodeRelCordX]->isStepable()) //S
		{
			newType[S] = false;
			newType[SE] = false;
			newType[SW] = false;
		}
	}
	if (nodeToCheck->type[SW] && nodeToCheck->type[N])
	{
		if (!roomMapRef[nodeRelCordY][nodeRelCordX - 1]->isStepable()) //W
		{
			newType[W] = false;
			newType[NW] = false;
			newType[SW] = false;
		}
	}
	nodeToCheck->type = newType;
}

void Pathsetting::fillNodesMap(vector<vector<Node*>> & nodesMap)
{
	bool lastWasStepable;
	auto & roomMapRef = room->getRoomMap();
	for (int j = 0, jmax = static_cast<int>(roomMapRef.size()); j < jmax; j++)
	{
		lastWasStepable = false;
		for (int i = 0, imax = static_cast<int>(roomMapRef[j].size()); i < imax; i++)
		{
			if (lastWasStepable)
			{
				if (roomMapRef[j][i]->isStepable())
				{
					;
				}
				else //last was stepable and current is unstepable
				{
					//create NW Node at [j-1][i-1] if:
					//that square exist and is walkable
					//AND square [j-1][i] is walkable
					if (j - 1 >= 0 && i - 1 >= 0)
					{
						if (roomMapRef[j - 1][i - 1]->isStepable() == true)
						{
							if (roomMapRef[j - 1][i]->isStepable() == true)
							{
								if (nodesMap[j - 1][i - 1] == nullptr)
								{
									nodesMap[j - 1][i - 1] = new Node{ roomMapRef[j - 1][i - 1]}; //NW
									checkNESWsquares(nodesMap[j - 1][i - 1], roomMapRef);
								}
								nodesMap[j - 1][i - 1]->type[SE] = false;
							}
						}
					}
					//create SW Node at [j+1][i-1] if:
					//that square exist and is walkable
					//AND square [j+1][i] is walkable
					if (j + 1 < roomMapRef.size() && i - 1 >= 0)
					{
						if (roomMapRef[j + 1][i - 1]->isStepable() == true)
						{
							if (roomMapRef[j + 1][i]->isStepable() == true)
							{
								if (nodesMap[j + 1][i - 1] == nullptr)
								{
									nodesMap[j + 1][i - 1] = new Node{ roomMapRef[j + 1][i - 1]}; //SW
									checkNESWsquares(nodesMap[j + 1][i - 1], roomMapRef);
								}
								nodesMap[j + 1][i - 1]->type[NE] = false;
							}
						}
					}
				}
			}
			else //last was unstepable
			{
				if (roomMapRef[j][i]->isStepable())
				{
					//create NE Node at [j-1][i] if:
					//that square exists and is walkable
					//AND square [j-1][i-1] is walkable

					if (j - 1 >= 0 && i - 1 >= 0)
					{
						if (roomMapRef[j - 1][i]->isStepable() == true)
						{
							if (roomMapRef[j - 1][i - 1]->isStepable() == true)
							{
								if (nodesMap[j - 1][i] == nullptr)
								{
									nodesMap[j - 1][i] = new Node{ roomMapRef[j - 1][i] }; //NE
									checkNESWsquares(nodesMap[j - 1][i], roomMapRef);
								}
								nodesMap[j - 1][i]->type[SW] = false;
							}
						}
					}

					////////////////////////////////////
					//create SE Node at [j+1][i] if:
					//that square exists and is walkable
					//AND square [j+1][i-1] is walkable

					if (j + 1 < roomMapRef.size() && i - 1 >= 0)
					{
						if (roomMapRef[j + 1][i]->isStepable() == true)
						{
							if (roomMapRef[j + 1][i - 1]->isStepable() == true)
							{
								if (nodesMap[j + 1][i] == nullptr)
								{
									nodesMap[j + 1][i] = new Node{ roomMapRef[j + 1][i] }; //SE
									checkNESWsquares(nodesMap[j + 1][i], roomMapRef);
								}
								nodesMap[j + 1][i]->type[NW] = false;
							}
						}
					}
				}
				else //last was unstepable and current is unstepable
				{
					;
				}
			}
			lastWasStepable = roomMapRef[j][i]->isStepable();
		}
	}
}

double Pathsetting::linearFunction(double A, double B, double x) const
{
	return A * (x - 0.5) + B + 0.5;
}

Pathsetting::~Pathsetting()
{
}