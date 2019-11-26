#include "Item.h"
#include <iostream>
#include <random>
#include <string>
using namespace std;

////////////////////////////////////////////////////////////////
Item::Item()
{
	randomize(armor, 1, 10);
	randomize(weight, 0, 2);
	randomize(stat);
}

Item::~Item()
{
}

string Item::getName()
{
	return itemName;
}

double Item::getArmor()
{
	return armor;
}
double Item::getWeight()
{
	return weight;
}
statistic Item::getStat()
{
	return stat;
}

ostream& operator<<(ostream& s, Item* item)
{
	s << item->itemClassName << ": " << item->itemName <<
	" {" << item->stat.name << ": " << item->stat.value <<
	", armor: " << item->armor << ", " << item->weight << " kg}" << endl;
	return s;
}

/////////////////////////////////////////////////////////////////

#include "Head.h"
#include "Neck.h"
#include "Chest.h"
#include "Legs.h"
#include "Feet.h"
#include "Arms.h"
#include "Hands.h"

Item * randomItem()
{
	random_device generator;
	uniform_int_distribution<int> distribution(0, 6);
	switch (distribution(generator))
	{
	case 0: { return new Head; }
	case 1: { return new Neck; }
	case 2: { return new Chest; }
	case 3: { return new Legs; }
	case 4: { return new Feet; }
	case 5: { return new Arms; }
	case 6: { return new Hands; }
	default: { return new Head; }
	}
}

void randomize(statistic & stat, int min, int max)
{
	random_device generator;
	uniform_real_distribution<double> distr_double(min, max);
	uniform_int_distribution<int> distr_int(0, 2);
	stat.value = distr_double(generator);
	stat.type = static_cast<statisticType>(distr_int(generator));
	switch (stat.type)
	{
	case dexterity: {stat.name = "dexterity"; break; }
	case strength: {stat.name = "strength"; break; }
	case intelligence: {stat.name = "intelligence"; break; }
	}
}

void randomize(double & value, int min, int max)
{
	random_device generator;
	uniform_real_distribution<double> distr_double(min, max);
	value = distr_double(generator);
}