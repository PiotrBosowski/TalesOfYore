#pragma once
#include <vector>
#include <iostream>
#include "Item.h"
class Bundle
{
public:
	void addToBundle(Item* itemToPick);
	void removeFromBundle(Item* itemToDrop);
	bool checkCapacity(Item* itemToPick);
	double getCurrentLoad();
	double getCapacity();
	void print();
	friend std::ostream& operator<<(std::ostream& s, Bundle bundle);

	Bundle();
	~Bundle();

private:
	double capacity;
	std::vector<Item*> bundle_vec;
};

