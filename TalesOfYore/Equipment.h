#pragma once
#include "Item.h"
#include "Arms.h"
#include "Chest.h"
#include "Feet.h"
#include "Hands.h"
#include "Head.h"
#include "Legs.h"
#include "Neck.h"
#include "Bundle.h"
#include <iostream>
class Equipment
{
public:
	Equipment();
	~Equipment();
	
	bool pickUp(Item * itemToPick);
	void dropOff(Item * itemToDrop);
	friend std::ostream& operator<<(std::ostream& s, const Equipment equipment);

private:
	Arms arms;
	Chest chest;
	Feet feet;
	Hands hands;
	Head head;
	Legs legs;
	Neck neck;
	Bundle bundle;
};