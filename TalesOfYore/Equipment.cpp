#include "Equipment.h"
#include <iostream>
using namespace std;



Equipment::Equipment()
{

}


Equipment::~Equipment()
{
}

bool Equipment::pickUp(Item * itemToPick)
{
	if (bundle.checkCapacity(itemToPick))
	{
		bundle.addToBundle(itemToPick);
		cout << "Picked up an item: " << itemToPick->getName() << endl;
		return true;
	}
	else
	{
		cout << "Can't carry anymore" << endl;
		return false;
	}
}

void Equipment::dropOff(Item * itemToDrop)
{
	bundle.removeFromBundle(itemToDrop);
}

ostream& operator<<(ostream& s, Equipment eq)
{
	s << eq.bundle << endl;
	return s;
}