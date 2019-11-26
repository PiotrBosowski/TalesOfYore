#pragma once
#include "Item.hpp"
#include "Arms.hpp"
#include "Chest.hpp"
#include "Feet.hpp"
#include "Hands.hpp"
#include "Head.hpp"
#include "Legs.hpp"
#include "Neck.hpp"
#include "Bundle.hpp"
#include <iostream>
class Equipment
{
public:
	Equipment();
	bool pickUp(Item * itemToPick);
	void dropOff(Item * itemToDrop);
	friend std::ostream& operator<<(std::ostream& s, const Equipment equipment);
	~Equipment();

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