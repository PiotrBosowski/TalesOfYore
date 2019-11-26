#include "Room.h"
#include "Square.h"
#include <chrono>
#include <vector>
#include <string>
#include <random>
using namespace std;

Room::Room() {}

void Room::print_room()
{
	cout << "height: " << height << endl
		<< "width: " << width << endl
		<< "egress direction: " << egressDirection << endl
	//	<< "entrance relative position: " << entrancePosition.getRelative() << endl
		<< "egress relative position: " << egressPosition.getRelative() << endl
		//<< "entrance absolute position: " << entrancePosition.getAbsolute() << endl
		<< "egress absolute position: " << egressPosition.getAbsolute() << endl
		<< "relative span: " << roomMap[0][0].getPosition().getRelative() << " - "
		<< roomMap[height - 1][width - 1].getPosition().getRelative() << endl
		<< "absolute span: " << roomMap[0][0].getPosition().getAbsolute() << " - "
		<< roomMap[height - 1][width - 1].getPosition().getAbsolute() << endl;

	for (vector<Square> row : roomMap)
	{
		for (Square square : row)
			cout << square << ' ';
		cout << endl;
	}
}

Cords Room::getEgressPosition()
{
	return egressPosition.getAbsolute();
}

cardinalDirection Room::getEgressDirection()
{
	return egressDirection;
}

Room::~Room()
{
}