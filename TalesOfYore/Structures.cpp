#include "Structures.h"
using namespace std;

cardinalDirection oppositeDirection(cardinalDirection dirToSwitch)
{
	return static_cast<cardinalDirection>(((static_cast<int>(dirToSwitch)) + 2) % 4);
}