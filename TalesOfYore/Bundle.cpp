#include "Bundle.h"
#include "Item.h"
#include <vector>
#include <algorithm>
using namespace std;

//////////////////////////////////////////////////////////////////////////////

Bundle::Bundle() : capacity{ 20 }
{

}

Bundle::~Bundle()
{

}

void Bundle::addToBundle(Item* itemToPick)
{
	bundle_vec.push_back(itemToPick);
}
void Bundle::removeFromBundle(Item* itemToDrop)
{	
	bundle_vec.erase(remove(bundle_vec.begin(), bundle_vec.end(), itemToDrop), bundle_vec.end());
}

bool Bundle::checkCapacity(Item* itemToPick)
{
	double weight = getCurrentLoad();
	weight += itemToPick->getWeight();
	return (weight > capacity) ? false : true;
}

double Bundle::getCurrentLoad()
{
	double weight = 0;
	for (Item* item : bundle_vec)
	{
		weight += item->getWeight();
	}
	return weight;
}

double Bundle::getCapacity()
{
	return capacity;
}

void Bundle::print()
{
	
}

ostream& operator<<(ostream& s, Bundle bundle)
{
	s << endl << "__________Bundle contains: __________" << endl;
	for (Item* item : bundle.bundle_vec)
	{
		s << item;
	}
	s << ":::::Bundle load: " << bundle.getCurrentLoad()
		<< "/" << bundle.getCapacity() << ":::::" << endl;
	return s;
}

////////////////////////////////////////////////////////////////////////////////





